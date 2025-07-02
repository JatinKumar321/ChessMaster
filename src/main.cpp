#include <bits/stdc++.h>
#include "../include/Board.hpp"
#include "../include/Types.hpp"

using namespace std;

int main() {
    system("chcp 65001 > nul"); // UTF-8 for Unicode pieces
    
    Board board;           // Game board
    bool whiteTurn = true; // Current player
    string from, to;       // Move input
    int moveCount = 1;     // Move counter

    // Display welcome screen with game instructions
    cout << Colors::BOLD << Colors::GREEN;
    cout << "\n+==============================================================+\n";
    cout << "|                    WELCOME TO CHESS!                           |\n";
    cout << "|                                                                |\n";
    cout << "|  * Enter moves in format: e2 e4                                |\n";
    cout << "|  * Type 'quit' to exit the game                                |\n";
    cout << "|  * White moves first                                           |\n";
    cout << "+================================================================+\n";
    cout << Colors::RESET;
    
    // Wait for user to start the game
    cout << "\nPress Enter to start the game...";
    cin.ignore();

    // Main game loop - continues until game ends or user quits
    while (true) {
        // Display current board state
        board.display();
        
        // Check for checkmate
        if (board.isCheckmate(whiteTurn)) {
            cout << Colors::BOLD << Colors::RED;
            cout << "+======================================+\n";
            cout << "|              CHECKMATE!              |\n";
            cout << "|    " << (whiteTurn ? "Black" : "White") << " wins the game!             |\n";
            std::cout << "+======================================+\n";
            std::cout << Colors::RESET;
            break;
        }
        
        // Check for stalemate
        if (board.isStalemate(whiteTurn)) {
            std::cout << Colors::BOLD << Colors::YELLOW;
            std::cout << "+======================================+\n";
            std::cout << "|              STALEMATE!              |\n";
            std::cout << "|             Game is a draw!          |\n";
            std::cout << "+======================================+\n";
            std::cout << Colors::RESET;
            break;
        }
        
        // Check for threefold repetition
        if (board.isThreefoldRepetition()) {
            std::cout << Colors::BOLD << Colors::YELLOW;
            std::cout << "+======================================+\n";
            std::cout << "|         THREEFOLD REPETITION!        |\n";
            std::cout << "|             Game is a draw!          |\n";
            std::cout << "+======================================+\n";
            std::cout << Colors::RESET;
            break;
        }
        
        // Check for 50-move rule
        if (board.isFiftyMoveRule()) {
            std::cout << Colors::BOLD << Colors::YELLOW;
            std::cout << "+======================================+\n";
            std::cout << "|            50-MOVE RULE!             |\n";
            std::cout << "|             Game is a draw!          |\n";
            std::cout << "+======================================+\n";
            std::cout << Colors::RESET;
            break;
        }
        
        // Check for insufficient material
        if (board.isInsufficientMaterial()) {
            std::cout << Colors::BOLD << Colors::YELLOW;
            std::cout << "+======================================+\n";
            std::cout << "|        INSUFFICIENT MATERIAL!        |\n";
            std::cout << "|             Game is a draw!          |\n";
            std::cout << "+======================================+\n";
            std::cout << Colors::RESET;
            break;
        }
        
        // Check for check
        if (board.isCheck(whiteTurn)) {
            std::cout << Colors::BOLD << Colors::RED;
            std::cout << "*** " << (whiteTurn ? "White" : "Black") << " is in CHECK! ***\n";
            std::cout << Colors::RESET;
        }

        // Display current turn
        std::cout << Colors::BOLD;
        if (whiteTurn) {
            std::cout << Colors::YELLOW << "Move " << moveCount << ": White to play (YELLOW pieces)";
        } else {
            std::cout << Colors::BLACK << "Move " << moveCount << ": Black to play (BLACK pieces)";
        }
        std::cout << Colors::RESET << "\n";
        
        std::cout << "Enter your move (from to) or 'quit' to exit: ";
        std::cin >> from;
        
        // Check for quit immediately after first input
        if (from == "quit" || from == "exit") {
            std::cout << Colors::CYAN << "Thanks for playing!\n" << Colors::RESET;
            break;
        }
        
        std::cin >> to;

        if (to == "quit" || to == "exit") {
            std::cout << Colors::CYAN << "Thanks for playing!\n" << Colors::RESET;
            break;
        }

        if (board.move(from, to, whiteTurn)) {
            whiteTurn = !whiteTurn;
            if (whiteTurn) {
                moveCount++;
            }
        } else {
            std::cout << Colors::RED << "*** Invalid move! Try again. ***\n" << Colors::RESET;
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

    return 0;
}
