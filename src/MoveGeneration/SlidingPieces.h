#ifndef SLIDINGPIECES_H
#define SLIDINGPIECES_H

#include "../Board/Bitboard.h"

namespace ChessEngine::SlidingPieces {

    using namespace Bitboard_Util;

    // NOTE: performance isn't crucial for these functions
    // since they are run once when producing the tables.

    /*******************************************************/
    /* General                                             */
    /*******************************************************/

    /* Generate a move table based on the given function for each board position. */
    constexpr std::array<Bitboard, 64> InitMasksTable(Bitboard getMask(File, Rank)) {
        std::array<Bitboard, 64> mask = {};

        for (uint8_t rank = 0; rank < 8; rank++) {
            for (uint8_t file = 0; file < 8; file++) {
                uint8_t squareIndex = GetSquareIndex(file, rank);
                mask[squareIndex] = getMask((File)file, (Rank)rank);
            }
        }

        return mask;
    }

    /* Generate a mask based on an initial position and direction */
    constexpr Bitboard GetDirectionalBlockerMask(File file, Rank rank, int8_t dirX, int8_t dirY){
        // Exclude outer edges.
        Bitboard mask = BITBOARD_EMPTY;
        int x = file + dirX, y = rank + dirY;
        while(x > 0 && x < 7 && y > 0 && y < 7) {
            mask |= SetBit(BITBOARD_EMPTY, GetSquareIndex(x, y));
            x += dirX;
            y += dirY;
        }

        return mask;
    }

    /* Generate an attack mask based on an initial position , direction and occupancies */
    constexpr Bitboard GetDirectionalMoves(File file, Rank rank, int8_t dirX, int8_t dirY, Bitboard occupancies){
        // Include outer edges if not blocked till that point.
        Bitboard mask = BITBOARD_EMPTY;
        int x = file + dirX, y = rank + dirY;
        while(x >= 0 && x <= 7 && y >= 0 && y <= 7) {
            Bitboard currentBit = SetBit(BITBOARD_EMPTY, GetSquareIndex(x, y));
            mask |= currentBit;

            // We found a piece and we should stop.
            if((currentBit & occupancies) != 0)
                break;

            x += dirX;
            y += dirY;
        }

        return mask;
    }

    /*******************************************************/
    /* Rook                                                */
    /*******************************************************/

    constexpr Bitboard GetRookBlockerMask(File file, Rank rank){
        Bitboard mask = BITBOARD_EMPTY;

        mask |= GetDirectionalBlockerMask(file, rank, 0, 1);
        mask |= GetDirectionalBlockerMask(file, rank, 0, -1);
        mask |= GetDirectionalBlockerMask(file, rank, 1, 0);
        mask |= GetDirectionalBlockerMask(file, rank, -1, 0);

        return mask;
    }

    constexpr Bitboard GetRookMoves(File file, Rank rank, Bitboard occupancies){
        Bitboard mask = BITBOARD_EMPTY;

        mask |= GetDirectionalMoves(file, rank, 0, 1, occupancies);
        mask |= GetDirectionalMoves(file, rank, 0, -1, occupancies);
        mask |= GetDirectionalMoves(file, rank, 1, 0, occupancies);
        mask |= GetDirectionalMoves(file, rank, -1, 0, occupancies);

        // Exclude self.
        return mask;
    }

    /*******************************************************/
    /* Bishop                                              */
    /*******************************************************/

    constexpr Bitboard GetBishopBlockerMask(File file, Rank rank){
        Bitboard mask = BITBOARD_EMPTY;

        mask |= GetDirectionalBlockerMask(file, rank, 1, 1);
        mask |= GetDirectionalBlockerMask(file, rank, 1, -1);
        mask |= GetDirectionalBlockerMask(file, rank, -1, 1);
        mask |= GetDirectionalBlockerMask(file, rank, -1, -1);

        return mask;
    }

    constexpr Bitboard GetBishopMoves(File file, Rank rank, Bitboard occupancies){
        Bitboard mask = BITBOARD_EMPTY;

        mask |= GetDirectionalMoves(file, rank, 1, 1, occupancies);
        mask |= GetDirectionalMoves(file, rank, 1, -1, occupancies);
        mask |= GetDirectionalMoves(file, rank, -1, 1, occupancies);
        mask |= GetDirectionalMoves(file, rank, -1, -1, occupancies);

        // Exclude self.
        return mask;
    }

    /*******************************************************/
    /* Attack masks                                        */
    /*******************************************************/

    constexpr std::array<Bitboard, 64> rookMasks = InitMasksTable(GetRookBlockerMask);
    constexpr std::array<Bitboard, 64> bishopMasks = InitMasksTable(GetBishopBlockerMask);


}

#endif