/*
 * Advanced Connect4 Game Example
 * 
 * This example shows advanced usage:
 * - AI plays first
 * - Custom depth per move
 * - Manual control of game flow
 */

#include <Connect4.h>

Connect4 game;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("=== Advanced Connect 4 Game ===");
  Serial.println("AI plays FIRST with variable depth");
  Serial.println();
  
  // Configure AI to play first
  game.setAIPlayer(Player::FIRST);
  
  // AI makes first move with depth 6
  Serial.println("AI opening move (depth 6)...");
  unsigned long startTime = millis();
  int8_t aiMove = game.calculateBestMove(6);
  unsigned long thinkTime = millis() - startTime;
  
  if (aiMove >= 0) {
    game.playMove(aiMove, Player::FIRST);
    Serial.print("AI played column ");
    Serial.print(aiMove);
    Serial.print(" (");
    Serial.print(thinkTime);
    Serial.println(" ms)");
    game.printBoard();
  }
  
  Serial.println("Your turn! Enter column (0-6):");
}

void loop() {
  if (!game.isGameOver() && Serial.available() > 0) {
    int column = Serial.parseInt();
    
    // Clear buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    if (column >= 0 && column < 7) {
      // Human plays as SECOND
      if (game.playMove(column, Player::SECOND)) {
        Serial.print("You played column ");
        Serial.println(column);
        game.printBoard();
        
        if (game.hasWinner()) {
          Serial.println("*** YOU WIN! ***");
          return;
        }
        if (game.isDraw()) {
          Serial.println("*** DRAW! ***");
          return;
        }
        
        // AI responds with adaptive depth based on game progress
        uint8_t moveCount = game.getBoard().getMoveCount();
        uint8_t depth;
        
        if (moveCount < 10) {
          depth = 5; // Early game: moderate depth
        } else if (moveCount < 30) {
          depth = 7; // Mid game: deeper search
        } else {
          depth = 9; // End game: maximum depth
        }
        
        Serial.print("AI thinking (depth ");
        Serial.print(depth);
        Serial.println(")...");
        
        unsigned long startTime = millis();
        int8_t aiMove = game.calculateBestMove(depth);
        unsigned long thinkTime = millis() - startTime;
        
        if (aiMove >= 0 && game.playMove(aiMove, Player::FIRST)) {
          Serial.print("AI played column ");
          Serial.print(aiMove);
          Serial.print(" (");
          Serial.print(thinkTime);
          Serial.println(" ms)");
          game.printBoard();
          
          if (game.hasWinner()) {
            Serial.println("*** AI WINS! ***");
            return;
          }
          if (game.isDraw()) {
            Serial.println("*** DRAW! ***");
            return;
          }
          
          Serial.println("Your turn:");
        }
      } else {
        Serial.println("Invalid move!");
      }
    } else {
      Serial.println("Invalid input! Enter 0-6");
    }
  }
}
