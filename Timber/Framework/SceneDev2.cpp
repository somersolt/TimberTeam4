#include "pch.h"
#include "SceneDev2.h"

SCENE_DEV2::SCENE_DEV2(SceneIds id) : Scene(id)
{
}

SCENE_DEV2::~SCENE_DEV2()
{
}

void SCENE_DEV2::Init()
{
}

void SCENE_DEV2::Release()
{
}

void SCENE_DEV2::Enter()
{
}

void SCENE_DEV2::Exit()
{
}

void SCENE_DEV2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SCENE_DEV1);
	}
}
