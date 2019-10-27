#ifndef COLLISIONPLATFORM_HPP
#define COLLISIONPLATFORM_HPP

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace sf;

class CollisionPlatform
{
    public:
        CollisionPlatform(float xCoords, float yCoords);
        Sprite getSprite();

        float getLeftSide();
        float getRightSide();
        float getTopSide();
        float getBottomSide();


        FloatRect getPosition();
    protected:

    private:


        float m_TopSide;
        float m_BottomSide;
        float m_LeftSide;
        float m_RightSide;

        Sprite m_Sprite;

        Texture m_Texture;

        Vector2f m_Position;
};

#endif // COLLISIONPLATFORM_HPP
