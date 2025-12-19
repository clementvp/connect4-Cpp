#ifndef CONNECT4_AI_H
#define CONNECT4_AI_H

#include "Connect4Board.h"
#include <stdint.h>

class Connect4AI {
private:
    // Evaluation constants
    static constexpr int32_t WIN_SCORE = 100000;
    static constexpr int32_t THREE_SCORE = 100;
    static constexpr int32_t TWO_SCORE = 10;
    static constexpr int32_t CENTER_SCORE = 3;

    // Evaluate a window of 4 cells
    int32_t evaluateWindow(Player p1, Player p2, Player p3, Player p4, Player player) const;
    
    // Evaluate the entire board position
    int32_t evaluateBoard(const Connect4Board& board, Player player) const;
    
    // Minimax with alpha-beta pruning
    int32_t minimax(Connect4Board& board, uint8_t depth, int32_t alpha, int32_t beta, 
                   bool maximizing, Player aiPlayer) const;

public:
    Connect4AI() = default;

    // Calculate the best move for the given player at specified depth
    // Returns the column number (0-6) or -1 if no valid move
    int8_t calculateBestMove(Connect4Board& board, Player player, uint8_t depth) const;
};

#endif // CONNECT4_AI_H
