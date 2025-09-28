// main.cpp
#include "Game.hpp"

// ------------------------------------------------------------
// Einstiegspunkt des Programms
// ------------------------------------------------------------
int main()
{
    // Erstellt eine Instanz des Spiels
    Game game;

    // Startet die Hauptschleife (run() verwaltet die Zustände)
    game.run();

    // Wenn das Fenster geschlossen wird, beendet sich das Programm
    return 0;
}
