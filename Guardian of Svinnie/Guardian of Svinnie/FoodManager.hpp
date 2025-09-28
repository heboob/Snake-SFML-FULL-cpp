// FoodManager.hpp
#pragma once
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Assets.hpp"

// ------------------------------------------------------------
// FoodManager-Klasse
// Verwaltet die �pfel im Spiel:
// - zuf�llige Platzierung im Spielfeld
// - pr�fen, ob Schlange einen Apfel gefressen hat
// - zeichnen der �pfel
// ------------------------------------------------------------
class FoodManager {
public:
    // Konstruktor: ben�tigt Spielfeldgr��e (cols, rows, cellSize) und Zugriff auf Assets
    FoodManager(int cols, int rows, int cellSize, const Assets& assets);

    // Initialisiert eine Anzahl �pfel und platziert sie an freien Positionen
    void init(int count, const std::deque<Segment>& snake);

    // Pr�ft, ob der Kopf der Schlange einen Apfel ber�hrt
    // Gibt den Index des Apfels zur�ck oder -1 falls keiner getroffen wurde
    int checkCollision(const Segment& head) const;

    // Ersetzt den Apfel an Position index durch einen neuen an einer freien Stelle
    void replaceFoodAt(int index, const std::deque<Segment>& snake);

    // Zeichnet alle �pfel ins Fenster
    void draw(sf::RenderWindow& window) const;

private:
    // Erzeugt eine zuf�llige Position, die nicht von der Schlange belegt ist
    Segment randomFreePos(const std::deque<Segment>& snake);

    std::vector<Segment> m_food;  // Positionen aller �pfel
    int m_cols, m_rows, m_cellSize; // Spielfeldgr��e
    const Assets& m_assets;       // Zugriff auf Texturen
    mutable sf::Sprite m_appleSprite; // Sprite f�r �pfel (mutable = auch in const draw ver�nderbar)
    std::mt19937 m_rng;           // Zufallszahlengenerator
};
