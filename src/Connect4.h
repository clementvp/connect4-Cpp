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
    bool playHumanMove(uint8_t column);
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
};

#endif // CONNECT4_H
