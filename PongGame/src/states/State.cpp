#include "PCH.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp)
	: b_quit(false), b_multiplayer(mp), m_states(states), m_window(window)
{
	if (!m_font.loadFromFile("assets/Roboto-Bold.ttf")) {
		throw std::runtime_error("Could not load font");
	}
}

sf::Text State::SetupText(sf::Text& text, int fontSize, sf::Color color, sf::Vector2f position)
{
	text.setFont(m_font);
	text.setCharacterSize(fontSize);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(color);
	text.setPosition(position);

	return text;
}

float State::RandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomGenerator);
}

void State::UpdateMousePos()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);
	m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
}

void State::EndState()
{
	b_quit = true;
}


bool State::GetQuit() const
{
	return b_quit;
}
