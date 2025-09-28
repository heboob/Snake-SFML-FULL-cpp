// Assets.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// ------------------------------------------------------------
// Die Klasse Assets verwaltet alle Ressourcen, die das Spiel braucht.
// Dazu gehören:
// - Texturen (Bilder für Snake, Apfel, Hintergründe, Screens)
// - Schriftart (Font für Texte)
// - Musik (Startscreen, Spielmusik)
// - Soundeffekte (Game Over Sound)
//
// Vorteil: Alle Ressourcen werden an einer Stelle geladen
// und über Getter-Funktionen im Spiel verwendet.
// ------------------------------------------------------------
class Assets {
public:
    Assets() = default;

    // Lädt alle Assets aus Dateien
    bool loadAll();

    // Getter für Texturen
    const sf::Texture& segment() const { return snakeTexture; }   // Körperteil der Schlange
    const sf::Texture& headUp() const { return headTextureUp; }   // Kopf nach oben
    const sf::Texture& headDown() const { return headTextureDown; } // Kopf nach unten
    const sf::Texture& headLeft() const { return headTextureLeft; } // Kopf nach links
    const sf::Texture& headRight() const { return headTextureRight; } // Kopf nach rechts
    const sf::Texture& apple() const { return appleTexture; }     // Apfel
    const sf::Texture& startScreen() const { return startTexture; } // Startscreen-Bild
    const sf::Texture& background() const { return backgroundTexture; } // Spielfeld-Hintergrund
    const sf::Texture& gameOver() const { return gameOverTexture; } // Game-Over-Bild

    // Getter für Schrift
    const sf::Font& getFont() const { return font; }

    // Getter für Musik
    sf::Music& getStartMusic() { return startMusic; } // Musik im Startscreen
    sf::Music& getGameMusic() { return gameMusic; }   // Musik während des Spiels

    // Getter für Game Over Soundeffekt
    sf::Sound& getGameOverSound() { return gameOverSound; }

private:
    // Texturen für Snake
    sf::Texture snakeTexture;
    sf::Texture headTextureUp, headTextureDown, headTextureLeft, headTextureRight;

    // Texturen für Apfel und Hintergründe
    sf::Texture appleTexture;
    sf::Texture startTexture;
    sf::Texture backgroundTexture;
    sf::Texture gameOverTexture;

    // Schriftart
    sf::Font font;

    // Musik (lang spielend)
    sf::Music startMusic;
    sf::Music gameMusic;

    // Soundeffekt (kurz, einmalig abspielbar)
    sf::SoundBuffer gameOverBuffer; // Datei wird hier reingeladen
    sf::Sound gameOverSound;        // Instanz, die den Sound abspielt
};
