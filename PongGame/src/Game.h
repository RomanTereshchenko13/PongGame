#pragma once

class State;

class Game
{
public:
	//Constructors
	Game();
	~Game();

	//Functions
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();
	void Render();
	void Run();

private:
	sf::RenderWindow* window;
	std::stack<std::unique_ptr<State>> states;

	sf::Clock dtClock;
	float deltaTime;
};

