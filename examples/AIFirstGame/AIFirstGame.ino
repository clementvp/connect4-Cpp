/*
 * Connect4 Game with AI Example
 * 
 * This example demonstrates how to use the AI functionality
 * to play against the computer.
 * 
 * - AI plays as Player 2 (O)
 * - Human plays as Player 1 (X)
 * - AI uses Minimax algorithm with configurable depth
 * 
 * Usage via Serial Monitor:
 * - Enter column number (1-7) to play
 * - AI will respond automatically
 */

#include <Connect4.h>

Connect4 game;

// Configuration
const uint8_t AI_DEPTH = 6;  // AI search depth (higher = stronger but slower)
const Player AI_PLAYER = Player::SECOND;
const Player HUMAN_PLAYER = Player::FIRST;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("=== Connect 4 - Play vs AI ===");
  Serial.println();
  Serial.println("You are Player 1 (X)");
  Serial.println("AI is Player 2 (O)");
  Serial.print("AI Depth: ");
  Serial.println(AI_DEPTH);
  Serial.println();
  
  game.printBoard();
  Serial.println("Your turn! Enter column (1-7):");
}

void loop() {
  if (!game.isGameOver() && Serial.available() > 0) {
    int column = Serial.parseInt();
    
    // Clear serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    if (column >= 1 && column <= 7) {
      // Human move
      if (game.playMove(column, HUMAN_PLAYER)) {
        Serial.print("You played column ");
        Serial.println(column);
        game.printBoard();
        
        // Check game state after human move
        if (game.hasWinner()) {
          Serial.println("*** YOU WIN! ***");
          Serial.println("Reset Arduino to play again");
          return;
        }
        if (game.isDraw()) {
          Serial.println("*** DRAW! ***");
          Serial.println("Reset Arduino to play again");
          return;
        }
        
        // AI move
        Serial.println("AI is thinking...");
        unsigned long startTime = millis();
        
        uint8_t bestMove = game.calculateBestMove(AI_PLAYER, AI_DEPTH);
        
        if (bestMove > 0 && game.playMove(bestMove, AI_PLAYER)) {
          unsigned long thinkTime = millis() - startTime;
          
          Serial.print("AI played column ");
          Serial.print(bestMove);  // Already in 1-7 format
          Serial.print(" (");
          Serial.print(thinkTime);
          Serial.println(" ms)");
          game.printBoard();
          
          // Check game state after AI move
          if (game.hasWinner()) {
            Serial.println("*** AI WINS! ***");
            Serial.println("Reset Arduino to play again");
            return;
          }
          if (game.isDraw()) {
            Serial.println("*** DRAW! ***");
            Serial.println("Reset Arduino to play again");
            return;
          }
          
          Serial.println("Your turn! Enter column (1-7):");
        }
      } else {
        Serial.println("Invalid move! Column is full or invalid. Try another column.");
      }
    } else {
      Serial.println("Invalid input! Enter a number between 1-7");
    }
  }
}
