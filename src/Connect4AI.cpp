#include "Connect4AI.h"
#include <limits.h>

int32_t Connect4AI::evaluateWindow(Player p1, Player p2, Player p3, Player p4, Player player) const {
    int32_t score = 0;
    Player opponent = (player == Player::FIRST) ? Player::SECOND : Player::FIRST;
    
    // Count pieces in window
    uint8_t playerCount = 0;
    uint8_t opponentCount = 0;
    uint8_t emptyCount = 0;
    
    Player pieces[4] = {p1, p2, p3, p4};
    for (uint8_t i = 0; i < 4; i++) {
        if (pieces[i] == player) playerCount++;
        else if (pieces[i] == opponent) opponentCount++;
        else emptyCount++;
    }
    
    // Score based on window content
    if (playerCount == 4) {
        score += WIN_SCORE;
    } else if (playerCount == 3 && emptyCount == 1) {
        score += THREE_SCORE;
    } else if (playerCount == 2 && emptyCount == 2) {
        score += TWO_SCORE;
    }
    
    // Penalize opponent opportunities
    if (opponentCount == 3 && emptyCount == 1) {
        score -= THREE_SCORE * 2; // Block opponent threats heavily
    } else if (opponentCount == 2 && emptyCount == 2) {
        score -= TWO_SCORE;
    }
    
    return score;
}

int32_t Connect4AI::evaluateBoard(const Connect4Board& board, Player player) const {
    int32_t score = 0;
    
    // Evaluate center column (strategic advantage)
    uint8_t centerCol = BOARD_COLS / 2;
    for (uint8_t row = 0; row < BOARD_ROWS; row++) {
        if (board.getCell(row, centerCol) == player) {
            score += CENTER_SCORE;
        }
    }
    
    // Evaluate horizontal windows
    for (uint8_t row = 0; row < BOARD_ROWS; row++) {
        for (uint8_t col = 0; col < BOARD_COLS - 3; col++) {
            score += evaluateWindow(
                board.getCell(row, col),
                board.getCell(row, col + 1),
                board.getCell(row, col + 2),
                board.getCell(row, col + 3),
                player
            );
        }
    }
    
    // Evaluate vertical windows
    for (uint8_t row = 0; row < BOARD_ROWS - 3; row++) {
        for (uint8_t col = 0; col < BOARD_COLS; col++) {
            score += evaluateWindow(
                board.getCell(row, col),
                board.getCell(row + 1, col),
                board.getCell(row + 2, col),
                board.getCell(row + 3, col),
                player
            );
        }
    }
    
    // Evaluate diagonal windows (/)
    for (uint8_t row = 3; row < BOARD_ROWS; row++) {
        for (uint8_t col = 0; col < BOARD_COLS - 3; col++) {
            score += evaluateWindow(
                board.getCell(row, col),
                board.getCell(row - 1, col + 1),
                board.getCell(row - 2, col + 2),
                board.getCell(row - 3, col + 3),
                player
            );
        }
    }
    
    // Evaluate diagonal windows (\)
    for (uint8_t row = 0; row < BOARD_ROWS - 3; row++) {
        for (uint8_t col = 0; col < BOARD_COLS - 3; col++) {
            score += evaluateWindow(
                board.getCell(row, col),
                board.getCell(row + 1, col + 1),
                board.getCell(row + 2, col + 2),
                board.getCell(row + 3, col + 3),
                player
            );
        }
    }
    
    return score;
}

int32_t Connect4AI::minimax(Connect4Board& board, uint8_t depth, int32_t alpha, int32_t beta, 
                            bool maximizing, Player aiPlayer) const {
    // Terminal conditions
    if (board.hasWinner()) {
        if (board.getWinner() == aiPlayer) {
            return WIN_SCORE + depth; // Prefer faster wins
        } else {
            return -WIN_SCORE - depth; // Delay losses
        }
    }
    
    if (board.isDraw() || depth == 0) {
        return evaluateBoard(board, aiPlayer);
    }
    
    Player currentPlayer = maximizing ? aiPlayer : 
                          (aiPlayer == Player::FIRST ? Player::SECOND : Player::FIRST);
    
    if (maximizing) {
        int32_t maxEval = INT32_MIN;
        
        // Try columns from center outward (better move ordering)
        uint8_t moveOrder[BOARD_COLS] = {3, 2, 4, 1, 5, 0, 6};
        
        for (uint8_t i = 0; i < BOARD_COLS; i++) {
            uint8_t col = moveOrder[i];
            
            if (!board.isValidMove(col)) continue;
            
            board.makeMove(col, currentPlayer);
            int32_t eval = minimax(board, depth - 1, alpha, beta, false, aiPlayer);
            board.undoMove(col);
            
            maxEval = (eval > maxEval) ? eval : maxEval;
            alpha = (alpha > eval) ? alpha : eval;
            
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        
        return maxEval;
    } else {
        int32_t minEval = INT32_MAX;
        
        uint8_t moveOrder[BOARD_COLS] = {3, 2, 4, 1, 5, 0, 6};
        
        for (uint8_t i = 0; i < BOARD_COLS; i++) {
            uint8_t col = moveOrder[i];
            
            if (!board.isValidMove(col)) continue;
            
            board.makeMove(col, currentPlayer);
            int32_t eval = minimax(board, depth - 1, alpha, beta, true, aiPlayer);
            board.undoMove(col);
            
            minEval = (eval < minEval) ? eval : minEval;
            beta = (beta < eval) ? beta : eval;
            
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        
        return minEval;
    }
}

int8_t Connect4AI::calculateBestMove(Connect4Board& board, Player player, uint8_t depth) const {
    if (depth == 0) depth = 1; // Minimum depth
    
    int8_t bestMove = -1;
    int32_t bestScore = INT32_MIN;
    
    // Try columns from center outward
    uint8_t moveOrder[BOARD_COLS] = {3, 2, 4, 1, 5, 0, 6};
    
    for (uint8_t i = 0; i < BOARD_COLS; i++) {
        uint8_t col = moveOrder[i];
        
        if (!board.isValidMove(col)) continue;
        
        board.makeMove(col, player);
        
        // Check for immediate win
        if (board.hasWinner() && board.getWinner() == player) {
            board.undoMove(col);
            return col;
        }
        
        int32_t score = minimax(board, depth - 1, INT32_MIN, INT32_MAX, false, player);
        board.undoMove(col);
        
        if (score > bestScore) {
            bestScore = score;
            bestMove = col;
        }
    }
    
    return bestMove;
}
