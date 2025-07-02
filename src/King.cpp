#include <bits/stdc++.h>
#include "../include/King.hpp"
#include "../include/Board.hpp"

using namespace std;

King::King(bool isWhite) : Piece(isWhite) {}

string King::getSymbol() const {
    return m_isWhite ? "♔" : "♚";  // White: outline, Black: filled
}

bool King::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    if (dx <= 1 && dy <= 1) {
        Piece* target = board.getPieceAt(endX, endY);
        return target == nullptr || target->isWhite() != m_isWhite;
    }
    return false;
}
