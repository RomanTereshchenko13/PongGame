#include "PCH.h"
#include "Paddle.h"

Paddle::Paddle(float x, float y, float velocity) :Entity("assets/paddle.png"), m_velocity(velocity)
{
	SetPosition(x, y);
	m_position = GetPosition();
}

void Paddle::MoveUp(const float& deltaTime)
{
    m_position.y += -m_velocity * deltaTime;
	SetPosition(m_position);
}

void Paddle::MoveDown(const float& deltaTime)
{
    m_position.y += m_velocity * deltaTime;
	SetPosition(m_position);
}

void Paddle::SetVelocity(float velocity)
{
    m_velocity = velocity;
}

void Paddle::CheckBoundaryCollision(float fieldTop, float fieldHeight)
{
    const float topBoundary = fieldTop + 15;
    const float bottomBoundary = fieldTop + fieldHeight - GetGlobalBounds().height - 15;

    // Checks collision with top boundary
    if (GetPosition().y < topBoundary)
    {
        SetPosition(GetPosition().x, topBoundary);
    }
    // Checks collision with bottom boundary
    else if (GetPosition().y + GetGlobalBounds().height > fieldTop + fieldHeight - 15)
    {
        SetPosition(GetPosition().x, bottomBoundary);
    }
    m_position = GetPosition();
}

const float Paddle::GetVelocity() const
{
    return m_velocity;
}