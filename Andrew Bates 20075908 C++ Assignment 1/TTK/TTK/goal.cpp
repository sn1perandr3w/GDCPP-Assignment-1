#include "goal.hpp"
#include "textureHolder.hpp"
#include "ResourcePath.hpp"

//Constructor which sets the sprite of the goal and its position

Goal::Goal(float xCoords, float yCoords)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "graphics/goal.png"));
    m_Sprite.setPosition(xCoords,yCoords);
}

//Getting goal position

FloatRect Goal::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

//Getting sprite

Sprite Goal::getSprite()
{
    return m_Sprite;
}

//Setting position

void Goal::setPosition(float xCoords, float yCoords)
{
    m_Position.x = xCoords;
    m_Position.y = yCoords;
    m_Sprite.setPosition(m_Position);
}
