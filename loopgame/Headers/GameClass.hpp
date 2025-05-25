#pragma once
#ifndef GAMECLASS_HPP
#define GAMECLASS_HPP

#include <SFML/Graphics.hpp>

class GoombaEnemy : public sf::Drawable, public sf::Transformable {
public:
	GoombaEnemy(sf::Texture texture) {
		this->m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
		this->m_vertices.resize(4);
		this->m_texture = texture;
		this->m_vertices[0].position = sf::Vector2f({ 0,0 });
		this->m_vertices[1].position = sf::Vector2f({ static_cast<float>(texture.getSize().x) ,0 });
		this->m_vertices[2].position = sf::Vector2f({ 0 , static_cast<float>(texture.getSize().y) });
		this->m_vertices[3].position = sf::Vector2f({ static_cast<float>(texture.getSize().x) , static_cast<float>(texture.getSize().y) });

		this->m_vertices[0].texCoords = sf::Vector2f({ 0,0 });
		this->m_vertices[1].texCoords = sf::Vector2f({ static_cast<float>(texture.getSize().x) ,0 });
		this->m_vertices[2].texCoords = sf::Vector2f({ 0 , static_cast<float>(texture.getSize().y) });
		this->m_vertices[3].texCoords = sf::Vector2f({ static_cast<float>(texture.getSize().x) , static_cast<float>(texture.getSize().y) });
	}
	void setTextureRect(const sf::IntRect& rect, const bool resetSize);
	void setGoombaXvelocity(float x);
	void setGoombaYvelocity(float y);
	void setGoombaDirection(bool x);
	void setGoombaSpeed(float speed);
	float getGoombaXvelocity();
	float getGoombaYvelocity();
	bool getGoombaDirection();
	float getGoombaSpeed();
	void SetGoombaTexture(sf::Texture GoombaTexture);
private:
	float m_GoombaXvelocity = 0.0f;
	float m_GoombaYvelocity = 0.0f;
	float m_GoombaSpeed = 1.0f;
	bool m_FirstGoombaDirection = true;
	bool m_GoombaDirection = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_vertices;
	sf::Texture     m_texture;
};

class Level {
public:
	std::vector<sf::Sprite> data{};
	std::vector<sf::Vector2f> origin_pos{};
	std::vector<sf::Sprite> piranha_ground_data{};
	std::vector<sf::Vector2f> piranha_ground_origin_pos{};
	std::vector<GoombaEnemy> goomba_data{};
	std::vector<sf::Vector2f> goomba_origin_pos{};
	int pos = 0;

	void UpdateTilePosition();
	void UpdateEnemyPosition();
};

#endif