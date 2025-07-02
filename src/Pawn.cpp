#include <bits/stdc++.h>
#include "../include/Pawn.hpp"
#include "../include/Board.hpp"

using namespace std;

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

string Pawn::getSymbol() const {
    return m_isWhite ? "♙" : "♟";  // White: outline, Black: filled
}

bool Pawn::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    int direction = m_isWhite ? -1 : 1;
    
    // Standard one-step forward move
    if (startX + direction == endX && startY == endY && board.getPieceAt(endX, endY) == nullptr) {
        return true;
    }
    
    // Initial two-step forward move
    if ((m_isWhite && startX == 6) || (!m_isWhite && startX == 1)) {
        if (startX + 2 * direction == endX && startY == endY && 
            board.getPieceAt(endX, endY) == nullptr && 
            board.getPieceAt(startX + direction, startY) == nullptr) {
            return true;
        }
    }
    
    // Regular capture move
    if (startX + direction == endX && abs(startY - endY) == 1) {
        Piece* target = board.getPieceAt(endX, endY);
        if (target != nullptr && target->isWhite() != m_isWhite) {
            return true;
        }
        
        // En passant capture is handled separately in Board::canEnPassant
        // This function only validates normal pawn moves
    }
    
    return false;
}
