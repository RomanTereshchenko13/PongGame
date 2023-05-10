#include "PCH.h"
#include "Button.h"
#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, bool mp)
	: State(window, states, mp)
{
	InitButtons();
	InitBackground();
}

void MenuState::InitBackground()
{
	if(!m_backgroundTexture.loadFromFile("assets/main.png")) {
		throw std::runtime_error("Could not load background texture");
	}
	m_background.setTexture(&m_backgroundTexture);
	m_background.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
}

void MenuState::InitButtons()
{
	double scaleFactor = 0.6;
	float xPos = 600;
	float yPos = 300;

    std::vector<std::string> buttonNames = { "Single", "Multiplayer", "Exit" };

	for (const auto& buttonName : buttonNames) {
		m_buttons[buttonName] = std::make_unique<Button>(xPos, yPos,
			buttonName, sf::Color::White, scaleFactor, scaleFactor);
		yPos += 120;
	}
}

void MenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& i : m_buttons)
		i.second->Render(target);
}

void MenuState::UpdateButtons()
{
	for (auto& a : m_buttons) {
		a.second->Update(m_mousePosView);
	}

	if (m_buttons["Single"]->IsPressed()) {
		b_multiplayer = false;
		m_states->push(std::make_unique<GameState>(m_window, m_states, b_multiplayer));
	}
	else if (m_buttons["Multiplayer"]->IsPressed()) {
		b_multiplayer = true;
		m_states->push(std::make_unique<GameState>(m_window, m_states, b_multiplayer));
	}
	else if (m_buttons["Exit"]->IsPressed()) {
		EndState();
	}
}

void MenuState::Update(const float& deltaTime)
{
	UpdateMousePos();
	UpdateButtons();
}

void MenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;
	target->draw(m_background);
	RenderButtons(target);
	target->draw(m_text);
}
