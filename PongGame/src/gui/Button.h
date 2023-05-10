#pragma once

class Button
{
public:
	//Constructor
	Button(float posX, float posY, std::string_view name, sf::Color color, float sizeX, float sizeY);

	//Functions
	void LoadAssets();
	const bool IsPressed() const;
	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget* target);

	//Getters
	const sf::FloatRect GetGlobalBounds() const;

private:
	enum ButtonState { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

	sf::Sprite button;
	sf::Texture idleTexture;
	sf::Texture hoverTexture;

	unsigned short buttonState;
	sf::Font font;
	sf::Text text;
};

