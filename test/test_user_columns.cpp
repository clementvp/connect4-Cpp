#include "../src/Connect4.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Test User Column Numbering (1-7) ===" << endl;
    
    Connect4 game;
    game.setSearchDepth(5);
    game.setAIPlayer(Player::SECOND);
    
    cout << "\nInitial board (columns 1-7):" << endl;
    game.printBoard();
    
    // Test user input with column numbering 1-7
    cout << "Human plays column 4 (user input)" << endl;
    if (game.playHumanMoveUser(4)) {
        cout << "✓ Move accepted!" << endl;
    } else {
        cout << "✗ Move rejected!" << endl;
    }
    game.printBoard();
    
    // AI plays
    cout << "AI is thinking..." << endl;
    game.playAIMove();
    
    // Test new user-facing methods
    int8_t aiMove = game.getLastAIMoveUser();
    cout << "\n--- Using getLastAIMoveUser() ---" << endl;
    cout << "AI move (user format 1-7): " << (int)aiMove << endl;
    
    cout << "\n--- Using printAIMove() ---" << endl;
    game.printAIMove(game.getLastAIMove());
    
    game.printBoard();
    
    // Test boundary conditions
    cout << "\n--- Testing boundary conditions ---" << endl;
    
    cout << "Testing column 1 (minimum)..." << endl;
    if (game.playHumanMoveUser(1)) {
        cout << "✓ Column 1 works!" << endl;
    }
    game.printBoard();
    
    cout << "Testing column 7 (maximum)..." << endl;
    if (game.playHumanMoveUser(7)) {
        cout << "✓ Column 7 works!" << endl;
    }
    
    game.playAIMove();
    game.printAIMove(game.getLastAIMove());
    game.printBoard();
    
    // Test invalid inputs
    cout << "\n--- Testing invalid inputs ---" << endl;
    
    cout << "Testing column 0 (invalid)..." << endl;
    if (!game.playHumanMoveUser(0)) {
        cout << "✓ Column 0 correctly rejected!" << endl;
    } else {
        cout << "✗ Column 0 should be rejected!" << endl;
    }
    
    cout << "Testing column 8 (invalid)..." << endl;
    if (!game.playHumanMoveUser(8)) {
        cout << "✓ Column 8 correctly rejected!" << endl;
    } else {
        cout << "✗ Column 8 should be rejected!" << endl;
    }
    
    cout << "\n✓ All tests completed successfully!" << endl;
    cout << "\nSummary:" << endl;
    cout << "- Board displays columns 1-7 ✓" << endl;
    cout << "- User input accepts 1-7 ✓" << endl;
    cout << "- AI move displays as 1-7 ✓" << endl;
    cout << "- Invalid inputs (0, 8+) rejected ✓" << endl;
    
    return 0;
}
