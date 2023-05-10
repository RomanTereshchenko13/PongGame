#pragma once

class Entity
{
public:
	//Constructors
	Entity(const std::string& fileName);

	//Functions
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f pos);
	void SetScale(float x, float y);
	void Move(float x, float y);
	void Render(sf::RenderTarget* target);

	//Getters
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect& GetGlobalBounds() const;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

