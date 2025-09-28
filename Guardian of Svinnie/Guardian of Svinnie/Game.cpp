// Game.cpp
#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

// ------------------------------------------------------------
// Konstruktor: erstellt Fenster, lädt Assets und richtet UI ein
// ------------------------------------------------------------
Game::Game()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game SVI")
{
    m_window.setFramerateLimit(60);

    // Assets laden
    if (!m_assets.loadAll()) {
        std::cerr << "Fehler: Assets konnten nicht geladen werden.\n";
        m_window.close();
        return;
    }

    // ---------------- Hintergrundbilder ----------------
    m_startSprite.setTexture(m_assets.startScreen());
    m_startSprite.setScale(
        float(WINDOW_WIDTH) / m_assets.startScreen().getSize().x,
        float(WINDOW_HEIGHT) / m_assets.startScreen().getSize().y
    );

    m_backgroundSprite.setTexture(m_assets.background());
    m_backgroundSprite.setScale(
        float(WINDOW_WIDTH) / m_assets.background().getSize().x,
        float(WINDOW_HEIGHT) / m_assets.background().getSize().y
    );

    m_gameOverSprite.setTexture(m_assets.gameOver());
    m_gameOverSprite.setScale(
        float(WINDOW_WIDTH) / m_assets.gameOver().getSize().x,
        float(WINDOW_HEIGHT) / m_assets.gameOver().getSize().y
    );

    // ---------------- Texte im Startscreen ----------------
    m_title = sf::Text("Guardian of Svinnie", m_assets.getFont(), 32);
    m_title.setFillColor(sf::Color(255, 220, 100));
    auto tb = m_title.getLocalBounds();
    m_title.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    m_title.setPosition(WINDOW_WIDTH / 2.f, 80.f);

    m_pressKey = sf::Text("Druecke eine Taste zum Starten", m_assets.getFont(), 20);
    m_pressKey.setFillColor(sf::Color(255, 220, 100));
    auto kb = m_pressKey.getLocalBounds();
    m_pressKey.setOrigin(kb.left + kb.width / 2.f, kb.top + kb.height / 2.f);
    m_pressKey.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

    m_credits = sf::Text("Ein Spiel von Iheb und Tsu", m_assets.getFont(), 16);
    m_credits.setFillColor(sf::Color(200, 180, 80));
    auto cb = m_credits.getLocalBounds();
    m_credits.setOrigin(cb.left + cb.width / 2.f, cb.top + cb.height / 2.f);
    m_credits.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 40.f);

    // ---------------- Score-Text ----------------
    m_scoreText = sf::Text("", m_assets.getFont(), 24);
    m_scoreText.setFillColor(sf::Color::Yellow);

    // ---------------- Retry-Button im GameOver-Screen ----------------
    m_retryButton = sf::RectangleShape({ 520.f, 70.f });
    m_retryButton.setFillColor(sf::Color(255, 220, 100));
    m_retryButton.setOutlineColor(sf::Color::Black);
    m_retryButton.setOutlineThickness(4.f);
    m_retryButton.setOrigin(m_retryButton.getSize().x / 2.f, m_retryButton.getSize().y / 2.f);
    m_retryButton.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 200.f);

    m_retryText = sf::Text("Neu versuchen", m_assets.getFont(), 28);
    m_retryText.setFillColor(sf::Color::Black);
    auto rb = m_retryText.getLocalBounds();
    m_retryText.setOrigin(rb.left + rb.width / 2.f, rb.top + rb.height / 2.f);
    m_retryText.setPosition(m_retryButton.getPosition());

    // ---------------- Startzustand ----------------
    m_state = GameState::StartScreen;
    resetGame();
}

// ------------------------------------------------------------
// Spiel zurücksetzen: Punkte, Snake, Food
// ------------------------------------------------------------
void Game::resetGame()
{
    m_score = 0;
    m_moveDelay = 0.25f; // Startgeschwindigkeit
    m_moveTimer = 0.f;

    // Neue Schlange in der Mitte
    m_snake = std::make_unique<Snake>(COLS / 2, ROWS / 2, CELL_SIZE, m_assets);

    // FoodManager initialisieren (2 Äpfel am Anfang)
    m_food = std::make_unique<FoodManager>(COLS, ROWS, CELL_SIZE, m_assets);
    m_food->init(2, m_snake->body());
}

// ------------------------------------------------------------
// Hauptschleife: wechselt je nach Zustand in die passende Loop
// ------------------------------------------------------------
void Game::run()
{
    while (m_window.isOpen()) {
        switch (m_state) {
        case GameState::StartScreen: runStartScreen(); break;
        case GameState::Playing: runPlaying(); break;
        case GameState::GameOver: runGameOver(); break;
        }
    }
}

// ------------------------------------------------------------
// Startscreen: Musik + "Taste drücken" Effekt
// ------------------------------------------------------------
void Game::runStartScreen()
{
    m_assets.getStartMusic().play();
    float pulseTime = 0.f;
    sf::Event event;

    while (m_window.isOpen() && m_state == GameState::StartScreen) {
        // Events abfragen
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window.close();

            // Beliebige Taste → Spiel starten
            if (event.type == sf::Event::KeyPressed) {
                m_state = GameState::Playing;
                m_assets.getStartMusic().stop();
                m_assets.getGameMusic().play();
            }
        }

        // Text "Drücke Taste" pulsieren lassen
        pulseTime += 0.03f;
        float scale = 1.f + 0.05f * std::sin(pulseTime);
        m_pressKey.setScale(scale, scale);

        // Zeichnen
        m_window.clear();
        m_window.draw(m_startSprite);
        m_window.draw(m_title);
        m_window.draw(m_pressKey);
        m_window.draw(m_credits);
        m_window.display();
    }
}

// ------------------------------------------------------------
// Spielloop: Snake bewegen, Food prüfen, Zeichnen
// ------------------------------------------------------------
void Game::runPlaying()
{
    sf::Clock clock;

    while (m_window.isOpen() && m_state == GameState::Playing) {
        float dt = clock.restart().asSeconds();
        m_moveTimer += dt;

        // Events
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window.close();

            // Steuerung mit WASD
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) m_snake->setDirection(Up);
                if (event.key.code == sf::Keyboard::S) m_snake->setDirection(Down);
                if (event.key.code == sf::Keyboard::A) m_snake->setDirection(Left);
                if (event.key.code == sf::Keyboard::D) m_snake->setDirection(Right);
            }
        }

        // Snake bewegen, wenn Delay abgelaufen
        if (m_moveTimer >= m_moveDelay) {
            m_moveTimer = 0.f;
            Segment next = m_snake->getNextHead();

            // Wand-Kollision
            if (next.x < 0 || next.x >= COLS || next.y < 0 || next.y >= ROWS) {
                m_state = GameState::GameOver;
                m_assets.getGameMusic().stop();
                m_assets.getGameOverSound().play(); // Sound abspielen
                break;
            }

            // Eigenkollision
            if (m_snake->checkSelfCollision(next)) {
                m_state = GameState::GameOver;
                m_assets.getGameMusic().stop();
                m_assets.getGameOverSound().play(); // Sound abspielen
                break;
            }

            // Kopf setzen
            m_snake->pushHead(next);

            // Food prüfen
            int idx = m_food->checkCollision(next);
            if (idx >= 0) {
                // Punktzahl erhöhen
                m_score++;

                // Schlange schneller machen
                if (m_moveDelay > m_minDelay) m_moveDelay -= 0.01f;

                // Apfel ersetzen
                m_food->replaceFoodAt(idx, m_snake->body());
            }
            else {
                // Wenn kein Apfel → Schwanz entfernen
                m_snake->popTail();
            }
        }

        // ---------------- Zeichnen ----------------
        m_window.clear();
        m_window.draw(m_backgroundSprite);
        m_food->draw(m_window);
        m_snake->draw(m_window);

        // Punkteanzeige
        m_scoreText.setString("Punkte: " + std::to_string(m_score));
        m_scoreText.setPosition(20.f, 20.f);
        m_window.draw(m_scoreText);

        m_window.display();
    }
}

// ------------------------------------------------------------
// GameOver-Screen: GameOver-Bild + Retry-Button + Punkte
// ------------------------------------------------------------
void Game::runGameOver()
{
    sf::Event event;

    while (m_window.isOpen() && m_state == GameState::GameOver) {
        // Events abfragen
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window.close();

            // Klick auf Retry-Button
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (m_retryButton.getGlobalBounds().contains(mousePos)) {
                    m_state = GameState::StartScreen;
                    resetGame();
                }
            }
        }

        // Hover-Effekt für den Button
        sf::Vector2i mousePixel = sf::Mouse::getPosition(m_window);
        sf::Vector2f mouseWorld = m_window.mapPixelToCoords(mousePixel);
        if (m_retryButton.getGlobalBounds().contains(mouseWorld))
            m_retryButton.setFillColor(sf::Color(255, 240, 150));
        else
            m_retryButton.setFillColor(sf::Color(255, 220, 100));

        // ---------------- Zeichnen ----------------
        m_window.clear();
        m_window.draw(m_gameOverSprite);   // Hintergrund (GameOver-Bild)
        m_window.draw(m_retryButton);      // Button
        m_window.draw(m_retryText);        // Button-Text

        // Punkte unter dem Button anzeigen
        m_scoreText.setString("Punkte: " + std::to_string(m_score));
        m_scoreText.setPosition(
            WINDOW_WIDTH / 2.f - m_scoreText.getLocalBounds().width / 2.f,
            m_retryButton.getPosition().y + m_retryButton.getSize().y / 2.f + 80.f
        );
        m_window.draw(m_scoreText);

        m_window.display();
    }
}
