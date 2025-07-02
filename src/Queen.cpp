#include <bits/stdc++.h>
#include "../include/Queen.hpp"
#include "../include/Rook.hpp"
#include "../include/Bishop.hpp"

using namespace std;

Queen::Queen(bool isWhite) : Piece(isWhite) {}

string Queen::getSymbol() const {
    return m_isWhite ? "♕" : "♛";  // White: outline, Black: filled
}

bool Queen::isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const {
    Rook tempRook(m_isWhite);
    Bishop tempBishop(m_isWhite);
    return tempRook.isMoveValid(startX, startY, endX, endY, board) || tempBishop.isMoveValid(startX, startY, endX, endY, board);
}
