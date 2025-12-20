/*
 * Basic Connect4 Game Example - Two Players
 * 
 * This example demonstrates the basic two-player mode.
 * Players take turns entering columns to play.
 * 
 * Usage via Serial Monitor:
 * - Player 1 (X): Enter column number (1-7) to play
 * - Player 2 (O): Enter column number (1-7) to play
 * - Game alternates between players
 */

#include <Connect4.h>

Connect4 game;
Player currentPlayer = Player::FIRST;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("=== Connect 4 - Two Player Game ===");
  Serial.println();
  Serial.println("Player 1: X");
  Serial.println("Player 2: O");
  Serial.println();
  
  game.printBoard();
  Serial.println("Player 1 (X) - Enter column (1-7):");
}

void loop() {
  if (!game.isGameOver() && Serial.available() > 0) {
    int column = Serial.parseInt();
    
    // Clear serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    if (column >= 1 && column <= 7) {
      // Play move for current player
      if (game.playMove(column, currentPlayer)) {
        Serial.print("Player ");
        Serial.print(currentPlayer == Player::FIRST ? "1" : "2");
        Serial.print(" played column ");
        Serial.println(column);
        game.printBoard();
        
        // Check game state
        if (game.hasWinner()) {
          Serial.print("*** PLAYER ");
          Serial.print(currentPlayer == Player::FIRST ? "1" : "2");
          Serial.println(" WINS! ***");
          Serial.println("Reset Arduino to play again");
          return;
        }
        
        if (game.isDraw()) {
          Serial.println("*** DRAW! ***");
          Serial.println("Reset Arduino to play again");
          return;
        }
        
        // Switch to next player
        currentPlayer = game.getOpponent(currentPlayer);
        
        Serial.print("Player ");
        Serial.print(currentPlayer == Player::FIRST ? "1" : "2");
        Serial.print(" (");
        Serial.print(currentPlayer == Player::FIRST ? "X" : "O");
        Serial.println(") - Enter column (1-7):");
      } else {
        Serial.println("Invalid move! Column is full or invalid. Try another column.");
      }
    } else {
      Serial.println("Invalid input! Enter a number between 1-7");
    }
  }
}
