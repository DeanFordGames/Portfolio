#include "Player.h"

Player::Player()
{
	m_freezeAxis = false;
}

void Player::onTick()
{
	float x = 0;
	float y = 0;

	getCamera()->setCameraAngle(0, 0.0f);
	std::shared_ptr<Transform> t = getEntity()->getComponent<Transform>();


	if (getKeyboard()->getKey(KeyCodes::a))
	{
		t->changePosition(glm::vec3(0.1f, 0.0f, 0.0f));
	}
	else if (getKeyboard()->getKey(KeyCodes::d))
	{
		t->changePosition(glm::vec3(-0.1f, 0.0f, 0.0f));
	}
	if (getKeyboard()->getKeyDown(KeyCodes::space))
	{
		t->changePosition(glm::vec3(0.0f, 10.0f, 0.0f));
		getEntity()->getComponent<SoundSource>()->setAudio(getCore()->getResources()->load<Audio>("audio/jump.ogg"));
	}

	getCamera()->setPosition(t->getPosition() + glm::vec3(0.0f, 2.0f, -5.0f));

	if (getKeyboard()->getKey(KeyCodes::escape))
	{
		getCore()->stop();
	}

	if (!m_freezeAxis)
	{
		std::shared_ptr<RigidBody> rb = getEntity()->getComponent<RigidBody>();
		rb->freezePositionAxis(glm::vec3(1.0f, 1.0f, 0.0f));

		m_freezeAxis = true;
	}
}