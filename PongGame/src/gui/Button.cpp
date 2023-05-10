#include "PCH.h"
#include "Button.h"

Button::Button(float posX, float posY, std::string_view name, sf::Color color, float sizeX, float sizeY)
	: buttonState{BTN_IDLE}
{
	LoadAssets();

	//Set button
	button.setTexture(idleTexture);
	button.setPosition(posX, posY);
	button.setScale(sizeX, sizeY);

	// Set button`s text
	text.setFont(font);
	text.setString(static_cast<std::string>(name));
	text.setFillColor(color);
	text.setCharacterSize(50);

	// Calculate the center position of the text
	sf::FloatRect textRect = text.getLocalBounds();
	float centerX = button.getPosition().x + (button.getGlobalBounds().width / 2.f);
	float centerY = button.getPosition().y + (button.getGlobalBounds().height / 2.f);
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(centerX, centerY);
}

void Button::LoadAssets()
{
	if (!hoverTexture.loadFromFile("assets/button_hover.png")) {
		throw std::runtime_error("Could not load hover button texture");
	}
	if (!idleTexture.loadFromFile("assets/button.png")) {
		throw std::runtime_error("Could not load button texture");
	}
	if (!font.loadFromFile("assets/Roboto-Bold.ttf")) {
		throw std::runtime_error("Could not load font");
	}
}

const bool Button::IsPressed() const
{
	if (buttonState == BTN_ACTIVE)
		return true;
	return false;
}


void Button::Update(const sf::Vector2f mousePos)
{
	//button idle by default
	buttonState = BTN_IDLE;
	button.setTexture(idleTexture);

	// if left mouse key pressed inside Button bounds Button sets to active
	if (button.getGlobalBounds().contains(mousePos))
	{
		buttonState == BTN_HOVER;
		button.setTexture(hoverTexture);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = BTN_ACTIVE;
		}
	}
}

void Button::Render(sf::RenderTarget* target)
{
	target->draw(button);
	target->draw(text);
}

const sf::FloatRect Button::GetGlobalBounds() const
{
	return button.getGlobalBounds();
}



