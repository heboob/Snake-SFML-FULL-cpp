// Snake.hpp
#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
#include "Assets.hpp"

// ------------------------------------------------------------
// Datenstruktur f�r ein Segment (Teil) der Schlange.
// Enth�lt die Position in Zellen-Koordinaten (x,y).
// ------------------------------------------------------------
struct Segment {
    int x, y;
};

// ------------------------------------------------------------
// Bewegungsrichtungen der Schlange
// ------------------------------------------------------------
enum Direction { Up, Down, Left, Right };

// ------------------------------------------------------------
// Snake-Klasse:
// Verwaltet den K�rper der Schlange, ihre Bewegungen,
// Kollisionen und das Zeichnen auf das Fenster.
// ------------------------------------------------------------
class Snake {
public:
    // Konstruktor: setzt Startposition, Zellengr��e und l�dt Texturen
    Snake(int startX, int startY, int cellSize, const Assets& assets);

    // Gibt den aktuellen Kopf der Schlange zur�ck
    Segment getHead() const;

    // Berechnet, wo der n�chste Kopf sein wird, wenn man sich bewegt
    Segment getNextHead() const;

    // Richtung �ndern (z.B. durch Tastendruck)
    void setDirection(Direction d);

    // Aktuelle Richtung auslesen
    Direction getDirection() const;

    // Kopf an der Position s hinzuf�gen
    void pushHead(const Segment& s);

    // Letztes Segment (Schwanz) entfernen
    void popTail();

    // Pr�fen, ob Schlange ein Feld besetzt (f�r Food)
    bool occupies(int x, int y) const;

    // Pr�fen, ob Schlange in sich selbst bei�t (Kollision)
    bool checkSelfCollision(const Segment& head) const;

    // Schlange im Fenster zeichnen
    void draw(sf::RenderWindow& window) const;

    // Zugriff auf den K�rper (f�r FoodManager)
    const std::deque<Segment>& body() const { return m_body; }

private:
    std::deque<Segment> m_body;   // Segmente der Schlange (erstes = Kopf)
    Direction m_dir;              // aktuelle Bewegungsrichtung
    int m_cellSize;               // Gr��e einer Zelle in Pixeln
    const Assets& m_assets;       // Referenz auf Assets (Texturen)

    // Sprites f�r Kopf und K�rper
    mutable sf::Sprite m_bodySprite;
    mutable sf::Sprite m_headSprite;

    // �berschneidungsfaktor (verhindert L�cken zwischen Segmenten)
    const float m_overlap = 1.0f;
};
