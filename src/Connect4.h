#ifndef CONNECT4_H
#define CONNECT4_H

#include "Connect4Board.h"
#include "Connect4AI.h"

class Connect4 {
private:
    Connect4Board board;
    Connect4AI ai;  // Used for calculateBestMove
    
    // Internal method using 0-6 indexing
    bool playMoveInternal(uint8_t column, Player player);

public:
    // Constructor
    Connect4();

    // Game control methods
    void reset();
    bool playMove(uint8_t column, Player player);  // User-facing: column 1-7
    
    // AI calculation method (returns 1-7, or 0 if no valid move)
    uint8_t calculateBestMove(Player player, uint8_t depth);
    
    // Game state queries
    bool isValidMove(uint8_t column) const;  // Takes column 1-7
    bool hasWinner() const;
    Player getWinner() const;
    bool isDraw() const;
    bool isGameOver() const;
    GameState getGameState() const;
    
    // Board access
    const Connect4Board& getBoard() const;
    Player getCell(uint8_t row, uint8_t col) const;
    uint8_t getColumnHeight(uint8_t col) const;
    
    // Utility methods
    Player getOpponent(Player player) const;
    void printBoard() const;
};

#endif // CONNECT4_H
