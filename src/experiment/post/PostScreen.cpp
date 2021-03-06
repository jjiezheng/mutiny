#include "PostScreen.h"
#include "MainCamera.h"

using namespace mutiny::engine;

GameObject* PostScreen::create()
{
  GameObject* mainGo = new GameObject("PostScreen");
  mainGo->addComponent<PostScreen>();

  return mainGo;
}

void PostScreen::onAwake()
{
  MainCamera::create();
  GameObject* playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(0, 0, 0));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/textured"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));

  Mesh* mesh = Resources::load<Mesh>("models/curuthers/curuthers");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
  
  
}

void PostScreen::onGui()
{

}

