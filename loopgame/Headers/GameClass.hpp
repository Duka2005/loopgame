#pragma once
#ifndef GAMECLASS_HPP
#define GAMECLASS_HPP

#include <SFML/Graphics.hpp>
#include "LocalAnimationManager.hpp"

class PiranhaAI : public sf::Drawable, public sf::Transformable {
public:
	LocalAnimationManager m_animation;
	PiranhaAI(const sf::Texture& texture);
	PiranhaAI(const sf::Texture& texture, const sf::IntRect& rect);
	PiranhaAI(const sf::Texture& texture, const sf::Vector2f& position);
	PiranhaAI(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect);
	PiranhaAI(const sf::Vector2f& position);
	void setTextureRect(const sf::IntRect& rect, bool resetSize = false);
	void setHitbox(const sf::FloatRect& hitbox);
	sf::FloatRect getHitbox() const;
	void setDisabled(bool disabled);
	bool isDisabled() const;
	void setSpeed(float speed);
	float getSpeed() const;
	void setPositionLimit(float position_limit);
	float getPositionLimit() const;
	void setPositionTemporary(float position_temporary);
	float getPositionTemporary() const;
	void setState(bool state);
	bool getState() const;
	void setStopTime(float stop_time);
	float getStopTime() const;
	void restartStopClock();
	sf::Clock getStopClock() const;
	void setStop(bool stop);
	bool getStop() const;
	void setDistanceAppear(float distance_appear);
	float getDistanceAppear() const;
	void setTexture(const sf::Texture& texture, bool resetRect = false);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray       m_vertices;
	sf::Texture           m_texture;
	sf::Vector2f          m_curr{};
	sf::Vector2f          m_prev{};
	sf::FloatRect         m_hitbox;
	bool                  m_Disabled{};
	float                 m_speed{};
	float                 m_position_limit{};
	float                 m_position_temporary{};
	bool                  m_state{};
	float                 m_stop_time{};
	sf::Clock             m_stop_clock;
	bool                  m_stop{};
	float                 m_distance_appear{};
};

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
	bool isDisable();
	void setDisable(bool result);
	void SetGoombaTexture(sf::Texture GoombaTexture);
private:
	float m_GoombaXvelocity = 0.0f;
	float m_GoombaYvelocity = 0.0f;
	float m_GoombaSpeed = 1.0f;
	bool m_FirstGoombaDirection = true;
	bool m_GoombaDirection = true;
	bool m_GoombaisDisable = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::VertexArray m_vertices;
	sf::Texture     m_texture;
};

class SpinyEnemy : public sf::Drawable, public sf::Transformable {
public:
	SpinyEnemy(sf::Texture texture) {
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
	void setSpinyXvelocity(float x);
	void setSpinyYvelocity(float y);
	void setSpinyDirection(bool x);
	void setSpinySpeed(float speed);
	float getSpinyXvelocity();
	float getSpinyYvelocity();
	bool getSpinyDirection();
	float getSpinySpeed();
	bool isDisable();
	void setDisable(bool result);
	void SetSpinyTexture(sf::Texture GoombaTexture);
	LocalAnimationManager m_animation;
private:
	float m_SpinyXvelocity = 0.0f;
	float m_SpinyYvelocity = 0.0f;
	float m_SpinySpeed = 1.0f;
	bool m_FirstSpinyDirection = true;
	bool m_SpinyDirection = true;
	bool m_SpinyisDisable = true;

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
	std::vector<PiranhaAI> piranha_data{};
	std::vector<sf::Vector2f> piranha_origin_pos{};
	std::vector<GoombaEnemy> goomba_data{};
	std::vector<sf::Vector2f> goomba_origin_pos{};
	std::vector<SpinyEnemy> spiny_data{};
	std::vector<sf::Vector2f> spiny_origin_pos{};
	int pos = 0;

	void UpdateTilePosition();
	void UpdateEnemyPosition();
};

#endif