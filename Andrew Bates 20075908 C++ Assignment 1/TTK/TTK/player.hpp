#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "collisionPlatform.hpp"

//#include <iostream>

using namespace sf;

class Player
{
    public:

        Player(float xCoords, float yCoords);
        Sprite getSprite();

        void moveLeft();
        void moveRight();

        void stopLeft();
        void stopRight();

        void jump();
        void stopJump();

        void dash();
        void stopDash();

        // We will call this function once every frame
        void update(float elapsedTime);


        float getLeftSide();
        float getRightSide();
        float getTopSide();
        float getBottomSide();


        FloatRect getPosition();

        bool getCanMoveLeft();
        bool getCanMoveRight();
        bool getCanMoveUp();
        bool getCanMoveDown();

        bool determineDown(std::vector<CollisionPlatform> platforms);
        bool determineUp(std::vector<CollisionPlatform> platforms);
        bool determineLeft(std::vector<CollisionPlatform> platforms);
        bool determineRight(std::vector<CollisionPlatform> platforms);

        void setCanMoveLeft();
        void setCanMoveRight();
        void setCanMoveUp();
        void setCanMoveDown();

        void stopCanMoveLeft();
        void stopCanMoveRight();
        void stopCanMoveUp();
        void stopCanMoveDown();

        void setPosition(float xCoords, float yCoords);


        Vector2f getCenter();



    protected:

    private:

        // Which directions is the player currently moving in
        float m_DashMult;

        bool m_LeftPressed;
        bool m_RightPressed;

        bool m_JumpPressed;

        bool m_DashPressed;

        bool m_falling;
        bool m_jumping;
        bool m_standing;

        int m_Health;

        float m_TopSide;
        float m_BottomSide;
        float m_LeftSide;
        float m_RightSide;

        float m_JumpTimer;

        Sprite m_Sprite;

        Texture m_Texture;

        Vector2f m_Position;
        Vector2f m_Center;

        bool m_CanMoveLeft;
        bool m_CanMoveRight;
        bool m_CanMoveUp;
        bool m_CanMoveDown;



};

#endif // PLAYER_HPP
