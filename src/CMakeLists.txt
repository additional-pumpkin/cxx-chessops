add_library(chessops
    bitboard.cxx
    log.cxx
)


target_include_directories(
    chessops 
PUBLIC
    ../vendor/spdlog/include
)