#ifndef TIMEEXTENSION_HPP
#define TIMEEXTENSION_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class TimeExtension
{
    public:
        TimeExtension(float xCoords,float yCoords);
        Sprite getSprite();

        FloatRect getPosition();

    protected:

    private:

        Sprite m_Sprite;

        Texture m_Texture;

        Vector2f m_Position;
};

#endif // TIMEEXTENSION_HPP
