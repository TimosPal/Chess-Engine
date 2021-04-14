#ifndef PSEUDO_MOVES_H
#define PSEUDO_MOVES_H

#include <list>

#include "../Board/BoardState.h"
#include "../Board/BoardUtilities.h"
#include "Move.h"

namespace ChessEngine::MoveGeneration::Pseudo {

    /* The pseudo moves should be checked for validity afterwards. */
    std::list<Move> GetAllMoves(const BoardState &state, Color color, const BoardUtilities& utilities);
    std::list<Move> GetPawnMoves(const BoardState &state, Color color, const BoardUtilities& utilities);
    std::list<Move> GetKingMoves(const BoardState &state, Color color, const BoardUtilities& utilities);
    std::list<Move> GetCastlingMoves(const BoardState &state, Color color, const BoardUtilities& utilities);
    std::list<Move> GetKnightMoves(const BoardState &state, Color color, const BoardUtilities& utilities);
    std::list<Move> GetSlidingMoves(const BoardState &state, Color color, PieceType type, const BoardUtilities& utilities);
    std::list<Move> GetEnPassantMoves(const BoardState &state, Color color, const BoardUtilities& utilities);

}

#endif