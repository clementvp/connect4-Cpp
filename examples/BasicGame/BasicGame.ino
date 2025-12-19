/*
 * Basic Connect4 Game Example
 * 
 * This example demonstrates how to use the Connect4 library
 * with configurable AI depth and player settings.
 * 
 * Usage via Serial Monitor:
 * - Enter column number (0-6) to play
 * - AI will respond automatically
 */

#include <Connect4.h>

Connect4 game;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("=== Connect 4 Game ===");
  Serial.println();
  
  // Configuration: AI plays second, depth 5
  game.setAIPlayer(Player::SECOND);
  game.setSearchDepth(5);
  
  Serial.print("AI is Player: ");
  Serial.println(game.getAIPlayer() == Player::FIRST ? "FIRST (X)" : "SECOND (O)");
  Serial.print("Search Depth: ");
  Serial.println(game.getSearchDepth());
  Serial.println();
  
  game.printBoard();
  Serial.println("Enter column (0-6) to play:");
}

void loop() {
  if (!game.isGameOver() && Serial.available() > 0) {
    int column = Serial.parseInt();
    
    // Clear serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    if (column >= 0 && column < 7) {
      // Human move
      if (game.playHumanMove(column)) {
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
        
        if (game.playAIMove()) {
          unsigned long thinkTime = millis() - startTime;
          Serial.print("AI played (");
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
          
          Serial.println("Your turn! Enter column (0-6):");
        }
      } else {
        Serial.println("Invalid move! Try another column.");
      }
    } else {
      Serial.println("Invalid input! Enter 0-6");
    }
  }
}
