#include <bits/stdc++.h>
#include "../include/Piece.hpp"

using namespace std;

Piece::Piece(bool isWhite) : m_isWhite(isWhite) {}

bool Piece::isWhite() const {
    return m_isWhite;
}
