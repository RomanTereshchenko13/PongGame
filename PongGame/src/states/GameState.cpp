#include "PCH.h"
#include"GameState.h"
#include"Paddle.h"
#include"Ball.h"

GameState::GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp)
	: State(window, states, mp), m_scorePlayer1{ 0 }, m_scorePlayer2{ 0 }, b_isPaused{ false }, b_done{ false }
{
	InitField();
	InitEntities();
	InitText();
}

void GameState::InitField()
{
	float windowWidth = static_cast<float>(m_window->getSize().x);
	float windowHeight = static_cast<float>(m_window->getSize().y);

	float fieldWidth = windowWidth - 50;
	float fieldHeight = windowHeight - 100;

	m_field.setSize(sf::Vector2f(fieldWidth, fieldHeight));

	m_field.setPosition((windowWidth - fieldWidth) / 2, windowHeight - fieldHeight - 10);

	if (!m_fieldTexture.loadFromFile("assets/field.png")) {
		throw std::runtime_error("Could not load field texture");
	}
	m_field.setTexture(&m_fieldTexture);
}

void GameState::InitEntities()
{
	// Setting starting position
	float yPos = (m_window->getSize().y / 2.f) - 100;
	float xPos = (m_window->getSize().x / 2.f);

	// Randomize the ball's initial velocity
	float initialSpeed = RandomFloat(350.0f, 500.0f);
	float initialAngle = RandomFloat(-45.0f, 45.0f);

	// Calculate the initial velocity components based on the speed and angle
	float initialVelocityX = initialSpeed * std::cos(initialAngle * 3.14159f / 180.0f);
	float initialVelocityY = initialSpeed * std::sin(initialAngle * 3.14159f / 180.0f);

	m_player1 = std::make_unique<Paddle>(50, yPos, 250);
	m_player2 = std::make_unique<Paddle>(1850, yPos, 250);
	m_ball = std::make_unique<Ball>(xPos, yPos, initialVelocityX, initialVelocityY);
}

void GameState::InitText()
{
	//Scores initialization
	m_scoreText = SetupText(m_scoreText, 64, sf::Color(211, 102, 74),
		sf::Vector2f(m_window->getSize().x / 2.f, 0));
	m_scoreText.setString(std::to_string(m_scorePlayer1) + " - " + std::to_string(m_scorePlayer2));
	m_scoreText.setOrigin(m_scoreText.getGlobalBounds().width / 2.f, 0);

	//Pause message initialization
	m_pauseText = SetupText(m_pauseText, 64, sf::Color(211, 102, 74),
		sf::Vector2f(m_window->getSize().x / 2.f, m_window->getSize().y / 2.f));
	m_pauseText.setString("PAUSED");
	m_pauseText.setOrigin(m_pauseText.getGlobalBounds().width / 2.f, m_pauseText.getGlobalBounds().height / 2.f);

	//EndGame message initialization
	m_endText = SetupText(m_endText, 64, sf::Color(211, 102, 74),
		sf::Vector2f(m_window->getSize().x / 2.f, m_window->getSize().y / 2.f));
}

void GameState::HandleAi(const float& deltaTime)
{
	m_player2->SetVelocity(300);

	const sf::Vector2f ballPosition = m_ball->GetPosition();
	const sf::Vector2f ballVelocity = m_ball->GetVelocity();
	const sf::Vector2f paddlePosition = m_player2->GetPosition();

	// Calculate the predicted y position of the ball when it reaches the AI paddle's x-coordinate
	float predictedY = ballPosition.y + (paddlePosition.x - ballPosition.x) * (ballVelocity.y / ballVelocity.x);

	// Update the AI paddle's position based on the predicted y position of the ball
	if (predictedY < paddlePosition.y) {
		m_player2->MoveUp(deltaTime);
	}
	else if (predictedY > paddlePosition.y + m_player2->GetGlobalBounds().height) {
		m_player2->MoveDown(deltaTime);
	}
}

void GameState::UpdateInput(const float& deltaTime)
{
	static bool pauseKeyReleased = true;
	static const sf::Time cooldown = sf::seconds(0.3f); // Cooldown period of 0.5 seconds
	static sf::Clock cooldownTimer;

	// Toggle pause state with cooldown
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && pauseKeyReleased && cooldownTimer.getElapsedTime() > cooldown) {
		b_isPaused = !b_isPaused;
		pauseKeyReleased = false;
		cooldownTimer.restart();
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		pauseKeyReleased = true;
	}

	// Return to menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		EndState();
	}
}

void GameState::UpdatePlayerInput(const float& deltaTime)
{
	// Check movement for player1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Key::W)))
		m_player1->MoveUp(deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Key::S)))
		m_player1->MoveDown(deltaTime);

	// Check movement for player2 if multiplayer enabled
	if (b_multiplayer) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Key::Up)))
			m_player2->MoveUp(deltaTime);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::Key::Down)))
			m_player2->MoveDown(deltaTime);
	}
}

void GameState::UpdatePaddle(const float& deltaTime)
{
	if (!b_multiplayer)
		HandleAi(deltaTime);
	m_player1->CheckBoundaryCollision(m_field.getPosition().y, m_field.getSize().y);
	m_player2->CheckBoundaryCollision(m_field.getPosition().y, m_field.getSize().y);
}

void GameState::UpdateBall(const float& deltaTime)
{
	//Moves ball and checks collision with paddles
	m_ball->Move(deltaTime);
	m_ball->CheckPaddleCollision(*m_player1);
	m_ball->CheckPaddleCollision(*m_player2);
	m_ball->CheckBoundaryCollision(m_field.getPosition().y, m_field.getSize().y);

	const sf::FloatRect ballBounds = m_ball->GetGlobalBounds();
	const sf::FloatRect fieldBounds = m_field.getGlobalBounds();
	const sf::Vector2f ballPosition = m_ball->GetPosition();
	const sf::Vector2f ballVelocity = m_ball->GetVelocity();

	// Collision with left and right field boundaries. Setting scores if ball collide
	if (ballPosition.x < fieldBounds.left) {
		m_scorePlayer2++;
		InitEntities();
	}
	else if (ballPosition.x + ballBounds.width > fieldBounds.left + fieldBounds.width) {
		m_scorePlayer1++;
		InitEntities();
	}
	m_scoreText.setString(std::to_string(m_scorePlayer1) + " - " + std::to_string(m_scorePlayer2));
}

void GameState::Update(const float& deltaTime)
{
	UpdateInput(deltaTime);

	if (!b_isPaused && !b_done) {
		UpdatePlayerInput(deltaTime);
		UpdatePaddle(deltaTime);
		UpdateBall(deltaTime);
	}
	EndLogic();
}

void GameState::EndLogic()
{
	if (m_scorePlayer1 >= 3 || m_scorePlayer2 >= 3) {
		b_done = true;
		m_endText.setString(m_scorePlayer1 == 3 ? "Player 1 has won" : "Player 2 has won");
		m_endText.setOrigin(m_endText.getGlobalBounds().width / 2.f, m_endText.getGlobalBounds().height / 2.f);
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	if (!b_done) {
		m_ball->Render(target);
	}
	else
		target->draw(m_endText);

	if (b_isPaused && !b_done)
		target->draw(m_pauseText);

	m_player1->Render(target);
	m_player2->Render(target);
	target->draw(m_field);
	target->draw(m_scoreText);
}
