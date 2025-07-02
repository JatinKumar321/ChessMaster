#include <bits/stdc++.h>
#include "../include/Bishop.hpp"
#include "../include/Board.hpp"

using namespace std;

Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

string Bishop::getSymbol() const {
    return m_isWhite ? "♗" : "♝";  // White: outline, Black: filled
}

bool Bishop::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    if (abs(startX - endX) != abs(startY - endY)) {
        return false;
    }
    int xDirection = (endX > startX) ? 1 : -1;
    int yDirection = (endY > startY) ? 1 : -1;
    int currentX = startX + xDirection;
    int currentY = startY + yDirection;
    while (currentX != endX) {
        if (board.getPieceAt(currentX, currentY) != nullptr) {
            return false;
        }
        currentX += xDirection;
        currentY += yDirection;
    }
    Piece* target = board.getPieceAt(endX, endY);
    return target == nullptr || target->isWhite() != m_isWhite;
}
