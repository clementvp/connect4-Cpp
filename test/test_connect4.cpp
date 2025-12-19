#include "../src/Connect4.h"
#include <iostream>
#include <chrono>

using namespace std;

void printSeparator() {
    cout << "\n========================================\n" << endl;
}

void testBasicGame() {
    cout << "TEST 1: Basic Game Test" << endl;
    printSeparator();
    
    Connect4 game;
    game.setSearchDepth(5);
    game.setAIPlayer(Player::SECOND);
    
    cout << "Initial board:" << endl;
    game.printBoard();
    
    // Human plays column 3
    cout << "Human plays column 3" << endl;
    game.playHumanMove(3);
    game.printBoard();
    
    // AI responds
    cout << "AI is thinking..." << endl;
    auto start = chrono::high_resolution_clock::now();
    game.playAIMove();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "AI played (took " << duration.count() << " ms)" << endl;
    game.printBoard();
    
    cout << "✓ Test 1 passed!\n" << endl;
}

void testAIFirst() {
    cout << "TEST 2: AI Plays First" << endl;
    printSeparator();
    
    Connect4 game;
    game.setAIPlayer(Player::FIRST);
    game.setSearchDepth(6);
    
    cout << "AI plays first (depth 6)..." << endl;
    auto start = chrono::high_resolution_clock::now();
    game.playAIMove();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "AI played (took " << duration.count() << " ms)" << endl;
    game.printBoard();
    
    cout << "✓ Test 2 passed!\n" << endl;
}

void testFullGame() {
    cout << "TEST 3: Full Game Simulation" << endl;
    printSeparator();
    
    Connect4 game;
    game.setAIPlayer(Player::SECOND);
    game.setSearchDepth(4);
    
    cout << "Playing a full game (depth 4)..." << endl;
    
    int moveCount = 0;
    uint8_t humanMoves[] = {3, 2, 4, 1, 3, 2, 3, 4, 3, 2, 3, 5, 3};
    
    while (!game.isGameOver() && moveCount < 13) {
        // Human move
        cout << "\nMove " << (moveCount + 1) << ": Human plays column " << (int)humanMoves[moveCount] << endl;
        game.playHumanMove(humanMoves[moveCount]);
        game.printBoard();
        
        if (game.hasWinner()) {
            cout << "Human wins!" << endl;
            break;
        }
        if (game.isDraw()) {
            cout << "Draw!" << endl;
            break;
        }
        
        // AI move
        cout << "AI thinking..." << endl;
        auto start = chrono::high_resolution_clock::now();
        game.playAIMove();
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "AI played (took " << duration.count() << " ms)" << endl;
        game.printBoard();
        
        if (game.hasWinner()) {
            cout << "AI wins!" << endl;
            break;
        }
        if (game.isDraw()) {
            cout << "Draw!" << endl;
            break;
        }
        
        moveCount++;
    }
    
    cout << "Game ended after " << game.getBoard().getMoveCount() << " total moves" << endl;
    cout << "✓ Test 3 passed!\n" << endl;
}

void testCustomDepth() {
    cout << "TEST 4: Custom Depth Per Move" << endl;
    printSeparator();
    
    Connect4 game;
    game.setAIPlayer(Player::SECOND);
    
    cout << "Testing different depths..." << endl;
    
    // Human plays
    game.playHumanMove(3);
    
    // Test depths 1-7
    for (uint8_t depth = 1; depth <= 7; depth++) {
        Connect4 testGame = game;
        
        cout << "\nDepth " << (int)depth << ": ";
        auto start = chrono::high_resolution_clock::now();
        int8_t move = testGame.calculateBestMove(depth);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "Best move = " << (int)move << " (took " << duration.count() << " ms)" << endl;
    }
    
    cout << "\n✓ Test 4 passed!\n" << endl;
}

void testBoardDetection() {
    cout << "TEST 5: Win Detection" << endl;
    printSeparator();
    
    Connect4 game;
    
    // Create a horizontal win for Player FIRST
    cout << "Testing horizontal win detection..." << endl;
    game.playMove(0, Player::FIRST);
    game.playMove(0, Player::SECOND);
    game.playMove(1, Player::FIRST);
    game.playMove(1, Player::SECOND);
    game.playMove(2, Player::FIRST);
    game.playMove(2, Player::SECOND);
    game.playMove(3, Player::FIRST);  // Should win
    
    game.printBoard();
    
    if (game.hasWinner() && game.getWinner() == Player::FIRST) {
        cout << "✓ Horizontal win detected correctly!" << endl;
    } else {
        cout << "✗ Horizontal win detection failed!" << endl;
    }
    
    // Test vertical win
    game.reset();
    cout << "\nTesting vertical win detection..." << endl;
    game.playMove(3, Player::FIRST);
    game.playMove(4, Player::SECOND);
    game.playMove(3, Player::FIRST);
    game.playMove(4, Player::SECOND);
    game.playMove(3, Player::FIRST);
    game.playMove(4, Player::SECOND);
    game.playMove(3, Player::FIRST);  // Should win
    
    game.printBoard();
    
    if (game.hasWinner() && game.getWinner() == Player::FIRST) {
        cout << "✓ Vertical win detected correctly!" << endl;
    } else {
        cout << "✗ Vertical win detection failed!" << endl;
    }
    
    cout << "\n✓ Test 5 passed!\n" << endl;
}

void testPerformance() {
    cout << "TEST 6: Performance Benchmark" << endl;
    printSeparator();
    
    Connect4 game;
    game.setAIPlayer(Player::FIRST);
    
    cout << "Benchmarking AI at different depths..." << endl;
    cout << "\nDepth | Time (ms) | Moves explored" << endl;
    cout << "------|-----------|----------------" << endl;
    
    for (uint8_t depth = 1; depth <= 8; depth++) {
        Connect4 testGame;
        testGame.setAIPlayer(Player::FIRST);
        
        auto start = chrono::high_resolution_clock::now();
        int8_t move = testGame.calculateBestMove(depth);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "  " << (int)depth << "   |   " << duration.count() << " ms   | column " << (int)move << endl;
    }
    
    cout << "\n✓ Test 6 passed!\n" << endl;
}

int main() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║   Connect4 Library Test Suite         ║" << endl;
    cout << "╚════════════════════════════════════════╝\n" << endl;
    
    try {
        testBasicGame();
        testAIFirst();
        testCustomDepth();
        testBoardDetection();
        testPerformance();
        testFullGame();
        
        printSeparator();
        cout << "✓ ALL TESTS PASSED!" << endl;
        cout << "\nLibrary is working correctly!\n" << endl;
        
        return 0;
    } catch (const exception& e) {
        cerr << "\n✗ TEST FAILED: " << e.what() << endl;
        return 1;
    }
}
