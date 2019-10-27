#include "TimeRemover.hpp"
#include "textureHolder.hpp"
#include "ResourcePath.hpp"

//Constructor setting the sprite and its coordinates.

TimeRemover::TimeRemover(float xCoords, float yCoords)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "graphics/timeRemover.png"));
    m_Sprite.setPosition(xCoords,yCoords);
}

//Getting the position

FloatRect TimeRemover::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

//Getting the sprite.

Sprite TimeRemover::getSprite()
{
    return m_Sprite;
}
