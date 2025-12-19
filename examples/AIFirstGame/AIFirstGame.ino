/*
 * AI First Connect4 Game Example
 * 
 * This example demonstrates a basic game where AI plays first.
 * 
 * Usage via Serial Monitor:
 * - AI makes the first move
 * - Enter column number (1-7) to respond
 * - AI will counter automatically
 */

#include <Connect4.h>

Connect4 game;
bool firstMove = true;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("=== Connect 4 Game - AI Plays First ===");
  Serial.println();
  
  // Configuration: AI plays FIRST, depth 5
  game.setAIPlayer(Player::FIRST);
  game.setSearchDepth(5);
  
  Serial.print("AI is Player: FIRST (X)");
  Serial.println();
  Serial.print("Search Depth: ");
  Serial.println(game.getSearchDepth());
  Serial.println();
  
  // AI makes first move
  Serial.println("AI is thinking...");
  unsigned long startTime = millis();
  
  if (game.playAIMove()) {
    unsigned long thinkTime = millis() - startTime;
    game.printAIMove(game.getLastAIMove());
    Serial.print("(");
    Serial.print(thinkTime);
    Serial.println(" ms)");
    game.printBoard();
  }
  
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
      // Human move (using user-facing method with columns 1-7)
      if (game.playHumanMoveUser(column)) {
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
          game.printAIMove(game.getLastAIMove());
          Serial.print("(");
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
        Serial.println("Invalid move! Try another column.");
      }
    } else {
      Serial.println("Invalid input! Enter 1-7");
    }
  }
}
