#ifndef TYPES_HPP
#define TYPES_HPP

enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum class Color {
    WHITE,
    BLACK
};

// ANSI Color codes for terminal
namespace Colors {
    inline const char* RESET = "\033[0m";
    inline const char* BOLD = "\033[1m";
    inline const char* RED = "\033[31m";
    inline const char* GREEN = "\033[32m";
    inline const char* YELLOW = "\033[33m";
    inline const char* BLUE = "\033[34m";
    inline const char* MAGENTA = "\033[35m";
    inline const char* CYAN = "\033[36m";
    inline const char* WHITE = "\033[37m";
    inline const char* BLACK = "\033[30m";
    
    // Background colors
    inline const char* BG_WHITE = "\033[47m";
    inline const char* BG_BLACK = "\033[40m";
    inline const char* BG_LIGHT_GRAY = "\033[47m";
    inline const char* BG_DARK_GRAY = "\033[100m";
}

#endif // TYPES_HPP