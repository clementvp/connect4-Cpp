# Connect4 C++ Library

Une bibliothèque C++ complète pour jouer au Puissance 4 (Connect 4) avec support optionnel de l'IA basée sur l'algorithme Minimax avec élagage alpha-beta. Compatible Arduino et PlatformIO.

## 🎯 Caractéristiques

- ✅ **Mode 2 joueurs** : Jouez à deux sans IA
- ✅ **IA optionnelle** : Utilisez l'algorithme Minimax avec élagage alpha-beta si nécessaire
- ✅ **API simple et flexible** : Contrôle total du jeu
- ✅ **Pas de couplage** : Le moteur de jeu est indépendant de l'IA
- ✅ **Optimisé pour Arduino** : Pas d'allocation dynamique, utilisation mémoire optimisée
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
    https://github.com/clementvp/connect4-cpp.git
```

## 🚀 Utilisation rapide

### Mode 2 joueurs (sans IA)

```cpp
#include <Connect4.h>

Connect4 game;
Player currentPlayer = Player::FIRST;

void setup() {
    Serial.begin(115200);
    game.printBoard();
}

void loop() {
    if (Serial.available()) {
        int column = Serial.parseInt();  // Utilisateur entre 1-7

        if (game.playMove(column, currentPlayer)) {
            game.printBoard();

            if (game.hasWinner()) {
                // Gérer la victoire
            }

            // Alterner les joueurs
            currentPlayer = game.getOpponent(currentPlayer);
        }
    }
}
```

### Mode avec IA (optionnel)

```cpp
#include <Connect4.h>

Connect4 game;
const uint8_t AI_DEPTH = 6;

void loop() {
    // Tour humain (Player 1)
    if (Serial.available()) {
        int column = Serial.parseInt();  // Utilisateur entre 1-7
        game.playMove(column, Player::FIRST);
        game.printBoard();

        if (!game.isGameOver()) {
            // Tour IA (Player 2)
            uint8_t aiMove = game.calculateBestMove(Player::SECOND, AI_DEPTH);
            if (aiMove > 0) {  // 0 = erreur, 1-7 = coup valide
                game.playMove(aiMove, Player::SECOND);
                game.printBoard();
            }
        }
    }
}
```

## 📖 Référence de l'API

### Contrôle du jeu

#### `reset()`

**Description** : Réinitialise complètement la partie.  
**Paramètres** : Aucun  
**Retour** : Aucun (void)  
**Exemple** :

```cpp
game.reset();  // Nouvelle partie
```

#### `playMove(uint8_t column, Player player)`

**Description** : Joue un coup pour un joueur spécifique avec indexation utilisateur (colonnes 1-7). **L'utilisateur contrôle l'alternance des tours.**  
**Paramètres** :

- `column` (uint8_t) : Numéro de colonne (1-7)
- `player` (Player) : Le joueur qui joue (`Player::FIRST` ou `Player::SECOND`)

**Retour** : `bool` - `true` si le coup est valide et joué, `false` sinon  
**Exemple** :

```cpp
// Joueur 1 joue dans la colonne 3
game.playMove(3, Player::FIRST);

// Joueur 2 joue dans la colonne 4
game.playMove(4, Player::SECOND);

// Lecture de l'entrée utilisateur (1-7)
int userInput = Serial.parseInt();
game.playMove(userInput, Player::FIRST);
```

---

### Calcul IA (optionnel)

#### `calculateBestMove(Player player, uint8_t depth)`

**Description** : Calcule le meilleur coup pour un joueur donné avec une profondeur de recherche spécifiée. **N'effectue pas le coup, juste le calcul.**  
**Paramètres** :

- `player` (Player) : Le joueur pour lequel calculer (`Player::FIRST` ou `Player::SECOND`)
- `depth` (uint8_t) : Profondeur de recherche Minimax (1-12+)

**Retour** : `uint8_t` - Numéro de colonne du meilleur coup (1-7), ou 0 si aucun coup valide  
**Exemple** :

```cpp
// Calculer le meilleur coup pour le joueur 2 avec profondeur 6
uint8_t bestMove = game.calculateBestMove(Player::SECOND, 6);
if (bestMove > 0) {  // 0 = erreur, 1-7 = coup valide
    game.playMove(bestMove, Player::SECOND);
}

// Profondeur adaptative
uint8_t moveCount = game.getBoard().getMoveCount();
uint8_t depth = (moveCount < 20) ? 5 : 8;  // Plus profond en fin de partie
uint8_t move = game.calculateBestMove(Player::FIRST, depth);
if (move > 0) {
    game.playMove(move, Player::FIRST);
}
```

---

### État du jeu

#### `isValidMove(uint8_t column)`

**Description** : Vérifie si un coup dans une colonne donnée est valide.  
**Paramètres** :

- `column` (uint8_t) : Numéro de colonne (1-7)

**Retour** : `bool`  
**Exemple** :

```cpp
if (game.isValidMove(3)) {
    game.playMove(3, Player::FIRST);
}
```

#### `hasWinner()`

**Description** : Vérifie s'il y a un gagnant.  
**Retour** : `bool`  
**Exemple** :

```cpp
if (game.hasWinner()) {
    Player winner = game.getWinner();
}
```

#### `getWinner()`

**Description** : Retourne le joueur gagnant.  
**Retour** : `Player` - `Player::FIRST`, `Player::SECOND`, ou `Player::NONE`

#### `isDraw()`

**Description** : Vérifie si la partie est un match nul.  
**Retour** : `bool`

#### `isGameOver()`

**Description** : Vérifie si la partie est terminée.  
**Retour** : `bool`

#### `getGameState()`

**Description** : Retourne l'état complet du jeu.  
**Retour** : `GameState` - `IN_PROGRESS`, `FIRST_WINS`, `SECOND_WINS`, ou `DRAW`

---

### Accès au plateau

#### `getBoard()`

**Description** : Retourne une référence au plateau de jeu.  
**Retour** : `const Connect4Board&`  
**Exemple** :

```cpp
const Connect4Board& board = game.getBoard();
uint8_t moveCount = board.getMoveCount();
```

#### `getCell(uint8_t row, uint8_t col)`

**Description** : Retourne le contenu d'une cellule.  
**Paramètres** :

- `row` (uint8_t) : Ligne (0-5)
- `col` (uint8_t) : Colonne (0-6)

**Retour** : `Player`

#### `getColumnHeight(uint8_t col)`

**Description** : Retourne le nombre de pions dans une colonne.  
**Paramètres** :

- `col` (uint8_t) : Colonne (0-6)

**Retour** : `uint8_t`

---

### Utilitaires

#### `getOpponent(Player player)`

**Description** : Retourne l'adversaire d'un joueur.  
**Retour** : `Player`  
**Exemple** :

```cpp
currentPlayer = game.getOpponent(currentPlayer);
```

#### `printBoard()`

**Description** : Affiche le plateau via Serial (pour débogage).  
**Exemple** :

```cpp
game.printBoard();
```

---

## 📊 Recommandations de profondeur IA

| Plateforme   | Profondeur recommandée | Temps de calcul |
| ------------ | ---------------------- | --------------- |
| Arduino Uno  | 3-4                    | 1-5 secondes    |
| Arduino Mega | 4-5                    | 0.5-3 secondes  |
| ESP32        | 5-7                    | 0.1-2 secondes  |
| ESP8266      | 4-6                    | 0.2-3 secondes  |
| PC/Desktop   | 7-12                   | <1 seconde      |

**Note** : Plus la profondeur est élevée, plus l'IA est forte mais plus le calcul est long.

## 💡 Exemples complets

Des exemples complets et fonctionnels sont disponibles dans le dossier `examples/` :

- **[BasicGame](examples/BasicGame/)** : Jeu à 2 joueurs avec gestion complète des entrées et affichage
- **[AIFirstGame](examples/AIFirstGame/)** : Jeu contre l'IA avec profondeur configurable et mesure du temps de calcul

Consultez ces fichiers pour voir l'implémentation détaillée avec gestion d'erreurs, affichage formaté et logique de jeu complète.

## 🔧 Architecture

```
Connect4Board    → Logique du plateau, détection victoires
Connect4AI       → Algorithme Minimax (optionnel)
Connect4         → API principale (moteur de jeu pur)
```

## 📝 Détails techniques

- **Algorithme IA** : Minimax avec élagage alpha-beta
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

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou une pull request.

## 👤 Auteur

Clement

## 🔗 Liens utiles

- [Documentation Arduino](https://www.arduino.cc/)
- [PlatformIO](https://platformio.org/)
- [Algorithme Minimax](https://en.wikipedia.org/wiki/Minimax)
