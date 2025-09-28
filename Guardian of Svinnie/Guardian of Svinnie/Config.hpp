// Config.hpp
#pragma once

// Fensterbreite in Pixeln
constexpr int WINDOW_WIDTH = 1024;

// Fensterh�he in Pixeln
constexpr int WINDOW_HEIGHT = 1024;

// Gr��e einer Spielfeldzelle in Pixeln
constexpr int CELL_SIZE = 64;

// Anzahl Spalten im Spielfeld (abh�ngig von Fensterbreite und Zellgr��e)
constexpr int COLS = WINDOW_WIDTH / CELL_SIZE;

// Anzahl Reihen im Spielfeld (abh�ngig von Fensterh�he und Zellgr��e)
constexpr int ROWS = WINDOW_HEIGHT / CELL_SIZE;
