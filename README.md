# Snake-SFML-FULL-cpp

## 🎮 Gameplay

- Control a snake on a grid-based map.
- Collect apples to grow longer and score points.
- Avoid colliding with the walls or with yourself.
- When the snake dies, a **Game Over screen** appears with a retry button and a score display.

---

## 🕹️ Controls

| Key | Action       |
|-----|--------------|
| `W` | Move Up      |
| `S` | Move Down    |
| `A` | Move Left    |
| `D` | Move Right   |
| `Mouse` | Click on "Retry" button after Game Over |

---

## ✨ Features

- **Start screen** with title, music, and animated "Press a key" text.
- **Background music** in the menu and during gameplay.
- **Sound effect** when the game is over.
- **Apples** spawn at random free positions, avoiding the snake’s body.
- **Score system**: points increase each time an apple is eaten.
- **Retry button** on the Game Over screen to restart the game.
⚔️ To Summon the Game

### Requirements
- C++17 or higher
- [SFML 2.5+](https://www.sfml-dev.org/) (Graphics, Audio, Window)

### Ritual on Windows (Visual Studio)
1. Open the ancient scroll: `Guardian of Svinnie.vcxproj`.  
2. Bind the **SFML libraries** into your project.  
3. Place all relics (`.png`, `.ogg`, `.ttf`) beside the executable.  
4. Build. Run. Survive.  

### Ritual on Linux / macOS
```bash
sudo apt-get install libsfml-dev  # summon the SFML libraries

g++ -std=c++17 -Iinclude -o snake \
    main.cpp Game.cpp Snake.cpp FoodManager.cpp Assets.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
