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

Connect4::Connect4() 
    : searchDepth(4), aiPlayer(Player::SECOND), currentPlayer(Player::FIRST) {
    // Default: AI is Player::SECOND, search depth is 4
}

void Connect4::setSearchDepth(uint8_t depth) {
    searchDepth = (depth > 0) ? depth : 1;
}

uint8_t Connect4::getSearchDepth() const {
    return searchDepth;
}

void Connect4::setAIPlayer(Player player) {
    if (player == Player::FIRST || player == Player::SECOND) {
        aiPlayer = player;
    }
}

Player Connect4::getAIPlayer() const {
    return aiPlayer;
}

void Connect4::reset() {
    board.reset();
    currentPlayer = Player::FIRST;
}

bool Connect4::playMove(uint8_t column, Player player) {
    if (board.makeMove(column, player)) {
        // Toggle current player
        currentPlayer = (currentPlayer == Player::FIRST) ? Player::SECOND : Player::FIRST;
        return true;
    }
    return false;
}

int8_t Connect4::calculateBestMove(uint8_t depth) {
    return ai.calculateBestMove(board, aiPlayer, depth);
}

int8_t Connect4::calculateBestMove() {
    return calculateBestMove(searchDepth);
}

bool Connect4::playHumanMove(uint8_t column) {
    Player humanPlayer = (aiPlayer == Player::FIRST) ? Player::SECOND : Player::FIRST;
    return playMove(column, humanPlayer);
}

bool Connect4::playAIMove() {
    int8_t move = calculateBestMove();
    if (move >= 0) {
        return playMove(move, aiPlayer);
    }
    return false;
}

bool Connect4::playAIMove(uint8_t depth) {
    int8_t move = calculateBestMove(depth);
    if (move >= 0) {
        return playMove(move, aiPlayer);
    }
    return false;
}

bool Connect4::isValidMove(uint8_t column) const {
    return board.isValidMove(column);
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

Player Connect4::getCurrentPlayer() const {
    return currentPlayer;
}

void Connect4::setCurrentPlayer(Player player) {
    if (player == Player::FIRST || player == Player::SECOND) {
        currentPlayer = player;
    }
}

Player Connect4::getOpponent(Player player) const {
    if (player == Player::FIRST) return Player::SECOND;
    if (player == Player::SECOND) return Player::FIRST;
    return Player::NONE;
}

void Connect4::printBoard() const {
    PRINTLN("\n  0 1 2 3 4 5 6");
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
