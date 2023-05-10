#pragma once

#include"Entity.h"

class Paddle : public Entity {
public:
    //Constructor
    Paddle(float x, float y, float velocity);

    //Functions
    void MoveUp(const float& deltaTime);
    void MoveDown(const float& deltaTime);
    void SetVelocity(float velocity);
    void CheckBoundaryCollision(float fieldTop, float fieldHeight);

    //Getters
    const float GetVelocity() const;

private:
    float m_velocity;
    sf::Vector2f m_position;
};

