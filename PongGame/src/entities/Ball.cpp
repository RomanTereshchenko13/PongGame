#include "PCH.h"
#include"Paddle.h"
#include "Ball.h"

Ball::Ball(float startX, float startY, float velX, float velY) : Entity("assets/ball.png") ,
m_velocity(velX, velY), m_position(startX, startY) {}

void Ball::Move(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	SetPosition(m_position);
}

void Ball::SetVelocity(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

void Ball::CheckPaddleCollision(const Paddle& paddle)
{
	const sf::FloatRect ballBounds = GetGlobalBounds();
	const sf::FloatRect paddleBounds = paddle.GetGlobalBounds();
	const sf::Vector2f ballPosition = GetPosition();
	const sf::Vector2f ballVelocity = GetVelocity();

	if (ballBounds.intersects(paddleBounds))
	{
		// Check if the ball hits the top or bottom of the paddle
		if (ballPosition.y + ballBounds.height >= paddleBounds.top && 
			ballPosition.y <= paddleBounds.top + paddleBounds.height) {
			// Reverse the horizontal velocity of the ball
			SetVelocity(-ballVelocity.x, ballVelocity.y);
			// Calculate the offset between the centers of the ball and paddle
			float offset = (m_position.y + ballBounds.height / 2) - (paddleBounds.top + paddleBounds.height / 2);
			// Modify the y-velocity of the ball based on the offset
			m_velocity.y = offset * 5.f;
		}
		else {
			// Reverse the vertical velocity of the ball
			SetVelocity(ballVelocity.x, -ballVelocity.y);
		}
	}
}

void Ball::CheckBoundaryCollision(float fieldTop, float fieldHeight)
{
	const float fieldBottom = fieldTop + fieldHeight - GetGlobalBounds().height;

	// Collision with top and pottom field boundaries
	if (GetPosition().y < fieldTop) {
		SetVelocity(m_velocity.x, -m_velocity.y);
		SetPosition(GetPosition().x, fieldTop);
	}
	else if (GetPosition().y + GetGlobalBounds().height > fieldTop + fieldHeight) {
		SetVelocity(m_velocity.x, -m_velocity.y);
		SetPosition(GetPosition().x, fieldBottom);
	}
}

sf::Vector2f Ball::GetVelocity() const
{
	return m_velocity;
}

float Ball::GetRadius() const
{
	return GetGlobalBounds().width / 2;
}