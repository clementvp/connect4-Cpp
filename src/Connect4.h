#ifndef CONNECT4_H
#define CONNECT4_H

#include "Connect4Board.h"
#include "Connect4AI.h"

class Connect4 {
private:
    Connect4Board board;
    Connect4AI ai;
    uint8_t searchDepth;
    Player aiPlayer;
    Player currentPlayer;
    int8_t lastAIMove;  // Stores the last AI move (-1 if none)

public:
    // Constructor
    Connect4();

    // Configuration methods
    void setSearchDepth(uint8_t depth);
    uint8_t getSearchDepth() const;
    
    void setAIPlayer(Player player);
    Player getAIPlayer() const;
    
    // Game control methods
    void reset();
    bool playMove(uint8_t column, Player player);
    
    // AI calculation methods
    int8_t calculateBestMove(uint8_t depth);  // Calculate with custom depth
    int8_t calculateBestMove();               // Calculate with configured depth
    
    // Helper methods for simplified usage
    bool playHumanMove(uint8_t column);          // Internal: column 0-6
    bool playHumanMoveUser(uint8_t column);      // User-facing: column 1-7
    bool playAIMove();
    bool playAIMove(uint8_t depth);
    
    // Game state queries
    bool isValidMove(uint8_t column) const;
    bool hasWinner() const;
    Player getWinner() const;
    bool isDraw() const;
    bool isGameOver() const;
    GameState getGameState() const;
    
    // Board access
    const Connect4Board& getBoard() const;
    Player getCell(uint8_t row, uint8_t col) const;
    uint8_t getColumnHeight(uint8_t col) const;
    
    // Turn management
    Player getCurrentPlayer() const;
    void setCurrentPlayer(Player player);
    Player getOpponent(Player player) const;
    
    // Display helper (optional, for debugging)
    void printBoard() const;
    
    // AI move information
    int8_t getLastAIMove() const;           // Internal: Get last AI move 0-6 (-1 if none)
    int8_t getLastAIMoveUser() const;       // User-facing: Get last AI move 1-7 (0 if none)
    void printAIMove(uint8_t column) const; // Print AI move information (internal 0-6)
};

#endif // CONNECT4_H
