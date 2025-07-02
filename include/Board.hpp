#pragma once
#include <bits/stdc++.h>
#include "Piece.hpp"

using namespace std;

class Board {
public:
    Board();                    // Setup board
    ~Board();                   // Cleanup pieces

    void display() const;       // Show board
    bool move(const string& from, const string& to, bool whiteTurn); // Make move
    
    bool isCheck(bool isWhite) const;           // King attacked?
    bool isCheckmate(bool isWhite);             // No moves + check?
    bool isStalemate(bool isWhite);             // No moves + no check?
    
    bool isInsufficientMaterial() const;        // Draw by material?
    bool isThreefoldRepetition();               // Draw by repetition?
    bool isFiftyMoveRule() const;               // Draw by 50 moves?
    
    Piece* getPieceAt(int x, int y) const;      // Get piece
    void promotePawn(int x, int y, char pieceType); // Promote pawn
    
    bool canCastle(bool isWhite, bool kingSide);        // Can castle?
    bool performCastle(bool isWhite, bool kingSide);    // Do castle
    bool canEnPassant(int startX, int startY, int endX, int endY) const;  // Can en passant?
    bool performEnPassant(int startX, int startY, int endX, int endY);    // Do en passant

private:
    void setupBoard();                          // Place pieces
    string getBoardHash();                 // Board fingerprint
    bool hasOnlyKingsAndMinorPieces() const;   // Material check
    
    vector<vector<Piece*>> m_board;   // 8x8 board
    
    // Castling flags
    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRookKingSideMoved;
    bool whiteRookQueenSideMoved;
    bool blackRookKingSideMoved;
    bool blackRookQueenSideMoved;
    
    // En passant tracking
    int enPassantTargetX;
    int enPassantTargetY;
    bool enPassantAvailable;
    
    // Draw rules
    map<string, int> boardPositions;  // Position history
    int halfMoveClock;                          // Move counter
};
