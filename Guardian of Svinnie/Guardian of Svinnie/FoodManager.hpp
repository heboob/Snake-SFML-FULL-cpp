// FoodManager.hpp
#pragma once
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Assets.hpp"

// ------------------------------------------------------------
// FoodManager-Klasse
// Verwaltet die Äpfel im Spiel:
// - zufällige Platzierung im Spielfeld
// - prüfen, ob Schlange einen Apfel gefressen hat
// - zeichnen der Äpfel
// ------------------------------------------------------------
class FoodManager {
public:
    // Konstruktor: benötigt Spielfeldgröße (cols, rows, cellSize) und Zugriff auf Assets
    FoodManager(int cols, int rows, int cellSize, const Assets& assets);

    // Initialisiert eine Anzahl Äpfel und platziert sie an freien Positionen
    void init(int count, const std::deque<Segment>& snake);

    // Prüft, ob der Kopf der Schlange einen Apfel berührt
    // Gibt den Index des Apfels zurück oder -1 falls keiner getroffen wurde
    int checkCollision(const Segment& head) const;

    // Ersetzt den Apfel an Position index durch einen neuen an einer freien Stelle
    void replaceFoodAt(int index, const std::deque<Segment>& snake);

    // Zeichnet alle Äpfel ins Fenster
    void draw(sf::RenderWindow& window) const;

private:
    // Erzeugt eine zufällige Position, die nicht von der Schlange belegt ist
    Segment randomFreePos(const std::deque<Segment>& snake);

    std::vector<Segment> m_food;  // Positionen aller Äpfel
    int m_cols, m_rows, m_cellSize; // Spielfeldgröße
    const Assets& m_assets;       // Zugriff auf Texturen
    mutable sf::Sprite m_appleSprite; // Sprite für Äpfel (mutable = auch in const draw veränderbar)
    std::mt19937 m_rng;           // Zufallszahlengenerator
};
