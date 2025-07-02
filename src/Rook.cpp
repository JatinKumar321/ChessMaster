#include <bits/stdc++.h>
#include "../include/Rook.hpp"
#include "../include/Board.hpp"

using namespace std;

Rook::Rook(bool isWhite) : Piece(isWhite) {}

string Rook::getSymbol() const {
    return m_isWhite ? "♖" : "♜";  // White: outline, Black: filled
}

bool Rook::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    if (startX != endX && startY != endY) {
        return false;
    }
    int xDirection = (endX > startX) ? 1 : ((endX < startX) ? -1 : 0);
    int yDirection = (endY > startY) ? 1 : ((endY < startY) ? -1 : 0);
    int currentX = startX + xDirection;
    int currentY = startY + yDirection;
    while (currentX != endX || currentY != endY) {
        if (board.getPieceAt(currentX, currentY) != nullptr) {
            return false;
        }
        currentX += xDirection;
        currentY += yDirection;
    }
    Piece* target = board.getPieceAt(endX, endY);
    return target == nullptr || target->isWhite() != m_isWhite;
}
