#pragma once

#include "types.hxx"
#include <algorithm>
#include <Pext.hpp>

namespace chessops
{
// inspired by scidb
// Copyright: (C) 2009-2017 Gregor Cramer

struct SimplePosition
{

    SimplePosition(): by_type{0}, by_color{0} {}
    Bitboard by_type[6];
    Bitboard by_color[2];
};

struct Position : public SimplePosition
{
    Position() { std::fill(&board[0], &board[0] + sizeof(board) / sizeof(board[0]), PIECE_NONE); }
    Piece board[64]; // faster piece retrieval
};

struct ExactPosition: public Position
{
    ExactPosition(): stm(COLOR_NONE), ep(SQUARE_NONE), castling_rights(CASTLING_NONE) {}
    Color stm;
    Square ep; // enpassant square
    uint8_t castling_rights;

};


struct UniquePosition : public ExactPosition
{
	uint32_t	half_move_clock;	// number of moves since last pawn move or capture
	uint32_t	ply_number;		// ply number in game (incremented after each half move)
};

// A bitboard based board representation
class Board
{
public:
    Board();

    static std::string print_bitboard(Bitboard bitboard);
    std::string print();
    std::string print(const Position &position);
    std::string print(const ExactPosition &position);
    std::string print(const UniquePosition &position);
    std::string print_board_symbols();
    std::string print_board_symbols(const Position &position);

    void clear_square(Square square); 

    void set_piece_at(Piece piece, Square square);
    void set_piece_at(Piece piece, Square square, Position &position);

    Piece get_piece_at(Square square);
    Piece get_piece_at(Square square, const Position &position);
    void set_ep_square(Square square);
    Square get_ep_square(Square square);
private:
    // all parse_fen methods assume fen is valid
    bool parse_fen(std::string fen, UniquePosition &position); // returns false if it fails
    bool parse_fen(std::string fen, ExactPosition &position); // returns false if it fails
    bool parse_fen(std::string fen, Position &position); // returns false if it fails
    void set_stm(Color color) { m_unique_position.stm = color;} // sets side to move
    
    Bitboard get_rook_attacks(Square square, Bitboard occupancy) { return Chess_Lookup::Lookup_Pext::Rook(square, occupancy); }
    Bitboard get_bishop_attacks(Square square, Bitboard occupancy) { return Chess_Lookup::Lookup_Pext::Bishop(square, occupancy); }
    Bitboard get_queen_attacks(Square square, Bitboard occupancy) { return Chess_Lookup::Lookup_Pext::Queen(square, occupancy); }

    void init();
    void init_leaper_attacks();

    UniquePosition m_unique_position;
    
    Piece get_piece_at_from_bb(Square s);

    // leaper attacks precalculated
    Bitboard m_pawn_attacks[2][64];
    Bitboard m_knight_attacks[64];
    Bitboard m_king_attacks[64];



};
} // namespace chessops