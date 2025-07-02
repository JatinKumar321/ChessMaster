#pragma once
#include <string>

// Represents a position on the chess board

class Position {
public:
    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}
    
    int row;
    int col;
    
    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    
    // Convert from chess notation (e.g., "e4" -> Position(4, 4))
    static Position fromChessNotation(const std::string& notation);
    
    // Convert to chess notation (e.g., Position(4, 4) -> "e4")
    std::string toChessNotation() const;
};
