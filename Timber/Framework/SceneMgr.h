#pragma once
#include "Singleton.h"

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SCENE_TITLE;
	SceneIds currentScene = startScene;

	std::string player1Id = "";
	std::string player2Id = "";

	Modes mode = Modes::NONE;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SetPlayerId(Players player, std::string playerId);
	std::string GetPlayerId(Players player) const;

	void SetMode(const Modes mode);
	Modes GetMode() const { return mode; }

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())