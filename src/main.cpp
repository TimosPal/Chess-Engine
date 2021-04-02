#include <iostream>

#include "FenParser/FenParser.h"
#include "Board/Board.h"
#include "MoveGeneration/MoveGeneration.h"
#include "MoveGeneration/MoveTables.h"
#include "MoveGeneration/SlidingPieces.h"

using namespace ChessEngine;
using namespace ChessEngine::BitboardUtil;

int main() {
    InitEngine(); // Should be called first.

    BoardState state = {};
    std::string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    if(!ParseFenString(fenPosition, state)){
        std::cout << "Incorrect fen string" << std::endl;
        return -1;
    }

    Board board(state);
    //board.Draw();

    Bitboard b = board.GetOccupancies()[2]; // TODO: rook 4 corners.
    Bitboard a = MoveGeneration::MoveTables::GetBishopMoves(GetSquareIndex(File::E, Rank::R3) , 0);
    DrawBitBoard(a);

    return 0;
}
