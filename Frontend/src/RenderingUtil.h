#ifndef RENDERING_UTIL_H
#define RENDERING_UTIL_H

#include <list>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Engine/Board/BoardState.h>
#include <Engine/MoveGeneration/Move.h>

namespace ChessFrontend::RenderingUtil {

    void DrawCheckerBoard(sf::RenderWindow &window);

    void DrawPieces(sf::RenderWindow &window, ChessEngine::BoardState state, bool isHolding, sf::Vector2i fromPos);

    void ScalePieceSprite(sf::Sprite &sprite, sf::Vector2i targetScale);

    void DrawHoldingPiece(sf::RenderWindow &window, sf::Sprite &holdingSprite);

    void DrawActivePieceMoves(sf::RenderWindow &window, std::list<ChessEngine::MoveGeneration::Move> activePieceMoves);

}

#endif
