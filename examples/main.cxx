#include "bitboard.hxx"
#include "log.hxx"
#include <iostream>

int main()
{
    // std::cout << "Hello World!\n\n";
    chessops::log::init();
    chessops::Board board;

    chessops::Piece wB = chessops::WHITE_BISHOP;
    chessops::Piece bN = chessops::BLACK_KNIGHT;
    chessops::Piece wP = chessops::WHITE_PAWN;

    board.set_piece_at(wB, chessops::B4);
    board.set_piece_at(bN, chessops::B5);
    board.set_piece_at(bN, chessops::E4);
    board.set_piece_at(wP, chessops::E4);

    // std::cout << board.print();

    // chessops::Bitboard test_bb = 0;


    // for (chessops::Rank rank = chessops::RANK_8; rank >= chessops::RANK_1; --rank)
    // {
    //     for (chessops::File file = chessops::FILE_A; file <= chessops::FILE_H; ++file)
    //     {
    //         chessops::Square sq = chessops::make_square(file, rank);
    //         if (rank != chessops::RANK_1)
    //         {
    //             test_bb |= square_bitboard(sq);
    //         }
             
    //     }
    // }

    // std::cout << test_bb << "\n";
    // std::cout << board.print_bitboard(test_bb);



}
