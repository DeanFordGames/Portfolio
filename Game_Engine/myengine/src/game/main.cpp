#include <myengine/myengine.h>

#include "Player.h"
#include "Handler.h"

using namespace myengine;

void initializePlayer(std::shared_ptr<Core> _core)
{
	std::shared_ptr<Entity> player = _core->addEntity();
	std::shared_ptr<Transform> playerT = player->addComponent<Transform>();
	playerT->setPosition(glm::vec3(0.0f, -0.2f, 0.0f));
	playerT->setScale(glm::vec3(0.2f, 0.2f, 0.2f));

	std::shared_ptr<ModelRenderer> playerMR = player->addComponent<ModelRenderer>();
	playerMR->setModel(_core->getResources()->load<Model>("models/curuthers/curuthers.obj"));
	playerMR->setTexture(_core->getResources()->load<Texture>("models/curuthers/Whiskers_diffuse.png"));

	std::shared_ptr<BoxCollider> playerBC = player->addComponent<BoxCollider>();
	playerBC->setSize(glm::vec3(0.2f, 0.2f, 0.2f));
	playerBC->initialize();
	std::shared_ptr<RigidBody> playerRB = player->addComponent<RigidBody>();
	playerRB->initialize();

	player->addComponent<SoundSource>();

	player->addComponent<Player>();
}
void initializeFloor(std::shared_ptr<Core> _core)
{
	std::shared_ptr<Entity> floor = _core->addEntity();
	std::shared_ptr<Transform> floorT = floor->addComponent<Transform>();
	floorT->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	floorT->setScale(glm::vec3(2.0f, 0.5f, 1.0f));

	std::shared_ptr<ModelRenderer> floorMR = floor->addComponent<ModelRenderer>();
	floorMR->setModel(_core->getResources()->load<Model>("models/floor/floor.obj"));
	floorMR->setTexture(_core->getResources()->load<Texture>("models/floor/tex.png"));

	std::shared_ptr<BoxCollider> floorBC = floor->addComponent<BoxCollider>();
	floorBC->setSize(glm::vec3(20.0f, 1.0f, 20.0f));
	floorBC->initialize();

	std::shared_ptr<RigidBody> floorRB = floor->addComponent<RigidBody>();
	floorRB->setMass(0.0f);
	floorRB->initialize();
}
void initializeWalls(std::shared_ptr<Core> _core)
{
	std::shared_ptr<Entity> wall1 = _core->addEntity();
	std::shared_ptr<Transform> wall1T = wall1->addComponent<Transform>();
	wall1T->setPosition(glm::vec3(10.0f, 3.0f, 0.0f));
	wall1T->setScale(glm::vec3(0.5f, 3.0f, 1.0f));
	wall1T->setRotaion(glm::vec3(0.0f, 0.0f, 90.0f));

	std::shared_ptr<ModelRenderer> wall1MR = wall1->addComponent<ModelRenderer>();
	wall1MR->setModel(_core->getResources()->load<Model>("models/floor/floor.obj"));
	wall1MR->setTexture(_core->getResources()->load<Texture>("models/floor/tex.png"));

	std::shared_ptr<BoxCollider> wall1BC = wall1->addComponent<BoxCollider>();
	wall1BC->setSize(glm::vec3(0.6f, 20.0f, 20.0f));
	wall1BC->initialize();

	std::shared_ptr<RigidBody> wall1RB = wall1->addComponent<RigidBody>();
	wall1RB->setMass(0.0f);
	wall1RB->initialize();

	//////////////////////////////////////////////////////////////////

	std::shared_ptr<Entity> wall2 = _core->addEntity();
	std::shared_ptr<Transform> wall2T = wall2->addComponent<Transform>();
	wall2T->setPosition(glm::vec3(-10.0f, 3.0f, 0.0f));
	wall2T->setScale(glm::vec3(0.5f, 3.0f, 1.0f));
	wall2T->setRotaion(glm::vec3(0.0f, 0.0f, 90.0f));

	std::shared_ptr<ModelRenderer> wall2MR = wall2->addComponent<ModelRenderer>();
	wall2MR->setModel(_core->getResources()->load<Model>("models/floor/floor.obj"));
	wall2MR->setTexture(_core->getResources()->load<Texture>("models/floor/tex.png"));

	std::shared_ptr<BoxCollider> wall2BC = wall2->addComponent<BoxCollider>();
	wall2BC->setSize(glm::vec3(1.0f, 20.0f, 20.0f));
	wall2BC->initialize();

	std::shared_ptr<RigidBody> wall2RB = wall2->addComponent<RigidBody>();
	wall2RB->setMass(0.0f);
	wall2RB->initialize();
}

int main(int argc, char* argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	//player
	initializePlayer(core);

	std::shared_ptr<Entity> handler = core->addEntity();
	handler->addComponent<Handler>();

	//floor
	initializeFloor(core);

	//walls
	initializeWalls(core);

	core->start();

	return 0;
}