#include "pch.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneGame.h"
#include "SceneBattle.h"


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
	scenes.push_back(new SCENE_BATTLE(SceneIds::SCENE_BATTLE));

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
	// TO-DO: ��� ���� ������Ʈ ������Ʈ ���� �Ŀ� �� ��ȯ �ǵ���

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
