#include "Handler.h"

#include <random>
#include <time.h>

Handler::Handler()
{
	m_spawnTime = 1.0f;
}

void Handler::onTick()
{
	if (m_spawnTime <= 0.0f)
	{
		std::shared_ptr<Entity> e = getCore()->addEntity();
		e->addComponent<Enemy>();
		std::shared_ptr<Transform> t = e->addComponent<Transform>();

		srand(time(NULL));

		float randX = rand() % 14 - 7.0f;
		float randY = rand() % 2 + 1;

		t->setPosition(glm::vec3(randX, randY, 20.0f));
		t->setRotaion(glm::vec3(0.0f, 180.0f, 0.0f));

		std::shared_ptr<ModelRenderer> mr = e->addComponent<ModelRenderer>();
		mr->setModel(getCore()->getResources()->load<Model>("models/bee/bee.obj"));
		mr->setTexture(getCore()->getResources()->load<Texture>("models/bee/bee.png"));

		m_spawnTime = 1.0f;
	}
	else
	{
		m_spawnTime -= getEnviroment()->GetDeltaTime();
	}
}