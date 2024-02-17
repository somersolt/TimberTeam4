#include "pch.h"
#include "SceneModSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"

SCENE_MOD_SELECT::SCENE_MOD_SELECT(SceneIds id) : Scene(id)
{
}

SCENE_MOD_SELECT::~SCENE_MOD_SELECT()
{
}

void SCENE_MOD_SELECT::Init()
{
	texResMgr.Load("graphics/BgModeSelect.png");
	SpriteGo* BgModeSelect = new SpriteGo("BgModeSelect");
	AddGo(BgModeSelect);

	

}

void SCENE_MOD_SELECT::Release()
{
}

void SCENE_MOD_SELECT::Enter()
{
}

void SCENE_MOD_SELECT::Exit()
{
}

void SCENE_MOD_SELECT::Update(float dt)
{
	//Scene::Update(dt);

//	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
//	{
//		SceneMgr::Instance().ChangeScene(SceneIds::SCENE_DEV1);
//	}
}
