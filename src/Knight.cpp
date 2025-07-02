#include <bits/stdc++.h>
#include "../include/Knight.hpp"
#include "../include/Board.hpp"

using namespace std;

Knight::Knight(bool isWhite) : Piece(isWhite) {}

string Knight::getSymbol() const {
    return m_isWhite ? "♘" : "♞";  // White: outline, Black: filled
}

bool Knight::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        Piece* target = board.getPieceAt(endX, endY);
        return target == nullptr || target->isWhite() != m_isWhite;
    }
    return false;
}
