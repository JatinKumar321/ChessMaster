#include <bits/stdc++.h>
#include "../include/Board.hpp"
#include "../include/Pawn.hpp"
#include "../include/Rook.hpp"
#include "../include/Knight.hpp"
#include "../include/Bishop.hpp"
#include "../include/Queen.hpp"
#include "../include/King.hpp"
#include "../include/Types.hpp"

using namespace std;

Board::Board() {
    m_board.resize(8, std::vector<Piece*>(8, nullptr));
    whiteKingMoved = false;
    blackKingMoved = false;
    whiteRookKingSideMoved = false;
    whiteRookQueenSideMoved = false;
    blackRookKingSideMoved = false;
    blackRookQueenSideMoved = false;
    
    // Initialize en passant variables
    enPassantTargetX = -1;
    enPassantTargetY = -1;
    enPassantAvailable = false;
    
    // Initialize move counters
    halfMoveClock = 0;
    
    setupBoard();
}

Board::~Board() {
    for (auto& row : m_board) {
        for (auto& piece : row) {
            delete piece;
        }
    }
}

void Board::setupBoard() {
    // Black pieces
    m_board[0][0] = new Rook(false);
    m_board[0][1] = new Knight(false);
    m_board[0][2] = new Bishop(false);
    m_board[0][3] = new Queen(false);
    m_board[0][4] = new King(false);
    m_board[0][5] = new Bishop(false);
    m_board[0][6] = new Knight(false);
    m_board[0][7] = new Rook(false);
    for (int i = 0; i < 8; ++i) {
        m_board[1][i] = new Pawn(false);
    }

    // White pieces
    m_board[7][0] = new Rook(true);
    m_board[7][1] = new Knight(true);
    m_board[7][2] = new Bishop(true);
    m_board[7][3] = new Queen(true);
    m_board[7][4] = new King(true);
    m_board[7][5] = new Bishop(true);
    m_board[7][6] = new Knight(true);
    m_board[7][7] = new Rook(true);
    for (int i = 0; i < 8; ++i) {
        m_board[6][i] = new Pawn(true);
    }
}

void Board::display() const {
    system("cls"); // Clear screen for Windows (use "clear" for Linux/Mac)
    
    // Print game title
    cout << Colors::BOLD << Colors::CYAN << "\n";
    cout << "    +========================================+\n";
    cout << "    |              CHESS GAME                |\n";
    cout << "    +========================================+\n";
    cout << Colors::RESET << "\n";
    
    // Print column labels
    cout << "     ";
    for (char c = 'a'; c <= 'h'; ++c) {
        cout << Colors::BOLD << Colors::YELLOW << " " << c << "  " << Colors::RESET;
    }
    cout << "\n   +";
    for (int i = 0; i < 8; ++i) {
        cout << "----";
        if (i < 7) cout << "+";
    }
    cout << "+\n";
    
    // Print board with pieces
    for (int i = 0; i < 8; ++i) {
        // Print row number
        cout << Colors::BOLD << Colors::YELLOW << " " << (8 - i) << " " << Colors::RESET << "|";
        
        for (int j = 0; j < 8; ++j) {
            // Choose background color for square - grey and white alternating
            bool isLightSquare = (i + j) % 2 == 0;
            string bgColor = isLightSquare ? Colors::BG_WHITE : Colors::BG_DARK_GRAY;
            
            cout << bgColor;
            
            if (m_board[i][j]) {
                // WHITE PIECES = YELLOW, BLACK PIECES = DARK BLUE (visible on both backgrounds)
                if (m_board[i][j]->isWhite()) {
                    cout << Colors::BOLD << Colors::YELLOW;  // White pieces in bright yellow
                } else {
                    cout << Colors::BOLD << Colors::BLUE;    // Black pieces in dark blue (visible on all backgrounds)
                }
                cout << " " << m_board[i][j]->getSymbol() << " ";
            } else {
                cout << "   ";
            }
            
            cout << Colors::RESET << "|";
        }
        
        // Print row number on right side
        cout << Colors::BOLD << Colors::YELLOW << " " << (8 - i) << Colors::RESET;
        
        // Print horizontal divider (except for last row)
        if (i < 7) {
            std::cout << "\n   +";
            for (int k = 0; k < 8; ++k) {
                std::cout << "----";
                if (k < 7) std::cout << "+";
            }
            std::cout << "+";
        }
        std::cout << "\n";
    }
    
    // Print bottom border
    std::cout << "   +";
    for (int i = 0; i < 8; ++i) {
        std::cout << "----";
        if (i < 7) std::cout << "+";
    }
    std::cout << "+\n";
    
    // Print column labels again
    std::cout << "     ";
    for (char c = 'a'; c <= 'h'; ++c) {
        std::cout << Colors::BOLD << Colors::YELLOW << " " << c << "  " << Colors::RESET;
    }
    std::cout << "\n";
    
    // Print legend
    std::cout << "\n   Legend: ";
    std::cout << Colors::BOLD << Colors::YELLOW << "Yellow = White pieces" << Colors::RESET << " | ";
    std::cout << Colors::BOLD << Colors::BLUE << "Blue = Black pieces" << Colors::RESET << "\n\n";
}

bool Board::move(const std::string& from, const std::string& to, bool whiteTurn) {
    // Convert algebraic notation to array indices
    int startX = 8 - (from[1] - '0');  // Convert row
    int startY = from[0] - 'a';        // Convert column
    int endX = 8 - (to[1] - '0');      // Convert row
    int endY = to[0] - 'a';            // Convert column

    // Validate coordinates
    if (startX < 0 || startX > 7 || startY < 0 || startY > 7 || endX < 0 || endX > 7 || endY < 0 || endY > 7) {
        std::cout << "Invalid position!\n";
        return false;
    }

    // Check piece ownership
    Piece* piece = m_board[startX][startY];
    if (!piece || piece->isWhite() != whiteTurn) {
        std::cout << "Invalid piece selection!\n";
        return false;
    }

    // Check for en passant
    bool isEnPassant = false;
    if ((piece->getSymbol() == "♙" || piece->getSymbol() == "♟") && 
        canEnPassant(startX, startY, endX, endY)) {
        isEnPassant = true;
    }

    // Validate move
    if (piece->isMoveValid(startX, startY, endX, endY, *this) || isEnPassant) {
        Piece* target = m_board[endX][endY];
        bool wasPawnMove = (piece->getSymbol() == "♙" || piece->getSymbol() == "♟");
        bool wasCapture = (target != nullptr) || isEnPassant;
        
        // Track position for repetition rule
        std::string currentPosition = getBoardHash();
        
        // Update castling flags
        if (piece->getSymbol() == "♔" || piece->getSymbol() == "♚") {
            if (piece->isWhite()) whiteKingMoved = true;
            else blackKingMoved = true;
        }
        if (piece->getSymbol() == "♖" || piece->getSymbol() == "♜") {
            if (piece->isWhite()) {
                if (startX == 7 && startY == 0) whiteRookQueenSideMoved = true;
                if (startX == 7 && startY == 7) whiteRookKingSideMoved = true;
            } else {
                if (startX == 0 && startY == 0) blackRookQueenSideMoved = true;
                if (startX == 0 && startY == 7) blackRookKingSideMoved = true;
            }
        }
        
        // Clear previous en passant state
        enPassantAvailable = false;
        
        // Move piece
        if (isEnPassant) {
            performEnPassant(startX, startY, endX, endY);
        } else {
            m_board[endX][endY] = piece;
            m_board[startX][startY] = nullptr;
        }
        
        // Check if move leaves king in check
        if (isCheck(whiteTurn)) {
            std::cout << "Illegal move, you are in check!\n";
            m_board[startX][startY] = piece;
            m_board[endX][endY] = target;
            return false;
        }
        
        // Set en passant target for next move
        if (wasPawnMove && abs(startX - endX) == 2) {
            enPassantTargetX = (startX + endX) / 2;
            enPassantTargetY = startY;
            enPassantAvailable = true;
        }
        
        // Handle pawn promotion
        if (wasPawnMove && 
            ((piece->isWhite() && endX == 0) || (!piece->isWhite() && endX == 7))) {
            std::cout << Colors::YELLOW << "Pawn promotion! Choose piece (Q/R/B/N): " << Colors::RESET;
            char choice;
            std::cin >> choice;
            choice = toupper(choice);
            if (choice != 'Q' && choice != 'R' && choice != 'B' && choice != 'N') {
                choice = 'Q'; // Default to Queen
            }
            promotePawn(endX, endY, choice);
        }
        
        // Update 50-move counter
        if (wasPawnMove || wasCapture) {
            halfMoveClock = 0;
        } else {
            halfMoveClock++;
        }
        
        // Record position for threefold repetition
        std::string newPosition = getBoardHash();
        boardPositions[newPosition]++;
        
        delete target;
        return true;
    } else {
        std::cout << "Illegal move!\n";
        return false;
    }
}

Piece* Board::getPieceAt(int x, int y) const {
    if (x < 0 || x > 7 || y < 0 || y > 7) return nullptr;
    return m_board[x][y];
}

bool Board::isCheck(bool isWhite) const {
    int kingX = -1, kingY = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] != nullptr && m_board[i][j]->isWhite() == isWhite && (m_board[i][j]->getSymbol() == "♔" || m_board[i][j]->getSymbol() == "♚")) {
                kingX = i;
                kingY = j;
                break;
            }
        }
        if (kingX != -1) break;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] != nullptr && m_board[i][j]->isWhite() != isWhite) {
                if (m_board[i][j]->isMoveValid(i, j, kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(bool isWhite) {
    if (!isCheck(isWhite)) return false;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] != nullptr && m_board[i][j]->isWhite() == isWhite) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (m_board[i][j]->isMoveValid(i, j, x, y, *this)) {
                            Piece* temp = m_board[x][y];
                            m_board[x][y] = m_board[i][j];
                            m_board[i][j] = nullptr;
                            if (!isCheck(isWhite)) {
                                m_board[i][j] = m_board[x][y];
                                m_board[x][y] = temp;
                                return false;
                            }
                            m_board[i][j] = m_board[x][y];
                            m_board[x][y] = temp;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Board::promotePawn(int x, int y, char pieceType) {
    bool isWhite = m_board[x][y]->isWhite();
    delete m_board[x][y];
    
    switch (pieceType) {
        case 'Q':
            m_board[x][y] = new Queen(isWhite);
            break;
        case 'R':
            m_board[x][y] = new Rook(isWhite);
            break;
        case 'B':
            m_board[x][y] = new Bishop(isWhite);
            break;
        case 'N':
            m_board[x][y] = new Knight(isWhite);
            break;
        default:
            m_board[x][y] = new Queen(isWhite); // Default to Queen
    }
}

bool Board::isStalemate(bool isWhite) {
    if (isCheck(isWhite)) return false; // If in check, it's not stalemate
    
    // Check if any legal move exists
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j] != nullptr && m_board[i][j]->isWhite() == isWhite) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (m_board[i][j]->isMoveValid(i, j, x, y, *this)) {
                            Piece* temp = m_board[x][y];
                            m_board[x][y] = m_board[i][j];
                            m_board[i][j] = nullptr;
                            if (!isCheck(isWhite)) {
                                m_board[i][j] = m_board[x][y];
                                m_board[x][y] = temp;
                                return false; // Found a legal move
                            }
                            m_board[i][j] = m_board[x][y];
                            m_board[x][y] = temp;
                        }
                    }
                }
            }
        }
    }
    return true; // No legal moves found
}

bool Board::canCastle(bool isWhite, bool kingSide) {
    if (isWhite) {
        if (whiteKingMoved) return false;
        if (kingSide && whiteRookKingSideMoved) return false;
        if (!kingSide && whiteRookQueenSideMoved) return false;
        
        int row = 7;
        int kingCol = 4;
        int rookCol = kingSide ? 7 : 0;
        
        // Check if squares between king and rook are empty
        int start = std::min(kingCol, rookCol) + 1;
        int end = std::max(kingCol, rookCol) - 1;
        for (int col = start; col <= end; ++col) {
            if (m_board[row][col] != nullptr) return false;
        }
        
        // Check if king would pass through or end up in check
        for (int col = kingCol; col != (kingSide ? 6 : 2); col += (kingSide ? 1 : -1)) {
            // Temporarily move king to check for check
            Piece* originalKing = m_board[row][kingCol];
            m_board[row][col] = originalKing;
            m_board[row][kingCol] = nullptr;
            bool inCheck = isCheck(isWhite);
            m_board[row][kingCol] = originalKing;
            m_board[row][col] = nullptr;
            if (inCheck) return false;
        }
    } else {
        // Similar logic for black
        if (blackKingMoved) return false;
        if (kingSide && blackRookKingSideMoved) return false;
        if (!kingSide && blackRookQueenSideMoved) return false;
        
        int row = 0;
        int kingCol = 4;
        int rookCol = kingSide ? 7 : 0;
        
        int start = std::min(kingCol, rookCol) + 1;
        int end = std::max(kingCol, rookCol) - 1;
        for (int col = start; col <= end; ++col) {
            if (m_board[row][col] != nullptr) return false;
        }
        
        for (int col = kingCol; col != (kingSide ? 6 : 2); col += (kingSide ? 1 : -1)) {
            Piece* originalKing = m_board[row][kingCol];
            m_board[row][col] = originalKing;
            m_board[row][kingCol] = nullptr;
            bool inCheck = isCheck(isWhite);
            m_board[row][kingCol] = originalKing;
            m_board[row][col] = nullptr;
            if (inCheck) return false;
        }
    }
    return true;
}

bool Board::performCastle(bool isWhite, bool kingSide) {
    if (!canCastle(isWhite, kingSide)) return false;
    
    int row = isWhite ? 7 : 0;
    int kingCol = 4;
    int rookCol = kingSide ? 7 : 0;
    int newKingCol = kingSide ? 6 : 2;
    int newRookCol = kingSide ? 5 : 3;
    
    // Move king and rook
    Piece* king = m_board[row][kingCol];
    Piece* rook = m_board[row][rookCol];
    
    m_board[row][newKingCol] = king;
    m_board[row][newRookCol] = rook;
    m_board[row][kingCol] = nullptr;
    m_board[row][rookCol] = nullptr;
    
    // Update movement flags
    if (isWhite) whiteKingMoved = true;
    else blackKingMoved = true;
    
    return true;
}

bool Board::canEnPassant(int startX, int startY, int endX, int endY) const {
    // No en passant if not enabled
    if (!enPassantAvailable) return false;
    
    // Only pawns can en passant
    Piece* piece = m_board[startX][startY];
    if (!piece || (piece->getSymbol() != "♙" && piece->getSymbol() != "♟")) return false;
    
    // Direction depends on color
    int direction = piece->isWhite() ? -1 : 1;
    
    // Must move diagonally to target square
    return (startX + direction == endX && 
            endY == enPassantTargetY && 
            endX == enPassantTargetX);
}

bool Board::performEnPassant(int startX, int startY, int endX, int endY) {
    // Verify it's valid
    if (!canEnPassant(startX, startY, endX, endY)) return false;
    
    Piece* pawn = m_board[startX][startY];
    
    // Move attacking pawn
    m_board[endX][endY] = pawn;
    m_board[startX][startY] = nullptr;
    
    // Remove captured pawn (special case - not at end position)
    int capturedPawnX = pawn->isWhite() ? endX + 1 : endX - 1;
    delete m_board[capturedPawnX][endY];
    m_board[capturedPawnX][endY] = nullptr;
    
    return true;
}

std::string Board::getBoardHash() {
    // Create unique position fingerprint
    std::ostringstream hash;
    
    // Add all piece positions
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j]) {
                hash << i << j << m_board[i][j]->getSymbol();
            } else {
                hash << i << j << ".";
            }
        }
    }
    
    // Add game state info
    hash << whiteKingMoved << blackKingMoved;
    hash << whiteRookKingSideMoved << whiteRookQueenSideMoved;
    hash << blackRookKingSideMoved << blackRookQueenSideMoved;
    hash << enPassantAvailable << enPassantTargetX << enPassantTargetY;
    
    return hash.str();
}

bool Board::isThreefoldRepetition() {
    // Current position
    std::string currentPosition = getBoardHash();
    
    // Check repetition count
    auto it = boardPositions.find(currentPosition);
    return (it != boardPositions.end() && it->second >= 3);
}

bool Board::isFiftyMoveRule() const {
    // 50 full moves = 100 half moves
    return halfMoveClock >= 100;
}

bool Board::hasOnlyKingsAndMinorPieces() const {
    // Count minor pieces
    int whiteKnights = 0, whiteBishops = 0;
    int blackKnights = 0, blackBishops = 0;
    bool hasOtherPieces = false;
    
    // Check all squares
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (m_board[i][j]) {
                std::string symbol = m_board[i][j]->getSymbol();
                // Classify pieces
                if (symbol == "♔" || symbol == "♚") {
                    continue; // Kings don't count
                } else if (symbol == "♘") {
                    whiteKnights++;
                } else if (symbol == "♞") {
                    blackKnights++;
                } else if (symbol == "♗") {
                    whiteBishops++;
                } else if (symbol == "♝") {
                    blackBishops++;
                } else {
                    // Queens, rooks, pawns can deliver mate
                    hasOtherPieces = true;
                }
            }
        }
    }
    
    // If pawns, queens or rooks exist, checkmate is possible
    if (hasOtherPieces) return false;
    
    // Check known insufficient material patterns
    int totalMinorPieces = whiteKnights + whiteBishops + blackKnights + blackBishops;
    
    // King vs King
    if (totalMinorPieces == 0) return true;
    
    // King + minor piece vs King
    if (totalMinorPieces == 1) return true;
    
    // King + Bishop vs King + Bishop (same color squares)
    if (whiteBishops == 1 && blackBishops == 1 && whiteKnights == 0 && blackKnights == 0) {
        // Find bishops and check if they're on same color squares
        int whiteBishopColor = -1, blackBishopColor = -1;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (m_board[i][j]) {
                    if (m_board[i][j]->getSymbol() == "♗") {
                        whiteBishopColor = (i + j) % 2; // Square color (0=dark, 1=light)
                    } else if (m_board[i][j]->getSymbol() == "♝") {
                        blackBishopColor = (i + j) % 2;
                    }
                }
            }
        }
        // Same-colored bishops can't checkmate
        return whiteBishopColor == blackBishopColor;
    }
    
    return false;
}

bool Board::isInsufficientMaterial() const {
    // Delegate to helper function
    return hasOnlyKingsAndMinorPieces();
}
