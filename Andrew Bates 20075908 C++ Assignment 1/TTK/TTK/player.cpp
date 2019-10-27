#include "player.hpp"
#include "textureHolder.hpp"
#include <iostream>
#include "ResourcePath.hpp"
//Constructor which sets the sprite, position through coordinates, jump timer, dash multiplier, booleans for movement, sides for collision detection and center for the view.

Player::Player(float xCoords, float yCoords)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "graphics/player.png"));
    m_Position.x = xCoords;
    m_Position.y = yCoords;
    m_Sprite.setPosition(m_Position);

    m_JumpTimer = 0.0f;

    m_DashMult = 1.0f;

    m_CanMoveLeft = true;
    m_CanMoveRight = true;
    m_CanMoveDown = true;

    m_falling = true;




    m_TopSide = m_Sprite.getPosition().y;
    m_BottomSide = m_Sprite.getPosition().y + m_Sprite.getLocalBounds().height;
    m_LeftSide = m_Sprite.getPosition().x;
    m_RightSide = m_Sprite.getPosition().x + m_Sprite.getLocalBounds().width;

    m_Center.x = ((m_Sprite.getPosition().x + (m_Sprite.getLocalBounds().width)/2));
    m_Center.y = ((m_Sprite.getPosition().y + (m_Sprite.getLocalBounds().height)/2));
}

//Setting player position

void Player::setPosition(float xCoords, float yCoords)
{
    m_Position.x = xCoords;
    m_Position.y = yCoords;
    m_Sprite.setPosition(m_Position);
}

//Functions for flagging player movement in directions

void Player::moveLeft()
{
    m_LeftPressed = true;
}

void Player::moveRight()
{
    m_RightPressed = true;
}
void Player::stopLeft()
{
    m_LeftPressed = false;
}

void Player::stopRight()
{
    m_RightPressed = false;
}

//Function for flagging jumping state

void Player::jump()
{
    m_JumpPressed = true;
}

void Player::stopJump()
{
    m_JumpPressed = false;
}

//Functions for flagging dashing state

void Player::dash()
{
    m_DashPressed = true;
}

void Player::stopDash()
{
    m_DashPressed = false;
}


//Update collision, position, center, gravity and movement based on pressed keys.

void Player::update(float elapsedTime)
{

    m_TopSide = m_Sprite.getPosition().y;
    m_BottomSide = m_Sprite.getPosition().y + m_Sprite.getLocalBounds().height;
    m_LeftSide = m_Sprite.getPosition().x;
    m_RightSide = m_Sprite.getPosition().x + m_Sprite.getLocalBounds().width;



    m_Center.x = ((m_Sprite.getPosition().x + (m_Sprite.getLocalBounds().width)/2));
    m_Center.y = ((m_Sprite.getPosition().y + (m_Sprite.getLocalBounds().height)/2));


    if(m_DashPressed == true)
        {
            m_DashMult = 3.0f;
        }
    else
        {
            m_DashMult = 1.0f;
        }

    if(m_CanMoveDown == true && m_jumping == false)
        {
            m_falling = true;
        }
        else
            {
                m_falling = false;
            }

    if(m_JumpTimer > 0.0f)
    {
        m_JumpTimer -= elapsedTime;
    }



    if (m_RightPressed)
    {
        m_Position.x += (90.0f * m_DashMult) * elapsedTime;
    }

    if (m_LeftPressed)
    {
        m_Position.x -= (90.0f * m_DashMult) * elapsedTime;
    }

    if (m_JumpPressed == true && m_falling == false && m_jumping == false)
    {
        m_jumping = true;
        m_JumpTimer = 1.2f;
    }


    if(m_falling == true)
    {
        m_Position.y += 360.0f * elapsedTime;
    }

    if(m_jumping == true)
    {
        if(m_JumpPressed == true)
        {
            if(m_JumpTimer > 0.0f)
            {
                m_Position.y -= 360.0f * elapsedTime;
            }
            else
            {

                m_falling = true;
                m_jumping = false;
                m_CanMoveDown = true;
            }
        }
        else
        {
            m_falling = true;
            m_jumping = false;
            m_CanMoveDown = true;
        }
    }


    m_Sprite.setPosition(m_Position);
}


//Returns player position

FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}


//Bools for player movement states.

bool Player::getCanMoveLeft()
{
    return m_CanMoveLeft;
}

bool Player::getCanMoveRight()
{
    return m_CanMoveRight;
}
bool Player::getCanMoveUp()
{
    return m_CanMoveUp;
}
bool Player::getCanMoveDown()
{
    return m_CanMoveDown;
}

void Player::setCanMoveLeft()
{
    m_CanMoveLeft = true;
}
void Player::setCanMoveRight()
{
    m_CanMoveRight = true;
}
void Player::setCanMoveUp()
{
    m_CanMoveUp = true;
}
void Player::setCanMoveDown()
{
    m_CanMoveDown = true;
}

//Bools for stopping player movement states

void Player::stopCanMoveLeft()
{
    m_CanMoveLeft = false;
}
void Player::stopCanMoveRight()
{
    m_CanMoveRight = false;
}
void Player::stopCanMoveUp()
{
    m_CanMoveUp = false;
}
void Player::stopCanMoveDown()
{
    m_CanMoveDown = false;
}

//The following 4 functions determine player collision with platforms.
//A vector of platforms is fed into each function. A bool for the direction is set by default to false.
//Side coordinates are then compared against each other. If there's no overlap, the direction is marked as false and returned to main.

bool Player::determineDown(std::vector<CollisionPlatform> platforms)
{
    bool down = false;
    for (int i = 0; i < platforms.size(); i++)
        {
            if(getBottomSide() >= platforms[i].getTopSide() && getTopSide() <= platforms[i].getTopSide()
            && getRightSide() > platforms[i].getLeftSide() + 1.5 && getLeftSide() < platforms[i].getRightSide() - 1.5)
        {
            down = true;
        }
    }
    return down;
};

bool Player::determineRight(std::vector<CollisionPlatform> platforms)
{
    bool right = false;
    for (int i = 0; i < platforms.size(); i++)
        {
            if(getLeftSide() <= platforms[i].getRightSide() && getRightSide() >= platforms[i].getRightSide()
                && getBottomSide() > platforms[i].getTopSide() + 20 && getTopSide() < platforms[i].getBottomSide() - 20)
        {
            right = true;
        }
    }

    return right;
};

bool Player::determineLeft(std::vector<CollisionPlatform> platforms)
{
    bool left = false;
    for (int i = 0; i < platforms.size(); i++)
        {
            if((getRightSide() >= platforms[i].getLeftSide() && getLeftSide() <= platforms[i].getLeftSide()
            && getBottomSide() > platforms[i].getTopSide() + 20 && getTopSide() < platforms[i].getBottomSide() - 20))
        {
            left = true;
        }
    }
    return left;
};

bool Player::determineUp(std::vector<CollisionPlatform> platforms)
{
    bool down = false;
    for (int i = 0; i < platforms.size(); i++)
        {
            if(getTopSide() < platforms[i].getBottomSide()  && getBottomSide() > platforms[i].getBottomSide()
                && getRightSide() > platforms[i].getLeftSide() + 1.5 && getLeftSide() < platforms[i].getRightSide() - 1.5)
        {
            down = true;
        }
    }
    return down;
};



//Getting sides of player

float Player::getLeftSide()
{
    return m_LeftSide;
}

float Player::getRightSide()
{
    return m_RightSide;
}

float Player::getTopSide()
{
    return m_TopSide;
}

float Player::getBottomSide()
{
    return m_BottomSide;
}

//Getting centre of player for view

Vector2f Player::getCenter()
{
    return m_Center;
}

//Getting sprite.

Sprite Player::getSprite()
{
    return m_Sprite;
}


