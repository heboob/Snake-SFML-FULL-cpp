// Assets.cpp
#include "Assets.hpp"
#include <iostream>

// Lädt alle Assets (Texturen, Sounds, Fonts, Musik)
// Gibt false zurück, wenn etwas nicht geladen werden konnte.
bool Assets::loadAll()
{
    // ---------------- Musik ----------------
    if (!startMusic.openFromFile("startscreen.ogg")) {
        std::cerr << "Error: startscreen.ogg\n";
        return false;
    }
    startMusic.setLoop(true); // Startscreen-Musik läuft in Endlosschleife

    if (!gameMusic.openFromFile("game.ogg")) {
        std::cerr << "Error: game.ogg\n";
        return false;
    }
    gameMusic.setLoop(true); // Spielmusik läuft ebenfalls in Endlosschleife

    // ---------------- Bilder (Texturen) ----------------
    if (!startTexture.loadFromFile("startscreen.png")) {
        std::cerr << "Error: startscreen.png\n";
        return false;
    }

    if (!backgroundTexture.loadFromFile("forest_background.png")) {
        std::cerr << "Error: forest_background.png\n";
        return false;
    }

    if (!gameOverTexture.loadFromFile("gameover.png")) {
        std::cerr << "Error: gameover.png\n";
        return false;
    }

    if (!snakeTexture.loadFromFile("snake_segment.png")) {
        std::cerr << "Error: snake_segment.png\n";
        return false;
    }

    if (!headTextureUp.loadFromFile("snake_head_w.png")) {
        std::cerr << "Error: snake_head_w.png\n";
        return false;
    }

    if (!headTextureDown.loadFromFile("snake_head_s.png")) {
        std::cerr << "Error: snake_head_s.png\n";
        return false;
    }

    if (!headTextureLeft.loadFromFile("snake_head_a.png")) {
        std::cerr << "Error: snake_head_a.png\n";
        return false;
    }

    if (!headTextureRight.loadFromFile("snake_head_d.png")) {
        std::cerr << "Error: snake_head_d.png\n";
        return false;
    }

    if (!appleTexture.loadFromFile("apple.png")) {
        std::cerr << "Error: apple.png\n";
        return false;
    }

    // ---------------- Schrift ----------------
    if (!font.loadFromFile("PressStart2P.ttf")) {
        std::cerr << "Error: PressStart2P.ttf\n";
        return false;
    }

    // ---------------- Soundeffekt ----------------
    if (!gameOverBuffer.loadFromFile("gameover.ogg")) {
        std::cerr << "Error: gameover.ogg\n";
        return false;
    }
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setLoop(false); // soll nur einmal abgespielt werden

    // Wenn alles geklappt hat → true zurückgeben
    return true;
}
