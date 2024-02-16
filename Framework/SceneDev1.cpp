#include "pch.h"
#include "SceneDev1.h"

SCENE_DEV1::SCENE_DEV1(SceneIds id) : Scene(id)
{
}

SCENE_DEV1::~SCENE_DEV1()
{
}

void SCENE_DEV1::Init()
{
	
}

void SCENE_DEV1::Release()
{
}

void SCENE_DEV1::Enter()
{
}

void SCENE_DEV1::Exit()
{
}

void SCENE_DEV1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SCENE_DEV2);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		GameObject* findGo = FindGo("Message");
		findGo->SetActive(!findGo->GetActive());
	}

}
