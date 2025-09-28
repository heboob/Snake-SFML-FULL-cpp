// Game.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Assets.hpp"
#include "Snake.hpp"
#include "FoodManager.hpp"

// ------------------------------------------------------------
// Verschiedene Zustände des Spiels
// - StartScreen: Titelbildschirm
// - Playing: laufendes Spiel
// - GameOver: Spielende mit Retry-Möglichkeit
// ------------------------------------------------------------
enum class GameState { StartScreen, Playing, GameOver };

// ------------------------------------------------------------
// Game-Klasse
// Koordiniert das komplette Spiel:
// - Fenster erstellen
// - Assets laden
// - Schlange und FoodManager verwalten
// - Spielzustände umschalten
// ------------------------------------------------------------
class Game {
public:
    Game();     // Konstruktor
    void run(); // Hauptschleife

private:
    // Reset für ein neues Spiel (Schlange, Punkte usw.)
    void resetGame();

    // Jeder Zustand hat seine eigene Loop
    void runStartScreen();
    void runPlaying();
    void runGameOver();

    // --------------------------------------------------------
    // Attribute
    // --------------------------------------------------------
    sf::RenderWindow m_window;   // Spiel-Fenster
    Assets m_assets;             // Alle Ressourcen (Bilder, Musik, Sounds)
    std::unique_ptr<Snake> m_snake;      // Schlange
    std::unique_ptr<FoodManager> m_food; // FoodManager

    GameState m_state;  // aktueller Zustand (Startscreen, Spiel, GameOver)
    int m_score;        // aktuelle Punktzahl
    float m_moveDelay;  // wie schnell die Schlange sich bewegt
    const float m_minDelay = 0.08f; // Minimalgeschwindigkeit
    float m_moveTimer;  // Timer für Snake-Bewegungen

    // UI-Elemente
    sf::Text m_title;     // Titel im Startscreen
    sf::Text m_pressKey;  // Hinweis "Taste drücken"
    sf::Text m_credits;   // Credits
    sf::Text m_scoreText; // Punktestand
    sf::Text m_retryText; // Text im Retry-Button

    sf::RectangleShape m_retryButton; // Button im GameOver-Screen

    // Sprites für Hintergründe
    sf::Sprite m_startSprite;     // Startscreen-Hintergrund
    sf::Sprite m_backgroundSprite; // Spielfeld-Hintergrund
    sf::Sprite m_gameOverSprite;   // GameOver-Bild
};
