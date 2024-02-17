#include "pch.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneCharacterSelect.h"
#include "SceneGame.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();

	scenes.push_back(new SCENE_DEV1(SceneIds::SCENE_DEV1));
	scenes.push_back(new SCENE_DEV2(SceneIds::SCENE_DEV2));
	scenes.push_back(new SCENE_GAME(SceneIds::SCENE_GAME));

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	// TO-DO: 모든 게임 오브젝트 업데이트 끝난 후에 씬 전환 되도록

	scenes[(int)currentScene]->Exit();
	currentScene = id;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}

void SceneMgr::SetPlayerId(Players player, std::string playerId)
{
	switch (player)
	{
	case Players::P1:
		player1Id = playerId;
		break;
	case Players::P2:
		player2Id = playerId;
		break;
	default:
		break;
	}
}

std::string SceneMgr::GetPlayerId(Players player) const
{
	switch (player)
	{
	case Players::P1:
		return player1Id;
		break;
	case Players::P2:
		return player2Id;
		break;
	default:
		break;
	}
}

void SceneMgr::SetMode(const Modes mode)
{
	this->mode = mode;
}
