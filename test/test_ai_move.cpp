#include "../src/Connect4.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Test AI Move Display ===" << endl;
    
    Connect4 game;
    game.setSearchDepth(5);
    game.setAIPlayer(Player::SECOND);
    
    cout << "\nInitial board:" << endl;
    game.printBoard();
    
    // Human plays
    cout << "Human plays column 3" << endl;
    game.playHumanMove(3);
    game.printBoard();
    
    // AI plays
    cout << "AI is thinking..." << endl;
    game.playAIMove();
    
    // Test new methods
    int8_t lastMove = game.getLastAIMove();
    cout << "\n--- Using getLastAIMove() ---" << endl;
    cout << "Last AI move: " << (int)lastMove << endl;
    
    cout << "\n--- Using printAIMove() ---" << endl;
    game.printAIMove(lastMove);
    
    game.printBoard();
    
    // Another round
    cout << "\nHuman plays column 2" << endl;
    game.playHumanMove(2);
    game.printBoard();
    
    cout << "AI plays..." << endl;
    game.playAIMove();
    game.printAIMove(game.getLastAIMove());
    game.printBoard();
    
    cout << "\n✓ Test completed successfully!" << endl;
    
    return 0;
}
