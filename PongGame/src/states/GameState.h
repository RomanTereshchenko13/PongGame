#pragma once
#include"State.h"

class Ball;
class Paddle;

class GameState : public State 
{
public:
	//Constructors
	GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp);

	//Init Functions
	void InitField();
	void InitEntities();
	void InitText();

	//Update and rendering functions
	void UpdateInput(const float& deltaTime);
	void UpdatePlayerInput(const float& deltaTime);
	void UpdatePaddle(const float& deltaTime);
	void UpdateBall(const float& deltaTime);
	void Update(const float& deltaTime) override;
	void EndLogic();
	void Render(sf::RenderTarget* target = nullptr) override;

private:
	void HandleAi(const float& deltaTime);

private:
	sf::Texture m_fieldTexture;
	sf::RectangleShape m_field;

	std::unique_ptr<Paddle> m_player1;
	std::unique_ptr<Paddle> m_player2;
	std::unique_ptr<Ball> m_ball;

	int m_scorePlayer1;
	int m_scorePlayer2;

	sf::Text m_scoreText;
	sf::Text m_endText;
	sf::Text m_pauseText;
	bool b_isPaused;
	bool b_done;
};

