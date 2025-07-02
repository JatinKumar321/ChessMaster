#pragma once
#include <bits/stdc++.h>
#include "Piece.hpp"

using namespace std;

class Knight : public Piece {
public:
    Knight(bool isWhite);
    string getSymbol() const override;
    bool isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const override;
};
