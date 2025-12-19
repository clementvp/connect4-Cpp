#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H

#include <stdint.h>

// Constants
constexpr uint8_t BOARD_ROWS = 6;
constexpr uint8_t BOARD_COLS = 7;
constexpr uint8_t CONNECT_WIN = 4;

enum class Player : uint8_t {
    NONE = 0,
    FIRST = 1,
    SECOND = 2
};

enum class GameState : uint8_t {
    IN_PROGRESS,
    FIRST_WINS,
    SECOND_WINS,
    DRAW
};

class Connect4Board {
private:
    uint8_t board[BOARD_ROWS][BOARD_COLS];
    uint8_t columnHeights[BOARD_COLS];
    uint8_t moveCount;
    GameState state;
    Player winner;

    // Check if there's a win at the given position
    bool checkWinAt(uint8_t row, uint8_t col, Player player) const {
        // Horizontal
        int count = 1;
        // Check left
        for (int c = col - 1; c >= 0 && board[row][c] == static_cast<uint8_t>(player); c--) count++;
        // Check right
        for (int c = col + 1; c < BOARD_COLS && board[row][c] == static_cast<uint8_t>(player); c++) count++;
        if (count >= CONNECT_WIN) return true;

        // Vertical
        count = 1;
        // Check down
        for (int r = row + 1; r < BOARD_ROWS && board[r][col] == static_cast<uint8_t>(player); r++) count++;
        // Check up
        for (int r = row - 1; r >= 0 && board[r][col] == static_cast<uint8_t>(player); r--) count++;
        if (count >= CONNECT_WIN) return true;

        // Diagonal (/)
        count = 1;
        // Check down-left
        for (int r = row + 1, c = col - 1; r < BOARD_ROWS && c >= 0 && board[r][c] == static_cast<uint8_t>(player); r++, c--) count++;
        // Check up-right
        for (int r = row - 1, c = col + 1; r >= 0 && c < BOARD_COLS && board[r][c] == static_cast<uint8_t>(player); r--, c++) count++;
        if (count >= CONNECT_WIN) return true;

        // Diagonal (\)
        count = 1;
        // Check down-right
        for (int r = row + 1, c = col + 1; r < BOARD_ROWS && c < BOARD_COLS && board[r][c] == static_cast<uint8_t>(player); r++, c++) count++;
        // Check up-left
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0 && board[r][c] == static_cast<uint8_t>(player); r--, c--) count++;
        if (count >= CONNECT_WIN) return true;

        return false;
    }

public:
    Connect4Board() {
        reset();
    }

    void reset() {
        for (uint8_t r = 0; r < BOARD_ROWS; r++) {
            for (uint8_t c = 0; c < BOARD_COLS; c++) {
                board[r][c] = static_cast<uint8_t>(Player::NONE);
            }
        }
        for (uint8_t c = 0; c < BOARD_COLS; c++) {
            columnHeights[c] = 0;
        }
        moveCount = 0;
        state = GameState::IN_PROGRESS;
        winner = Player::NONE;
    }

    bool isValidMove(uint8_t col) const {
        return col < BOARD_COLS && columnHeights[col] < BOARD_ROWS;
    }

    bool makeMove(uint8_t col, Player player) {
        if (!isValidMove(col) || state != GameState::IN_PROGRESS) {
            return false;
        }

        uint8_t row = columnHeights[col];
        board[row][col] = static_cast<uint8_t>(player);
        columnHeights[col]++;
        moveCount++;

        // Check for win
        if (checkWinAt(row, col, player)) {
            state = (player == Player::FIRST) ? GameState::FIRST_WINS : GameState::SECOND_WINS;
            winner = player;
        }
        // Check for draw
        else if (moveCount >= BOARD_ROWS * BOARD_COLS) {
            state = GameState::DRAW;
        }

        return true;
    }

    void undoMove(uint8_t col) {
        if (col >= BOARD_COLS || columnHeights[col] == 0) {
            return;
        }

        columnHeights[col]--;
        uint8_t row = columnHeights[col];
        board[row][col] = static_cast<uint8_t>(Player::NONE);
        moveCount--;
        state = GameState::IN_PROGRESS;
        winner = Player::NONE;
    }

    Player getCell(uint8_t row, uint8_t col) const {
        if (row >= BOARD_ROWS || col >= BOARD_COLS) {
            return Player::NONE;
        }
        return static_cast<Player>(board[row][col]);
    }

    uint8_t getColumnHeight(uint8_t col) const {
        return col < BOARD_COLS ? columnHeights[col] : 0;
    }

    GameState getState() const {
        return state;
    }

    Player getWinner() const {
        return winner;
    }

    uint8_t getMoveCount() const {
        return moveCount;
    }

    bool isFull() const {
        return moveCount >= BOARD_ROWS * BOARD_COLS;
    }

    bool hasWinner() const {
        return state == GameState::FIRST_WINS || state == GameState::SECOND_WINS;
    }

    bool isDraw() const {
        return state == GameState::DRAW;
    }

    bool isGameOver() const {
        return state != GameState::IN_PROGRESS;
    }
};

#endif // CONNECT4_BOARD_H
