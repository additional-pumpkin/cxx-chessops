#include "bitboard.hxx"
#include <log.hxx>
#include <iostream>
namespace chessops
{

    Bitboard not_a_file = 18374403900871474942ULL;
    Bitboard not_ab_file = 18229723555195321596ULL;
    Bitboard not_h_file = 9187201950435737471ULL;
    Bitboard not_gh_file = 4557430888798830399ULL;

    // FEN dedug positions
    #define empty_board "8/8/8/8/8/8/8/8 w - - "
    #define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
    #define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
    #define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
    #define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "



    
    Board::Board()
    {
        init();
    }

    std::string Board::print_bitboard(Bitboard bitboard)
    {
        std::string s = "   +---+---+---+---+---+---+---+---+\n";
        for(Rank rank = RANK_8; rank >= RANK_1; --rank)
        {
            s += std::to_string(rank + 1) + "  ";
            for(File file = FILE_A; file <= FILE_H; ++file)
            {
                Square square = make_square(file, rank);
                s += (bitboard & square_bitboard(square) ? "| X " : "|   ");
            }
            s += "|\n   +---+---+---+---+---+---+---+---+\n";
        }
        s += "     A   B   C   D   E   F   G   H\n";
        return s;
    
    }
    
    std::string Board::print()
    {
        std::string s;
        s += "by_piece:\n\n";
        for (PieceType p = PAWN; p <= KING; ++p)
        {
            s += piece_type_str.at(p) + "\n";
            s += print_bitboard(m_unique_position.by_type[p]);
        }
        s += "\n\n\nby_color:\n\n";
        s += "WHITE\n";
        s += print_bitboard(m_unique_position.by_color[WHITE]);
        s += "BLACK\n";
        s += print_bitboard(m_unique_position.by_color[BLACK]);
        s += print_board_symbols();
        s += "Side to move: " + color_str.at(m_unique_position.stm) + "\n";
        s += "En passant square: " + square_str.at(m_unique_position.ep) + "\n";
        return s;

    }
    
    std::string Board::print_board_symbols()
    {
        std::string s = "   +---+---+---+---+---+---+---+---+\n";
        std::string symbol;
        for(Rank rank = RANK_8; rank >= RANK_1; --rank)
        {
            s += std::to_string(rank + 1) + "  ";
            for(File file = FILE_A; file <= FILE_H; ++file)
            {
                Square square = make_square(file, rank);
                if ((symbol = get_piece_symbol(get_piece_at_from_bb(square))) != "x")
                  s += "| " + symbol + " ";
                else
                    s += "|   ";
            }
            s += "|\n   +---+---+---+---+---+---+---+---+\n";
        }
        s += "     A   B   C   D   E   F   G   H\n";
        return s;
        
    }
    
    void Board::clear_square(Square square)
    {
        if (square == SQUARE_NONE)
            return;
        for (PieceType p = PAWN; p <= KING; ++p)
            m_unique_position.by_type[p] &= ~square_bitboard(square);
        m_unique_position.by_color[WHITE] &= ~square_bitboard(square);
        m_unique_position.by_color[BLACK] &= ~square_bitboard(square);
    }
    void Board::set_piece_at(Piece piece, Square square)
    {
        clear_square(square);
        if (piece == PIECE_NONE || square == SQUARE_NONE)
            return;
        m_unique_position.by_type[type_of(piece)] |= square_bitboard(square);
        m_unique_position.by_color[color_of(piece)] |= square_bitboard(square);
        m_unique_position.board[square] = piece;
    }
    
    Piece Board::get_piece_at(Square square)
    {
        return m_unique_position.board[square];
    }
    
    void Board::set_ep_square(Square square)
    {
        m_unique_position.ep = square;
    }
    
    Square Board::get_ep_square(Square square)
    {
        return m_unique_position.ep;
    }
    
    bool Board::parse_fen(std::string fen, Position &position)
    {
        int curr_char = 0;
        // Field 1: parse piece positions
        for (Square square = A8; fen[curr_char] != ' '; )
        {
            char fen_char = fen[curr_char];
            // match ascii pieces within FEN string
            int id;
            // match empty square numbers within FEN string
            if (isdigit(fen_char))
            {
                // init offset (convert char 0 to int 0)
                int offset = fen_char - '0';
                
                // increment square and pointer to FEN string
                square = Square(square + offset);
                ++curr_char;
            }
            
            // match rank separator
            else if (fen_char == '/')
            {
                // increment pointer to FEN string
                ++curr_char;
                square = Square(square - 16);
            }
            else if ((id = fen_char_pieces.find(fen_char)) != std::string::npos)
            {
                // init piece type            
                // set piece on corresponding bitboard
                set_piece_at(Piece(id), square);
                
                // increment square and pointer to FEN string
                ++square;
                ++curr_char;
            }
            
            else
            {
                CHESSOPS_CORE_ERROR("Field 1: Malformed fen positions\n"); // error
                return false;
            }

        }
        ++curr_char;

        // Field 2: parse side to move
        if(fen[curr_char] == 'w' || fen[curr_char] == 'b')
        {

            position.stm = fen[curr_char] == 'w' ? WHITE : BLACK; 
            ++curr_char;
        }
        else
        {
            CHESSOPS_CORE_ERROR("Field 2: Invalid side to move\n"); // error
            return false;
        }

        if (fen[curr_char] != ' ')
        {
            CHESSOPS_CORE_ERROR("Field 2: There should be a space at the end of field 2\n"); // error
            return false;
        }

        ++curr_char;

        // Field 3: parse castling rights

        while (fen[curr_char] != ' ')
        {
            switch (fen[curr_char])
            {
            case '-': position.castling_rights =  CASTLING_NONE;      break;
            case 'K': position.castling_rights |= WHITE_CASTLING_OO;  break;
            case 'Q': position.castling_rights |= WHITE_CASTLING_OOO; break;
            case 'k': position.castling_rights |= BLACK_CASTLING_OO;  break;
            case 'q': position.castling_rights |= BLACK_CASTLING_OOO; break;

            default: CHESSOPS_CORE_ERROR("Field 3: Invalid character: {0}", fen[curr_char]); break;
            }
            ++curr_char;

        }
        ++curr_char;
        // Field 4: parse enpassant square
        if (fen[curr_char] != '-')
        {
            if(fen[curr_char] >= 'a' && fen[curr_char] <= 'h' && fen[curr_char +1] >= '1' && fen[curr_char + 1] <= '8')
            {
                File f = File(fen[curr_char] - 'a');
                Rank r = Rank(fen[curr_char + 1] - '1');
                position.ep = make_square(f, r); 
                curr_char += 2;
            }
            else
            {
                CHESSOPS_CORE_ERROR("Field 4: Invalid en passant square\n"); // error
                return false;
            }
        }
        else
        {
            position.ep = SQUARE_NONE;
            ++curr_char;
        }

        return true;
    }
    
    Piece Board::get_piece_at_from_bb(Square s)
    {
        bool is_white = false;
        if (m_unique_position.by_color[WHITE] & square_bitboard(s))
            is_white = true;

        if (m_unique_position.by_type[PAWN] &  square_bitboard(s))
        {
            if (is_white)
                return WHITE_PAWN;
            else
                return BLACK_PAWN;
        }   

        if (m_unique_position.by_type[KNIGHT] & square_bitboard(s))
        {
            if (is_white)
                return WHITE_KNIGHT;
            else
                return BLACK_KNIGHT;
        }

        if (m_unique_position.by_type[BISHOP] & square_bitboard(s))
        {
            if (is_white)
                return WHITE_BISHOP;
            else
                return BLACK_BISHOP;
        }

        if (m_unique_position.by_type[ROOK] & square_bitboard(s))
        {
            if (is_white)
                return WHITE_ROOK;
            else
                return BLACK_ROOK;
        }

        if (m_unique_position.by_type[KING] & square_bitboard(s))
        {
            if (is_white)
                return WHITE_KING;
            else
                return BLACK_KING;
        }

        if (m_unique_position.by_type[QUEEN] & square_bitboard(s))
        {
            if (is_white)
                return WHITE_QUEEN;
            else
                return BLACK_QUEEN;
        }
        return PIECE_NONE;
    }
    
    void Board::init()
    {
        init_leaper_attacks();
        for (Square sq = A1; sq <= H8; ++sq)
        {
            m_unique_position.board[sq] = PIECE_NONE;
            // std::cout << print_bitboard();
            

        }
        m_unique_position.castling_rights = CASTLING_ALL;
        set_ep_square(SQUARE_NONE);
        set_stm(COLOR_NONE);
        UniquePosition position;
        parse_fen(start_position, position);
        // CHESSOPS_CORE_TRACE(print());

        CHESSOPS_CORE_CRITICAL("This is very bad");
        CHESSOPS_CORE_ERROR("This is an error");
        CHESSOPS_CORE_WARN("This is a warning");
        CHESSOPS_CORE_INFO("This is an info");
        CHESSOPS_CORE_TRACE("This is a trace");

    }
    
    void Board::init_leaper_attacks()
    {
        for (Square sq = A1; sq <= H8; ++sq)
        {
        // pawn attacks
            m_pawn_attacks[WHITE][sq] |= square_bitboard((sq + NORTH_EAST)) & not_a_file;
            m_pawn_attacks[WHITE][sq] |= square_bitboard((sq + NORTH_WEST)) & not_h_file;
            m_pawn_attacks[BLACK][sq] |= square_bitboard((sq + SOUTH_EAST)) & not_a_file;
            m_pawn_attacks[BLACK][sq] |= square_bitboard((sq + SOUTH_WEST)) & not_h_file;            

        // knight attacks
            m_knight_attacks[sq] |= square_bitboard((sq + NORTH + NORTH_EAST)) & not_a_file;
            m_knight_attacks[sq] |= square_bitboard((sq + NORTH + NORTH_WEST)) & not_h_file;
            m_knight_attacks[sq] |= square_bitboard((sq + EAST + NORTH_EAST)) & not_ab_file;
            m_knight_attacks[sq] |= square_bitboard((sq + WEST + NORTH_WEST)) & not_gh_file;
            m_knight_attacks[sq] |= square_bitboard((sq + SOUTH + SOUTH_EAST)) & not_h_file;
            m_knight_attacks[sq] |= square_bitboard((sq + SOUTH + SOUTH_WEST)) & not_a_file;
            m_knight_attacks[sq] |= square_bitboard((sq + WEST + SOUTH_WEST)) & not_gh_file;
            m_knight_attacks[sq] |= square_bitboard((sq + EAST + SOUTH_EAST)) & not_ab_file;
        
        // king attacks
            m_king_attacks[sq] |= square_bitboard((sq + EAST))       & not_a_file;
            m_king_attacks[sq] |= square_bitboard((sq + NORTH_EAST)) & not_a_file;
            m_king_attacks[sq] |= square_bitboard((sq + NORTH));
            m_king_attacks[sq] |= square_bitboard((sq + NORTH_WEST)) & not_h_file;
            m_king_attacks[sq] |= square_bitboard((sq + WEST))       & not_h_file;
            m_king_attacks[sq] |= square_bitboard((sq + SOUTH_WEST)) & not_h_file;
            m_king_attacks[sq] |= square_bitboard((sq + SOUTH));
            m_king_attacks[sq] |= square_bitboard((sq + SOUTH_EAST)) & not_a_file;
        }
    }
} // namespace chessops