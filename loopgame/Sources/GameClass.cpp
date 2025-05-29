#include "../Headers/GameClass.hpp"
#include "../Headers/LocalAnimationManager.hpp"

//Goomba
void GoombaEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &m_texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(m_vertices, states);
}
void GoombaEnemy::setGoombaXvelocity(float x) {
	m_GoombaXvelocity = x;
}

void GoombaEnemy::setGoombaYvelocity(float y) {
	m_GoombaYvelocity = y;
}

void GoombaEnemy::setGoombaDirection(bool x) {
	m_GoombaDirection = x;
}

void GoombaEnemy::setGoombaSpeed(float speed) {
	m_GoombaSpeed = speed;
}

float GoombaEnemy::getGoombaXvelocity() {
	return m_GoombaXvelocity;
}

float GoombaEnemy::getGoombaYvelocity() {
	return m_GoombaYvelocity;
}

bool GoombaEnemy::getGoombaDirection() {
	return m_GoombaDirection;
}

float GoombaEnemy::getGoombaSpeed() {
	return m_GoombaSpeed;
}

void GoombaEnemy::SetGoombaTexture(sf::Texture texture) {
	this->m_texture = texture;
}
void GoombaEnemy::setTextureRect(const sf::IntRect& rect, const bool resetSize) {
	m_vertices[0].texCoords = sf::Vector2f(rect.position.x, rect.position.y);
	m_vertices[1].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
	m_vertices[2].texCoords = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);
	m_vertices[3].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);

	if (resetSize) {
		m_vertices[0].position = sf::Vector2f(0, 0);
		m_vertices[1].position = sf::Vector2f(rect.size.x, 0);
		m_vertices[2].position = sf::Vector2f(0, rect.size.y);
		m_vertices[3].position = sf::Vector2f(rect.size.x, rect.size.y);
	}
}

//Spiny
void SpinyEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &m_texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(m_vertices, states);
}
void SpinyEnemy::setSpinyXvelocity(float x) {
	m_SpinyXvelocity = x;
}

void SpinyEnemy::setSpinyYvelocity(float y) {
	m_SpinyYvelocity = y;
}

void SpinyEnemy::setSpinyDirection(bool x) {
	m_SpinyDirection = x;
}

void SpinyEnemy::setSpinySpeed(float speed) {
	m_SpinySpeed = speed;
}

float SpinyEnemy::getSpinyXvelocity() {
	return m_SpinyXvelocity;
}

float SpinyEnemy::getSpinyYvelocity() {
	return m_SpinyYvelocity;
}

bool SpinyEnemy::getSpinyDirection() {
	return m_SpinyDirection;
}

float SpinyEnemy::getSpinySpeed() {
	return m_SpinySpeed;
}

void SpinyEnemy::SetSpinyTexture(sf::Texture texture) {
	this->m_texture = texture;
}
void SpinyEnemy::setTextureRect(const sf::IntRect& rect, const bool resetSize) {
	m_vertices[0].texCoords = sf::Vector2f(rect.position.x, rect.position.y);
	m_vertices[1].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
	m_vertices[2].texCoords = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);
	m_vertices[3].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);

	if (resetSize) {
		m_vertices[0].position = sf::Vector2f(0, 0);
		m_vertices[1].position = sf::Vector2f(rect.size.x, 0);
		m_vertices[2].position = sf::Vector2f(0, rect.size.y);
		m_vertices[3].position = sf::Vector2f(rect.size.x, rect.size.y);
	}
}

void Level::UpdateTilePosition() {
	for (int i = 0; i < data.size(); ++i)
		data[i].setPosition(sf::Vector2f({ this->origin_pos[i].x + this->pos * 1280.0f , this->origin_pos[i].y }));
}

void Level::UpdateEnemyPosition() {
	for (int i = 0; i < piranha_ground_data.size(); ++i) {
		piranha_ground_data[i].setPosition(sf::Vector2f({ this->piranha_ground_origin_pos[i].x + this->pos * 1280.0f , this->piranha_ground_origin_pos[i].y }));
	}
	for (int i = 0; i < goomba_data.size(); ++i) {
		goomba_data[i].setPosition(sf::Vector2f({ this->goomba_origin_pos[i].x + this->pos * 1280.0f , this->goomba_origin_pos[i].y }));
	}
	for (int i = 0; i < spiny_data.size(); ++i) {
		spiny_data[i].setPosition(sf::Vector2f({ this->spiny_origin_pos[i].x + this->pos * 1280.0f , this->spiny_origin_pos[i].y }));
	}
}