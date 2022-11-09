#pragma once

#include <cstdint>
#include <string>
#include <array>

namespace chessops
{
    const std::array<std::string, 3> color_str =
    {
        "WHITE", "BLACK", "COLOR_NONE"
    };
    const std::array<std::string, 13> piece_str =
    {
        "WHITE_PAWN", "WHITE_KNIGHT", "WHITE_BISHOP", "WHITE_ROOK", "WHITE_QUEEN", "WHITE_KING",
        "BLACK_PAWN", "BLACK_KNIGHT", "BLACK_BISHOP", "BLACK_ROOK", "BLACK_QUEEN", "BLACK_KING",
        "PIECE_NONE",
    };
    const std::array<std::string, 13> piece_symbol = 
    {
       "♙","♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚", "x"
    };
    const std::array<std::string, 7> piece_type_str =
    {
        "PAWN", "KNIGHT", "BISHOP", "ROOK", "QUEEN", "KING","PIECE_TYPE_NONE",
    };
    const std::array<std::string, 65> square_str = 
    {
        "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
        "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
        "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
        "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
        "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
        "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
        "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
        "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
        "SQUARE_NONE"
    };


    typedef std::uint64_t Bitboard;

    enum Square: int
    {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        SQUARE_NONE
    };

    const std::string fen_char_pieces = "PNBRQKpnbrqkx";
    enum Rank: int
    {
        RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
    };
    enum File: int
    {
        FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H
    };
    enum Piece
    {
        WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
        BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING,
        PIECE_NONE,

    };
    enum PieceType
    {
        PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_TYPE_NONE,
    };

    enum Color
    {
        WHITE, BLACK, COLOR_NONE
    };

    enum Direction : int
    {
        NORTH =  8,
        EAST  =  1,
        SOUTH = -NORTH,
        WEST  = -EAST,
        NORTH_EAST = NORTH + EAST,
        SOUTH_EAST = SOUTH + EAST,
        SOUTH_WEST = SOUTH + WEST,
        NORTH_WEST = NORTH + WEST
    };

    enum CastlingRights : int
    {
        CASTLING_NONE = 0,
        WHITE_CASTLING_OOO = 1,
        WHITE_CASTLING_OO = WHITE_CASTLING_OOO << 1,
        BLACK_CASTLING_OOO = WHITE_CASTLING_OOO << 2,
        BLACK_CASTLING_OO = WHITE_CASTLING_OOO << 3,
        WHITE_CASTLING_ALL = WHITE_CASTLING_OOO | WHITE_CASTLING_OO,
        BLACK_CASTLING_ALL = BLACK_CASTLING_OOO | BLACK_CASTLING_OO,
        CASTLING_OO = WHITE_CASTLING_OO | BLACK_CASTLING_OO,
        CASTLING_OOO = WHITE_CASTLING_OOO | BLACK_CASTLING_OOO,
        CASTLING_ALL = WHITE_CASTLING_ALL | BLACK_CASTLING_ALL


    };
    
    inline Rank& operator++(Rank& d) { return d = Rank(int(d) + 1); }
    inline Rank& operator--(Rank& d) { return d = Rank(int(d) - 1); }

    inline File& operator++(File& d) { return d = File(int(d) + 1); }
    inline File& operator--(File& d) { return d = File(int(d) - 1); }

    inline Square& operator++(Square& d) { return d = Square(int(d) + 1); }
    inline Square& operator--(Square& d) { return d = Square(int(d) - 1); }

    inline Piece& operator++(Piece& d) { return d = Piece(int(d) + 1); }
    inline Piece& operator--(Piece& d) { return d = Piece(int(d) - 1); }

    inline PieceType& operator++(PieceType& d) { return d = PieceType(int(d) + 1); }
    inline PieceType& operator--(PieceType& d) { return d = PieceType(int(d) - 1); }

    inline Square& operator+(Square &s, Direction &d) { return s = Square(int(s) + int(d)); }

    inline Square make_square(File f, Rank r)
    {
        return Square(r * 8 + f);
    }

    inline PieceType type_of(Piece p)
    {
        return PieceType(p >= 6 ? p - 6 : p);
    }

    inline Color color_of(Piece p)
    {
        return Color(p == PIECE_NONE ? COLOR_NONE : p >= 6 ? BLACK : WHITE);
    }

    inline std::string get_piece_symbol(Piece p)
    {
        return fen_char_pieces.substr(p,1);
    }


    #define square_bitboard(s) (1ULL << s)
    
    #define popcount(x) __builtin_popcountll(x)

    #define ls1b(x) popcount((x & -x) - 1)

} // namespace chessops

