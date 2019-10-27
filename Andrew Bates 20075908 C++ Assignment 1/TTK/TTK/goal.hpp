#ifndef GOAL_HPP
#define GOAL_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Goal
{
    public:
        Goal(float xCoords,float yCoords);
        Sprite getSprite();

        FloatRect getPosition();

        void setPosition(float xCoords, float yCoords);

    protected:

    private:

        Sprite m_Sprite;

        Texture m_Texture;

        Vector2f m_Position;
};

#endif // GOAL_HPP
