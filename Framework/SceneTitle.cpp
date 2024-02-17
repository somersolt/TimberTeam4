#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"


SCENE_TITLE::SCENE_TITLE(SceneIds id) : Scene(id)
{
}

SCENE_TITLE::~SCENE_TITLE()
{
}

void SCENE_TITLE::Init()
{
	texResMgr.Load("graphics/title.png");
	fontResMgr.Load("fonts/KOMIKAP_.ttf");

	SpriteGo* title = new SpriteGo("title");

	title->SetTexture("graphics/title.png");
	AddGo(title);

	titleMsg = new TextGo("titleMsg");
	titleMsg->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 80, sf::Color::White);
	titleMsg->SetString("Press Enter To Start");
	titleMsg->SetOrigin(Origins::MC);
	titleMsg->SetPosition({ 1920.f / 2, 1080.f / 2 + 150 });
	AddGo(titleMsg);


}

void SCENE_TITLE::Release()
{
	Scene::Release();
	titleMsg = nullptr;
}

void SCENE_TITLE::Enter()
{

}

void SCENE_TITLE::Exit()
{
	GameObject* findGo = FindGo("title");
	RemoveGo(findGo);
	//findGo->SetActive(!findGo->GetActive());
	RES_MGR_TEXTURE.Unload("graphics/title.png");

}

void SCENE_TITLE::Update(float dt)
{
	Scene::Update(dt);

	titleMsgTimer += dt;
	GameObject* findTitleMsg = FindGo("titleMsg");
	if (titleMsgTimer > 1.f)
	{
		findTitleMsg->SetActive(!findTitleMsg->GetActive());
		titleMsgTimer = 0;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SCENE_GAME);
	}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	//{
	//	GameObject* findGo = FindGo("Message");
	//	findGo->SetActive(!findGo->GetActive());
	//}

}