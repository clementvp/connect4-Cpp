#include "Connect4.h"

// For printBoard() - Arduino compatibility
#ifdef ARDUINO
#include <Arduino.h>
#define PRINT(x) Serial.print(x)
#define PRINTLN(x) Serial.println(x)
#else
#include <iostream>
#define PRINT(x) std::cout << x
#define PRINTLN(x) std::cout << x << std::endl
#endif

Connect4::Connect4() {
    // Simple initialization
}

void Connect4::reset() {
    board.reset();
}

bool Connect4::playMoveInternal(uint8_t column, Player player) {
    // Internal method using 0-6 indexing
    if (player == Player::NONE) {
        return false;
    }
    return board.makeMove(column, player);
}

bool Connect4::playMove(uint8_t column, Player player) {
    // User-facing method: convert from 1-7 to internal 0-6
    if (column < 1 || column > 7) {
        return false;
    }
    return playMoveInternal(column - 1, player);
}

uint8_t Connect4::calculateBestMove(Player player, uint8_t depth) {
    // Calculate best move and convert from internal 0-6 to user-facing 1-7
    if (player == Player::NONE) {
        return 0;  // Return 0 for error (no valid move)
    }
    
    int8_t bestMove = ai.calculateBestMove(board, player, depth);
    
    if (bestMove < 0) {
        return 0;  // Return 0 for error (no valid move)
    }
    
    return static_cast<uint8_t>(bestMove + 1);  // Convert 0-6 to 1-7
}

bool Connect4::isValidMove(uint8_t column) const {
    // User-facing method: convert from 1-7 to internal 0-6
    if (column < 1 || column > 7) {
        return false;
    }
    return board.isValidMove(column - 1);
}

bool Connect4::hasWinner() const {
    return board.hasWinner();
}

Player Connect4::getWinner() const {
    return board.getWinner();
}

bool Connect4::isDraw() const {
    return board.isDraw();
}

bool Connect4::isGameOver() const {
    return board.isGameOver();
}

GameState Connect4::getGameState() const {
    return board.getState();
}

const Connect4Board& Connect4::getBoard() const {
    return board;
}

Player Connect4::getCell(uint8_t row, uint8_t col) const {
    return board.getCell(row, col);
}

uint8_t Connect4::getColumnHeight(uint8_t col) const {
    return board.getColumnHeight(col);
}

Player Connect4::getOpponent(Player player) const {
    if (player == Player::FIRST) return Player::SECOND;
    if (player == Player::SECOND) return Player::FIRST;
    return Player::NONE;
}

void Connect4::printBoard() const {
    PRINTLN("\n  1 2 3 4 5 6 7");
    PRINTLN("  -------------");
    
    // Print from top to bottom (row 5 to 0)
    for (int8_t row = BOARD_ROWS - 1; row >= 0; row--) {
        PRINT("|");
        for (uint8_t col = 0; col < BOARD_COLS; col++) {
            Player cell = board.getCell(row, col);
            if (cell == Player::FIRST) {
                PRINT(" X");
            } else if (cell == Player::SECOND) {
                PRINT(" O");
            } else {
                PRINT(" .");
            }
        }
        PRINTLN(" |");
    }
    
    PRINTLN("  -------------");
    PRINTLN("");
}
