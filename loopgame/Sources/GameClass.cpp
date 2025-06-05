#include "../Headers/GameClass.hpp"
#include "../Headers/LocalAnimationManager.hpp"

//Pirnaha
PiranhaAI::PiranhaAI(const sf::Vector2f& position) {
	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
	m_vertices.resize(4);
	setPosition(position);
}

PiranhaAI::PiranhaAI(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect) {
	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
	m_vertices.resize(4);
	setPosition(position);
	m_texture = texture;
	m_vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	m_vertices[1].position = sf::Vector2f(static_cast<float>(rect.size.x), 0.0f);
	m_vertices[2].position = sf::Vector2f(0.0f, static_cast<float>(rect.size.y));
	m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.size.x), static_cast<float>(rect.size.y));

	m_vertices[0].texCoords = sf::Vector2f(static_cast<float>(rect.position.x), static_cast<float>(rect.position.y));
	m_vertices[1].texCoords = sf::Vector2f(static_cast<float>(rect.position.x + rect.size.x), static_cast<float>(rect.position.y));
	m_vertices[2].texCoords = sf::Vector2f(static_cast<float>(rect.position.x), static_cast<float>(rect.position.y + rect.size.y));
	m_vertices[3].texCoords = sf::Vector2f(static_cast<float>(rect.position.x + rect.size.x), static_cast<float>(rect.position.y + rect.size.y));
}
PiranhaAI::PiranhaAI(const sf::Texture& texture, const sf::IntRect& rect) {
	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
	m_vertices.resize(4);
	m_texture = texture;
	m_vertices[0].position = sf::Vector2f(0.0f, 0.0f);
	m_vertices[1].position = sf::Vector2f(static_cast<float>(rect.size.x), 0.0f);
	m_vertices[2].position = sf::Vector2f(0.0f, static_cast<float>(rect.size.y));
	m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.size.x), static_cast<float>(rect.size.y));

	m_vertices[0].texCoords = sf::Vector2f(static_cast<float>(rect.position.x), static_cast<float>(rect.position.y));
	m_vertices[1].texCoords = sf::Vector2f(static_cast<float>(rect.position.x + rect.size.x), static_cast<float>(rect.position.y));
	m_vertices[2].texCoords = sf::Vector2f(static_cast<float>(rect.position.x), static_cast<float>(rect.position.y + rect.size.y));
	m_vertices[3].texCoords = sf::Vector2f(static_cast<float>(rect.position.x + rect.size.x), static_cast<float>(rect.position.y + rect.size.y));
}
PiranhaAI::PiranhaAI(const sf::Texture& texture) {
	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
	m_vertices.resize(4);
	m_texture = texture;
	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(static_cast<float>(m_texture.getSize().x), 0);
	m_vertices[2].position = sf::Vector2f(0, static_cast<float>(m_texture.getSize().y));
	m_vertices[3].position = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
	m_vertices[2].texCoords = sf::Vector2f(0, m_texture.getSize().y);
	m_vertices[3].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
}
PiranhaAI::PiranhaAI(const sf::Texture& texture, const sf::Vector2f& position) {
	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
	m_vertices.resize(4);
	setPosition(position);
	m_texture = texture;
	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(static_cast<float>(m_texture.getSize().x), 0);
	m_vertices[2].position = sf::Vector2f(0, static_cast<float>(m_texture.getSize().y));
	m_vertices[3].position = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
	m_vertices[2].texCoords = sf::Vector2f(0, m_texture.getSize().y);
	m_vertices[3].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
}
void PiranhaAI::setTextureRect(const sf::IntRect& rect, const bool resetSize) {
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
void PiranhaAI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}
void PiranhaAI::setHitbox(const sf::FloatRect& hitbox) {
	m_hitbox = hitbox;
}
sf::FloatRect PiranhaAI::getHitbox() const {
	return m_hitbox;
}
void PiranhaAI::setDisabled(const bool disabled) {
	m_Disabled = disabled;
}
bool PiranhaAI::isDisabled() const {
	return m_Disabled;
}
void PiranhaAI::setSpeed(const float speed) {
	m_speed = speed;
}
float PiranhaAI::getSpeed() const {
	return m_speed;
}
void PiranhaAI::setPositionLimit(const float position_limit) {
	m_position_limit = position_limit;
}
float PiranhaAI::getPositionLimit() const {
	return m_position_limit;
}
void PiranhaAI::setPositionTemporary(const float position_temporary) {
	m_position_temporary = position_temporary;
}
float PiranhaAI::getPositionTemporary() const {
	return m_position_temporary;
}
void PiranhaAI::setState(const bool state) {
	m_state = state;
}
bool PiranhaAI::getState() const {
	return m_state;
}
void PiranhaAI::setStopTime(const float stop_time) {
	m_stop_time = stop_time;
}
float PiranhaAI::getStopTime() const {
	return m_stop_time;
}
void PiranhaAI::restartStopClock() {
	m_stop_clock.restart();
}
sf::Clock PiranhaAI::getStopClock() const {
	return m_stop_clock;
}
void PiranhaAI::setStop(const bool stop) {
	m_stop = stop;
}
bool PiranhaAI::getStop() const {
	return m_stop;
}
void PiranhaAI::setDistanceAppear(const float distance_appear) {
	m_distance_appear = distance_appear;
}
float PiranhaAI::getDistanceAppear() const {
	return m_distance_appear;
}
void PiranhaAI::setTexture(const sf::Texture& texture, const bool resetRect) {
	m_texture = texture;
	if (resetRect) {
		m_vertices[0].position = sf::Vector2f(0, 0);
		m_vertices[1].position = sf::Vector2f(static_cast<float>(m_texture.getSize().x), 0);
		m_vertices[2].position = sf::Vector2f(0, static_cast<float>(m_texture.getSize().y));
		m_vertices[3].position = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);

		m_vertices[0].texCoords = sf::Vector2f(0, 0);
		m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
		m_vertices[2].texCoords = sf::Vector2f(0, m_texture.getSize().y);
		m_vertices[3].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
	}
}

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

bool GoombaEnemy::isDisable() {
	return m_GoombaisDisable;
}

void GoombaEnemy::setDisable(bool result) {
	m_GoombaisDisable = result;
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

bool SpinyEnemy::isDisable() {
	return m_SpinyisDisable;
}

void SpinyEnemy::setDisable(bool result) {
	m_SpinyisDisable = result;
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
	for (int i = 0; i < piranha_data.size(); ++i) {
		piranha_data[i].setPosition(sf::Vector2f({ this->piranha_origin_pos[i].x + this->pos * 1280.0f , this->piranha_origin_pos[i].y }));
	}
}