# Connect4 C++ Library

Une bibliothèque C++ complète pour jouer au Puissance 4 (Connect 4) avec une IA basée sur l'algorithme Minimax avec élagage alpha-beta. Compatible Arduino et PlatformIO.

## 🎯 Caractéristiques

- ✅ **IA avancée** : Algorithme Minimax avec élagage alpha-beta
- ✅ **Profondeur configurable** : Contrôle technique direct (1-12+)
- ✅ **Choix du joueur IA** : L'IA peut jouer en premier ou en second
- ✅ **Optimisé pour Arduino** : Pas d'allocation dynamique, utilisation mémoire optimisée
- ✅ **API flexible** : Contrôle manuel ou assisté
- ✅ **Compatible** : Arduino, ESP32, ESP8266, et C++ standard

## 📦 Installation

### Arduino IDE

1. Téléchargez la bibliothèque
2. Dans Arduino IDE : `Sketch` → `Include Library` → `Add .ZIP Library`
3. Sélectionnez le fichier ZIP téléchargé

### PlatformIO

Ajoutez dans votre `platformio.ini` :

```ini
lib_deps =
    https://github.com/yourusername/connect4-cpp.git
```

## 🚀 Utilisation rapide

```cpp
#include <Connect4.h>

Connect4 game;

void setup() {
    // Configuration de la profondeur de recherche (1-12+)
    game.setSearchDepth(5);

    // Choix du joueur IA (FIRST ou SECOND)
    game.setAIPlayer(Player::SECOND);
}

void loop() {
    // Tour humain
    if (game.playHumanMove(3)) {  // Joue colonne 3
        // Coup valide
    }

    // Tour IA
    game.playAIMove();  // Utilise la profondeur configurée

    // Vérifier l'état du jeu
    if (game.hasWinner()) {
        Player winner = game.getWinner();
        // Gérer la victoire
    }
}
```

## 🎮 API Principale

### Configuration

```cpp
// Définir la profondeur de recherche Minimax (valeur numérique directe)
game.setSearchDepth(6);  // 1-12+ selon la puissance du microcontrôleur

// Choisir qui est l'IA
game.setAIPlayer(Player::FIRST);   // IA commence
game.setAIPlayer(Player::SECOND);  // Humain commence
```

### Contrôle du jeu

```cpp
// Jouer un coup (contrôle manuel)
game.playMove(column, Player::FIRST);

// Méthodes assistées
game.playHumanMove(column);  // Joue pour l'humain
game.playAIMove();           // IA joue avec profondeur configurée
game.playAIMove(depth);      // IA joue avec profondeur personnalisée

// Calculer le meilleur coup sans jouer
int8_t bestMove = game.calculateBestMove();
int8_t bestMove = game.calculateBestMove(7);  // Profondeur custom
```

### État du jeu

```cpp
// Vérifications
if (game.hasWinner()) { /* ... */ }
if (game.isDraw()) { /* ... */ }
if (game.isGameOver()) { /* ... */ }
if (game.isValidMove(column)) { /* ... */ }

// Informations
Player winner = game.getWinner();
Player cell = game.getCell(row, col);
GameState state = game.getGameState();

// Réinitialiser
game.reset();
```

## 📊 Recommandations de profondeur

| Plateforme   | Profondeur recommandée | Temps de calcul |
| ------------ | ---------------------- | --------------- |
| Arduino Uno  | 3-4                    | 1-5 secondes    |
| Arduino Mega | 4-5                    | 0.5-3 secondes  |
| ESP32        | 5-7                    | 0.1-2 secondes  |
| ESP8266      | 4-6                    | 0.2-3 secondes  |
| PC/Desktop   | 7-12                   | <1 seconde      |

**Note** : Plus la profondeur est élevée, plus l'IA est forte mais plus le calcul est long.

## 💡 Exemples

### Exemple 1 : Jeu basique

```cpp
#include <Connect4.h>

Connect4 game;

void setup() {
    Serial.begin(115200);
    game.setAIPlayer(Player::SECOND);
    game.setSearchDepth(5);
}

void loop() {
    // Lire l'entrée utilisateur via Serial
    if (Serial.available()) {
        int col = Serial.parseInt();

        if (game.playHumanMove(col)) {
            game.printBoard();

            if (!game.isGameOver()) {
                game.playAIMove();
                game.printBoard();
            }
        }
    }
}
```

### Exemple 2 : Contrôle avancé

```cpp
Connect4 game;

// L'IA joue en premier avec profondeur 6
game.setAIPlayer(Player::FIRST);
int8_t aiMove = game.calculateBestMove(6);
game.playMove(aiMove, Player::FIRST);

// Humain joue
game.playMove(3, Player::SECOND);

// IA répond avec profondeur adaptative
uint8_t moveCount = game.getBoard().getMoveCount();
uint8_t depth = (moveCount < 20) ? 5 : 8;  // Plus profond en fin de partie
game.playAIMove(depth);
```

### Exemple 3 : Mode deux joueurs (sans IA)

```cpp
Connect4 game;

// Joueur 1
game.playMove(column, Player::FIRST);

// Joueur 2
game.playMove(column, Player::SECOND);
```

## 🔧 Architecture

```
Connect4Board    → Logique du plateau, détection victoires
Connect4AI       → Algorithme Minimax avec alpha-beta
Connect4         → API principale, interface facile
```

## 📝 Détails techniques

- **Algorithme** : Minimax avec élagage alpha-beta
- **Évaluation** : Heuristique basée sur les alignements et position centrale
- **Optimisation** : Ordre des coups du centre vers l'extérieur
- **Mémoire** : Pas d'allocation dynamique, tableaux statiques
- **Compatibilité** : C++11 minimum

## 🎯 Types et énumérations

```cpp
enum class Player : uint8_t {
    NONE = 0,
    FIRST = 1,
    SECOND = 2
};

enum class GameState : uint8_t {
    IN_PROGRESS,
    FIRST_WINS,
    SECOND_WINS,
    DRAW
};
```

## 📄 Licence

Ce projet est sous licence MIT - voir le fichier LICENSE pour plus de détails.

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou une pull request.

## 👤 Auteur

Clement

## 🔗 Liens utiles

- [Documentation Arduino](https://www.arduino.cc/)
- [PlatformIO](https://platformio.org/)
- [Algorithme Minimax](https://en.wikipedia.org/wiki/Minimax)
