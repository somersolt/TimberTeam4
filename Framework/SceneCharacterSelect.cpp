#include "pch.h"
#include "SceneCharacterSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneCharacterSelect::SceneCharacterSelect(SceneIds id) : Scene(id)
{
}

SceneCharacterSelect::~SceneCharacterSelect()
{
	Release();
}

void SceneCharacterSelect::Init()
{



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



	isP2Turn = false;

	selectNumP1 = 1;
	selectMarkerP1 = new SpriteGo("Select Marker1");
	selectMarkerP1->SetTexture("graphics/marker1.png");
	selectMarkerP1->SetOrigin(Origins::BC);
	selectMarkerP1->SetPosition({ characterInterval,
		FRAMEWORK.GetWindowSize().y / 2.f - 150.f});
	AddGo(selectMarkerP1);

	selectMarkerP2 = new SpriteGo("Select Marker2");
	selectMarkerP2->SetTexture("graphics/marker2.png");
	selectMarkerP2->SetOrigin(Origins::BC);
	selectMarkerP2->SetPosition({ characterInterval,
		FRAMEWORK.GetWindowSize().y / 2.f - 150.f });
	selectMarkerP2->SetActive(false);
	AddGo(selectMarkerP2);



	selectMessage = new TextGo("Select Message");
	selectMessage->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"),
		"Player1: Select a Character!", 75, sf::Color::Red);
	selectMessage->SetOrigin(Origins::BC);
	selectMessage->SetPosition({ FRAMEWORK.GetWindowSize().x / 2.f,
		FRAMEWORK.GetWindowSize().y / 2.f - 300.f });
	AddGo(selectMessage);
}

void SceneCharacterSelect::Release()
{
	Scene::Release();

	selectMarkerP1 = nullptr;
	selectMarkerP2 = nullptr;

	selectMessage = nullptr;
}

void SceneCharacterSelect::Enter()
{
	Scene::Enter();

}

void SceneCharacterSelect::Exit()
{
	std::string player1Id = "graphics/player" + std::to_string(selectNumP1) + ".png";
	SCENE_MGR.SetPlayerId(Players::P1, player1Id);

	if (SCENE_MGR.GetMode() == Modes::MULTI)
	{
		std::string player2Id = "graphics/player" + std::to_string(selectNumP2) + ".png";
		SCENE_MGR.SetPlayerId(Players::P2, player2Id);
	}
}

void SceneCharacterSelect::Update(float dt)
{
	Sides markerDir = Sides::NONE;
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		markerDir = Sides::RIGHT;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		markerDir = Sides::LEFT;
	}

	if (markerDir != Sides::NONE)
	{
		if (!isP2Turn)
		{
			MoveSelectMarker(selectMarkerP1, selectNumP1, markerDir);
		}
		else
		{
			MoveSelectMarker(selectMarkerP2, selectNumP2, markerDir);
		}
	}
	



	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		if (SCENE_MGR.GetMode() == Modes::MULTI && !isP2Turn)
		{
			isP2Turn = true;
			selectMarkerP1->SetActive(false);
			selectMarkerP2->SetActive(true);
			selectNumP2 = 1;
			if (selectNumP2 == selectNumP1)
			{
				sf::Vector2f newMarkerPos = selectMarkerP2->GetPosition();
				newMarkerPos += sf::Vector2f(characterInterval, 0.f);
				selectMarkerP2->SetPosition(newMarkerPos);
				selectNumP2++;
			}

			selectMessage->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"),
				"Player2: Select a Character!", 75, sf::Color::Blue);
			selectMessage->SetOrigin(Origins::BC);
		}
		else
		{
			if (SCENE_MGR.GetMode() == Modes::SINGLE)
			{
				SCENE_MGR.ChangeScene(SceneIds::SCENE_GAME);
			}
			else if(SCENE_MGR.GetMode() == Modes::MULTI)
			{
				SCENE_MGR.ChangeScene(SceneIds::SCENE_BATTLE);
			}
		}
	}
}

void SceneCharacterSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneCharacterSelect::MoveSelectMarker(SpriteGo* selectMarker, int& selectNum, Sides markerDir)
{
	sf::Vector2f newMarkerPos = selectMarker->GetPosition();
	if (markerDir == Sides::RIGHT && selectNum != characterNumber)
	{
		newMarkerPos += sf::Vector2f(characterInterval, 0.f);
		selectNum++;
	}
	if (markerDir == Sides::LEFT && selectNum != 1)
	{
		newMarkerPos -= sf::Vector2f(characterInterval, 0.f);
		selectNum--;
	}
	selectMarker->SetPosition(newMarkerPos);
}
