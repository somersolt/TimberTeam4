#include "pch.h"
#include "SceneTitle.h"

SCENE_TITLE::SCENE_TITLE(SceneIds id) : Scene(id)
{
}

SCENE_TITLE::~SCENE_TITLE()
{
}

void SCENE_TITLE::Init()
{
	
}

void SCENE_TITLE::Release()
{
}

void SCENE_TITLE::Enter()
{
}

void SCENE_TITLE::Exit()
{
}

void SCENE_TITLE::Update(float dt)
{
	Scene::Update(dt);

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SceneMgr::Instance().ChangeScene(SceneIds::SCENE_DEV2);
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		GameObject* findGo = FindGo("Message");
		findGo->SetActive(!findGo->GetActive());
	}

}
