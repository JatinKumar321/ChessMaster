#pragma once
#include <bits/stdc++.h>
using namespace std;

class Board;

class Piece {
public:
    Piece(bool isWhite);
    virtual ~Piece() = default;

    virtual string getSymbol() const = 0;
    virtual bool isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const = 0;
    bool isWhite() const;

protected:
    bool m_isWhite;
};
