// Snake.hpp
#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
#include "Assets.hpp"

// ------------------------------------------------------------
// Datenstruktur für ein Segment (Teil) der Schlange.
// Enthält die Position in Zellen-Koordinaten (x,y).
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
// Verwaltet den Körper der Schlange, ihre Bewegungen,
// Kollisionen und das Zeichnen auf das Fenster.
// ------------------------------------------------------------
class Snake {
public:
    // Konstruktor: setzt Startposition, Zellengröße und lädt Texturen
    Snake(int startX, int startY, int cellSize, const Assets& assets);

    // Gibt den aktuellen Kopf der Schlange zurück
    Segment getHead() const;

    // Berechnet, wo der nächste Kopf sein wird, wenn man sich bewegt
    Segment getNextHead() const;

    // Richtung ändern (z.B. durch Tastendruck)
    void setDirection(Direction d);

    // Aktuelle Richtung auslesen
    Direction getDirection() const;

    // Kopf an der Position s hinzufügen
    void pushHead(const Segment& s);

    // Letztes Segment (Schwanz) entfernen
    void popTail();

    // Prüfen, ob Schlange ein Feld besetzt (für Food)
    bool occupies(int x, int y) const;

    // Prüfen, ob Schlange in sich selbst beißt (Kollision)
    bool checkSelfCollision(const Segment& head) const;

    // Schlange im Fenster zeichnen
    void draw(sf::RenderWindow& window) const;

    // Zugriff auf den Körper (für FoodManager)
    const std::deque<Segment>& body() const { return m_body; }

private:
    std::deque<Segment> m_body;   // Segmente der Schlange (erstes = Kopf)
    Direction m_dir;              // aktuelle Bewegungsrichtung
    int m_cellSize;               // Größe einer Zelle in Pixeln
    const Assets& m_assets;       // Referenz auf Assets (Texturen)

    // Sprites für Kopf und Körper
    mutable sf::Sprite m_bodySprite;
    mutable sf::Sprite m_headSprite;

    // Überschneidungsfaktor (verhindert Lücken zwischen Segmenten)
    const float m_overlap = 1.0f;
};
