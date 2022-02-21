#ifndef TYPES_H
#define TYPES_H
#define SIZE 8
#include <memory>
#include <array>

// This file contain support types and enumerate classes in order to extend code readability.
using possible_moves_type = std::array<std::array<bool, SIZE>, SIZE>;
using exchange_status = bool;

enum class Color{
    BLACK,
    WHITE
};

enum class Counter_type{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
#endif // TYPES_H
