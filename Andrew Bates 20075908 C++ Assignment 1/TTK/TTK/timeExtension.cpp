#include "timeExtension.hpp"
#include "textureHolder.hpp"
#include "ResourcePath.hpp"

//Constructor setting the sprite and its coordinates.

TimeExtension::TimeExtension(float xCoords, float yCoords)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "graphics/timeExtension.png"));
    m_Sprite.setPosition(xCoords,yCoords);
}

//Getting the position

FloatRect TimeExtension::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

//Getting the sprite.

Sprite TimeExtension::getSprite()
{
    return m_Sprite;
}
