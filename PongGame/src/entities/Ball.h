#pragma once

#include"Entity.h"

class Paddle;

class Ball : public Entity
{
public:
    //Counstructor
    Ball(float startX, float startY, float velX, float velY);

    //Functions
    void Move(float deltaTime);
    void SetVelocity(float x, float y);
    void CheckPaddleCollision(const Paddle& paddle);
    void CheckBoundaryCollision(float fieldTop, float fieldHeight);

    //Getters
    sf::Vector2f GetVelocity() const;
    float GetRadius() const;

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_position;
};

