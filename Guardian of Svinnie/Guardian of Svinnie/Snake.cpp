// Snake.cpp
#include "Snake.hpp"
#include <algorithm>

// ------------------------------------------------------------
// Konstruktor
// Setzt Startposition, Richtung und legt die Texturen fest.
// ------------------------------------------------------------
Snake::Snake(int startX, int startY, int cellSize, const Assets& assets)
    : m_dir(Right), m_cellSize(cellSize), m_assets(assets)
{
    // Schlange startet mit einem Segment in der Mitte
    m_body.push_back({ startX, startY });

    // Texturen für Körper und Kopf setzen
    m_bodySprite.setTexture(m_assets.segment());
    m_headSprite.setTexture(m_assets.headRight()); // Start: nach rechts

    // Sprites skalieren, sodass sie genau in eine Zelle passen
    m_bodySprite.setScale(
        (m_cellSize * m_overlap) / float(m_assets.segment().getSize().x),
        (m_cellSize * m_overlap) / float(m_assets.segment().getSize().y)
    );

    m_headSprite.setScale(
        (m_cellSize * m_overlap) / float(m_assets.headRight().getSize().x),
        (m_cellSize * m_overlap) / float(m_assets.headRight().getSize().y)
    );
}

// ------------------------------------------------------------
// Kopf zurückgeben
// ------------------------------------------------------------
Segment Snake::getHead() const { return m_body.front(); }

// ------------------------------------------------------------
// Nächsten Kopf berechnen je nach Bewegungsrichtung
// ------------------------------------------------------------
Segment Snake::getNextHead() const
{
    Segment h = getHead();
    switch (m_dir) {
    case Up:    h.y--; break;
    case Down:  h.y++; break;
    case Left:  h.x--; break;
    case Right: h.x++; break;
    }
    return h;
}

// ------------------------------------------------------------
// Richtung ändern (180° Wendungen sind verboten)
// ------------------------------------------------------------
void Snake::setDirection(Direction d)
{
    // nicht direkt umdrehen (z.B. von Links nach Rechts)
    if ((m_dir == Up && d == Down) || (m_dir == Down && d == Up) ||
        (m_dir == Left && d == Right) || (m_dir == Right && d == Left))
        return;
    m_dir = d;
}

Direction Snake::getDirection() const { return m_dir; }

// ------------------------------------------------------------
// Neuen Kopf hinzufügen
// ------------------------------------------------------------
void Snake::pushHead(const Segment& s) { m_body.push_front(s); }

// ------------------------------------------------------------
// Schwanz entfernen (wenn kein Apfel gefressen wurde)
// ------------------------------------------------------------
void Snake::popTail() { if (!m_body.empty()) m_body.pop_back(); }

// ------------------------------------------------------------
// Prüfen, ob Schlange ein bestimmtes Feld besetzt
// (wird für FoodManager gebraucht)
// ------------------------------------------------------------
bool Snake::occupies(int x, int y) const
{
    for (auto& s : m_body)
        if (s.x == x && s.y == y) return true;
    return false;
}

// ------------------------------------------------------------
// Prüfen, ob Schlange mit sich selbst kollidiert
// ------------------------------------------------------------
bool Snake::checkSelfCollision(const Segment& head) const
{
    for (auto& s : m_body)
        if (s.x == head.x && s.y == head.y) return true;
    return false;
}

// ------------------------------------------------------------
// Schlange zeichnen
// Kopf wird mit passender Textur gezeichnet,
// Rest sind Körper-Sprites
// ------------------------------------------------------------
void Snake::draw(sf::RenderWindow& window) const
{
    for (size_t i = 0; i < m_body.size(); ++i) {
        sf::Vector2f pos(m_body[i].x * m_cellSize, m_body[i].y * m_cellSize);
        if (i == 0) {
            // Kopf je nach Richtung andere Textur
            switch (m_dir) {
            case Up:    m_headSprite.setTexture(m_assets.headUp()); break;
            case Down:  m_headSprite.setTexture(m_assets.headDown()); break;
            case Left:  m_headSprite.setTexture(m_assets.headLeft()); break;
            case Right: m_headSprite.setTexture(m_assets.headRight()); break;
            }
            m_headSprite.setPosition(pos);
            window.draw(m_headSprite);
        }
        else {
            // Körpersegment
            m_bodySprite.setPosition(pos);
            window.draw(m_bodySprite);
        }
    }
}
