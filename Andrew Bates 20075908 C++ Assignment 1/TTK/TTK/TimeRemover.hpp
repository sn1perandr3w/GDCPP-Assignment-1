#ifndef TIMEREMOVER_HPP
#define TIMEREMOVER_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class TimeRemover
{
    public:
        TimeRemover(float xCoords,float yCoords);
        Sprite getSprite();

        FloatRect getPosition();

    protected:

    private:

        Sprite m_Sprite;

        Texture m_Texture;

        Vector2f m_Position;
};

#endif // TIMEREMOVER_HPP
