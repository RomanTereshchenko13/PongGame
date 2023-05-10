#include "PCH.h"
#include "Entity.h"

Entity::Entity(const std::string& fileName)
{
	if (!m_texture.loadFromFile(fileName)) {
		throw std::runtime_error("Could not load " + fileName + " texture");
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

void Entity::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void Entity::SetPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

void Entity::SetScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

void Entity::Move(float x, float y)
{
	m_sprite.move(x, y);
}


const sf::Vector2f& Entity::GetPosition() const
{
	return m_sprite.getPosition();
}

const sf::FloatRect& Entity::GetGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void Entity::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
}
