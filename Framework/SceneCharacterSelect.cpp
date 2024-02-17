#include "pch.h"
#include "SceneCharacterSelect.h"
#include "SpriteGo.h"

SceneCharacterSelect::SceneCharacterSelect(SceneIds id) : Scene(id)
{
}

SceneCharacterSelect::~SceneCharacterSelect()
{
}

void SceneCharacterSelect::Init()
{
	texResMgr.Load("graphics/player_select_bg.png");
	texResMgr.Load("graphics/bee.png");



	SpriteGo* bgSprite = new SpriteGo("Player Select Background");
	bgSprite->SetTexture("graphics/player_select_bg.png");
	AddGo(bgSprite);



	characterInterval = FRAMEWORK.GetWindowSize().x / (characterNumber + 1);
	for (int i = 1; i <= characterNumber; i++)
	{
		std::string playerId = "graphics/player" + std::to_string(i) + ".png";
		texResMgr.Load(playerId);
		SpriteGo* player = new SpriteGo("Player" + std::to_string(i));
		player->SetTexture(playerId);
		player->SetOrigin(Origins::MC);
		player->SetPosition({ characterInterval * i, FRAMEWORK.GetWindowSize().y / 2.f });
		AddGo(player);
	}



	currentSelectNum = 1;
	selectSprite = new SpriteGo("Select Marker");
	selectSprite->SetTexture("graphics/bee.png");
	selectSprite->SetOrigin(Origins::BC);
	selectSprite->SetPosition({ characterInterval, FRAMEWORK.GetWindowSize().y / 2.f - 150.f});
	AddGo(selectSprite);
}

void SceneCharacterSelect::Release()
{
	Scene::Release();
}

void SceneCharacterSelect::Enter()
{
	Scene::Enter();
}

void SceneCharacterSelect::Exit()
{
}

void SceneCharacterSelect::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		if (currentSelectNum != characterNumber)
		{
			selectSprite->SetPosition(selectSprite->GetPosition() + sf::Vector2f(characterInterval, 0.f));
			currentSelectNum++;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		if (currentSelectNum != 1)
		{
			selectSprite->SetPosition(selectSprite->GetPosition() - sf::Vector2f(characterInterval, 0.f));
			currentSelectNum--;
		}
	}
}

void SceneCharacterSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

//void SceneCharacterSelect::SetMode(Modes mode)
//{
//	this->mode = mode;
//}
