#include <iostream>

#include "Board/Board.h"
#include "MoveGeneration/MoveGeneration.h"
#include "MoveGeneration/NonSlidingPieces.h"

using namespace ChessEngine;

int main() {
    BoardState state = {};
    std::string fenPosition = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";
    if(!ParseFenString(fenPosition, state)){
        std::cout << "Incorrect fen string" << std::endl;
        return -1;
    }

    Board board(state);

    MoveGeneration::GeneratePseudoMoves(board.GetState(), Color::White, board.GetOccupancies());

    return 0;
}
