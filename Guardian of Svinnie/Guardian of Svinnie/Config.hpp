// Config.hpp
#pragma once

// Fensterbreite in Pixeln
constexpr int WINDOW_WIDTH = 1024;

// Fensterhöhe in Pixeln
constexpr int WINDOW_HEIGHT = 1024;

// Größe einer Spielfeldzelle in Pixeln
constexpr int CELL_SIZE = 64;

// Anzahl Spalten im Spielfeld (abhängig von Fensterbreite und Zellgröße)
constexpr int COLS = WINDOW_WIDTH / CELL_SIZE;

// Anzahl Reihen im Spielfeld (abhängig von Fensterhöhe und Zellgröße)
constexpr int ROWS = WINDOW_HEIGHT / CELL_SIZE;
