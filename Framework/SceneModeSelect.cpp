#include "pch.h"
#include "SceneModeSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"

SCENE_MODE_SELECT::SCENE_MODE_SELECT(SceneIds id) : Scene(id)
{
}

SCENE_MODE_SELECT::~SCENE_MODE_SELECT()
{
}

void SCENE_MODE_SELECT::Init()
{
	texResMgr.Load("graphics/BgModeSelect.png");
	texResMgr.Load("graphics/single.png");
	texResMgr.Load("graphics/multi.png");
	texResMgr.Load("graphics/marker1.png");
	texResMgr.Load("graphics/marker2.png");

	SpriteGo* BgModeSelect = new SpriteGo("BgModeSelect");
	BgModeSelect->SetTexture("graphics/BgModeSelect.png");
	AddGo(BgModeSelect);

	modeMsg = new TextGo("modeMsg");
	modeMsg->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 60, sf::Color::White);
	modeMsg->SetOrigin(Origins::MC);
	modeMsg->SetPosition({ 1920.f / 2 , 1020.f / 3 });
	modeMsg->SetString("Press Enter To Select Mode");
	AddGo(modeMsg);

	singleModeIcon = new SpriteGo("singleModeIcon");
	singleModeIcon->SetTexture("graphics/single.png");
	singleModeIcon->SetOrigin(Origins::MC);
	singleModeIcon->SetPosition({ FRAMEWORK.GetWindowSize().x / 3.f , FRAMEWORK.GetWindowSize().y / 3.f * 2.f });
	AddGo(singleModeIcon);

	multiModeIcon = new SpriteGo("multiModeIcon");
	multiModeIcon->SetTexture("graphics/multi.png");
	multiModeIcon->SetOrigin(Origins::MC);
	multiModeIcon->SetPosition({ FRAMEWORK.GetWindowSize().x / 3.f * 2.f, FRAMEWORK.GetWindowSize().y / 3.f * 2.f });
	AddGo(multiModeIcon);

	modeMarker = new SpriteGo("modeMarker");
	modeMarker->SetTexture("graphics/marker1.png");
	modeMarker->SetOrigin(Origins::MC);
	modeMarker->SetPosition(singleModeIcon->GetPosition() + markerOffset);
	AddGo(modeMarker);


}

void SCENE_MODE_SELECT::Release()
{
}

void SCENE_MODE_SELECT::Enter()
{
}

void SCENE_MODE_SELECT::Exit()
{
}

void SCENE_MODE_SELECT::Update(float dt)
{
	Scene::Update(dt);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		modeMarker->SetPosition(singleModeIcon->GetPosition() + markerOffset);
		SelectMode = Modes::SINGLE;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		modeMarker->SetPosition(multiModeIcon->GetPosition() + markerOffset);
		SelectMode = Modes::MULTI;
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.SetMode(SelectMode);

		if (SCENE_MGR.GetMode() == Modes::SINGLE)
		{
			SceneMgr::Instance().ChangeScene(SceneIds::SCENE_CHARACTER_SELECT);
		}

		if (SCENE_MGR.GetMode() == Modes::MULTI)
		{
			SceneMgr::Instance().ChangeScene(SceneIds::SCENE_CHARACTER_SELECT);
		}
	}
}
