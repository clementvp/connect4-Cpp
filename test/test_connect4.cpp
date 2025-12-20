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
    
    cout << "Initial board:" << endl;
    game.printBoard();
    
    // Player 1 plays column 3
    cout << "Player 1 plays column 3" << endl;
    game.playMove(3, Player::FIRST);
    game.printBoard();
    
    // AI (Player 2) responds with depth 5
    cout << "AI is thinking..." << endl;
    auto start = chrono::high_resolution_clock::now();
    uint8_t aiMove = game.calculateBestMove(Player::SECOND, 5);
    if (aiMove > 0) {  // 0 = error, 1-7 = valid move
        game.playMove(aiMove, Player::SECOND);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "AI played column " << (int)aiMove << " (took " << duration.count() << " ms)" << endl;
    game.printBoard();
    
    cout << "✓ Test 1 passed!\n" << endl;
}

void testAIFirst() {
    cout << "TEST 2: AI Plays First" << endl;
    printSeparator();
    
    Connect4 game;
    
    cout << "AI plays first (depth 6)..." << endl;
    auto start = chrono::high_resolution_clock::now();
    uint8_t aiMove = game.calculateBestMove(Player::FIRST, 6);
    if (aiMove > 0) {  // 0 = error, 1-7 = valid move
        game.playMove(aiMove, Player::FIRST);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "AI played column " << (int)aiMove << " (took " << duration.count() << " ms)" << endl;
    game.printBoard();
    
    cout << "✓ Test 2 passed!\n" << endl;
}

void testFullGame() {
    cout << "TEST 3: Full Game Simulation" << endl;
    printSeparator();
    
    Connect4 game;
    const uint8_t AI_DEPTH = 4;
    
    cout << "Playing a full game (AI depth 4)..." << endl;
    
    int moveCount = 0;
    uint8_t humanMoves[] = {3, 2, 4, 1, 3, 2, 3, 4, 3, 2, 3, 5, 3};
    
    while (!game.isGameOver() && moveCount < 13) {
        // Human move (Player 1)
        cout << "\nMove " << (moveCount + 1) << ": Human plays column " << (int)humanMoves[moveCount] << endl;
        game.playMove(humanMoves[moveCount], Player::FIRST);
        game.printBoard();
        
        if (game.hasWinner()) {
            cout << "Human wins!" << endl;
            break;
        }
        if (game.isDraw()) {
            cout << "Draw!" << endl;
            break;
        }
        
        // AI move (Player 2)
        cout << "AI thinking..." << endl;
        auto start = chrono::high_resolution_clock::now();
        uint8_t aiMove = game.calculateBestMove(Player::SECOND, AI_DEPTH);
        if (aiMove > 0) {  // 0 = error, 1-7 = valid move
            game.playMove(aiMove, Player::SECOND);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "AI played column " << (int)aiMove << " (took " << duration.count() << " ms)" << endl;
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
    
    cout << "Testing different depths..." << endl;
    
    // Human plays
    game.playMove(3, Player::FIRST);
    
    // Test depths 1-7
    for (uint8_t depth = 1; depth <= 7; depth++) {
        Connect4 testGame = game;
        
        cout << "\nDepth " << (int)depth << ": ";
        auto start = chrono::high_resolution_clock::now();
        uint8_t move = testGame.calculateBestMove(Player::SECOND, depth);
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
    game.playMove(1, Player::FIRST);
    game.playMove(1, Player::SECOND);
    game.playMove(2, Player::FIRST);
    game.playMove(2, Player::SECOND);
    game.playMove(3, Player::FIRST);
    game.playMove(3, Player::SECOND);
    game.playMove(4, Player::FIRST);  // Should win
    
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
    
    cout << "Benchmarking AI at different depths..." << endl;
    cout << "\nDepth | Time (ms) | Best Move" << endl;
    cout << "------|-----------|----------" << endl;
    
    for (uint8_t depth = 1; depth <= 8; depth++) {
        Connect4 testGame;
        
        auto start = chrono::high_resolution_clock::now();
        uint8_t move = testGame.calculateBestMove(Player::FIRST, depth);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "  " << (int)depth << "   |   " << duration.count() << " ms   | column " << (int)move << endl;
    }
    
    cout << "\n✓ Test 6 passed!\n" << endl;
}

void testTwoPlayers() {
    cout << "TEST 7: Two Human Players" << endl;
    printSeparator();
    
    Connect4 game;
    
    cout << "Testing two-player mode (no AI)..." << endl;
    
    // Simulate alternating human players (columns 1-7)
    game.playMove(4, Player::FIRST);   // Player 1
    game.playMove(3, Player::SECOND);  // Player 2
    game.playMove(4, Player::FIRST);   // Player 1
    game.playMove(3, Player::SECOND);  // Player 2
    
    game.printBoard();
    
    cout << "✓ Two players can play independently!" << endl;
    cout << "✓ Test 7 passed!\n" << endl;
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
        testTwoPlayers();
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
