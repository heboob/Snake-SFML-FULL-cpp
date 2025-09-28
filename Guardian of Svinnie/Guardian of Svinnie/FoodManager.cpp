// FoodManager.cpp
#include "FoodManager.hpp"
#include <algorithm>
#include <iostream>

// ------------------------------------------------------------
// Konstruktor: speichert Spielfeldinfos, Assets und bereitet den Apfel-Sprite vor
// ------------------------------------------------------------
FoodManager::FoodManager(int cols, int rows, int cellSize, const Assets& assets)
    : m_cols(cols), m_rows(rows), m_cellSize(cellSize), m_assets(assets), m_rng(std::random_device{}())
{
    // Apfel-Textur setzen
    m_appleSprite.setTexture(m_assets.apple());

    // Sprite so skalieren, dass er genau in eine Zelle passt
    m_appleSprite.setScale(
        float(m_cellSize) / m_assets.apple().getSize().x,
        float(m_cellSize) / m_assets.apple().getSize().y
    );
}

// ------------------------------------------------------------
// Initialisiert count Äpfel an zufälligen freien Positionen
// Schlange darf diese Positionen nicht belegen
// ------------------------------------------------------------
void FoodManager::init(int count, const std::deque<Segment>& snake)
{
    m_food.clear();
    for (int i = 0; i < count; ++i)
        m_food.push_back(randomFreePos(snake));
}

// ------------------------------------------------------------
// Wählt eine zufällige freie Position aus
// ------------------------------------------------------------
Segment FoodManager::randomFreePos(const std::deque<Segment>& snake)
{
    std::uniform_int_distribution<int> dx(0, m_cols - 1);
    std::uniform_int_distribution<int> dy(0, m_rows - 1);

    Segment s;
    do {
        // Zufällige Zelle
        s.x = dx(m_rng);
        s.y = dy(m_rng);

        // Wiederholen, solange die Schlange die Zelle belegt
    } while (std::any_of(snake.begin(), snake.end(),
        [&](const Segment& seg) { return seg.x == s.x && seg.y == s.y; }));

    return s;
}

// ------------------------------------------------------------
// Prüft, ob der Kopf der Schlange mit einem Apfel kollidiert
// Gibt den Index des Apfels zurück oder -1
// ------------------------------------------------------------
int FoodManager::checkCollision(const Segment& head) const
{
    for (size_t i = 0; i < m_food.size(); ++i)
        if (m_food[i].x == head.x && m_food[i].y == head.y)
            return int(i);
    return -1;
}

// ------------------------------------------------------------
// Ersetzt den Apfel bei index durch einen neuen an freier Stelle
// ------------------------------------------------------------
void FoodManager::replaceFoodAt(int index, const std::deque<Segment>& snake)
{
    if (index < 0 || index >= (int)m_food.size()) return;
    m_food[index] = randomFreePos(snake);
}

// ------------------------------------------------------------
// Zeichnet alle Äpfel ins Fenster
// ------------------------------------------------------------
void FoodManager::draw(sf::RenderWindow& window) const
{
    for (auto& f : m_food) {
        // Apfel-Sprite an Position setzen
        m_appleSprite.setPosition(f.x * m_cellSize, f.y * m_cellSize);
        window.draw(m_appleSprite);
    }
}
