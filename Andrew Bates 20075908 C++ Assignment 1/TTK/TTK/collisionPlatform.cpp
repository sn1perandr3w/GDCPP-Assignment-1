#include "collisionPlatform.hpp"
#include "textureHolder.hpp"

//Constructor which sets the sprite and different sides of the platform.

CollisionPlatform::CollisionPlatform(float xCoords, float yCoords)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "graphics/platform.png"));
    m_Sprite.setPosition(xCoords,yCoords);

    m_TopSide = m_Sprite.getPosition().y;
    m_BottomSide = m_Sprite.getPosition().y + m_Sprite.getLocalBounds().height;
    m_LeftSide = m_Sprite.getPosition().x;
    m_RightSide = m_Sprite.getPosition().x + m_Sprite.getLocalBounds().width;
}


//Getting sides

float CollisionPlatform::getLeftSide()
{
    return m_LeftSide;
}

float CollisionPlatform::getRightSide()
{
    return m_RightSide;
}

float CollisionPlatform::getTopSide()
{
    return m_TopSide;
}

float CollisionPlatform::getBottomSide()
{
    return m_BottomSide;
}

//Getting position

FloatRect CollisionPlatform::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

//Getting sprite

Sprite CollisionPlatform::getSprite()
{
    return m_Sprite;
}
