#pragma once

#include"State.h"

class Button;

class MenuState : public State
{
public:
	//Constructors
	MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp);

	//Init Functions
	void InitBackground();
	void InitButtons();

	//Funtions
	void RenderButtons(sf::RenderTarget* target = nullptr);
	void UpdateButtons();
	void Update(const float& deltaTime) override;
	void Render(sf::RenderTarget* = nullptr) override;

private:

	sf::RectangleShape m_background;
	sf::Text m_text;
	sf::Font m_font;
	sf::Texture m_backgroundTexture;
	std::map<std::string, std::unique_ptr<Button>> m_buttons;
};

