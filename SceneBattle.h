#pragma once
#include "Scene.h"

class UiScore;
class TextGo;
class UiTimeBar;
class Tree;
class EffectLog;
class Player;

class SCENE_BATTLE : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	UiScore* uiScore = nullptr;
	TextGo* uiMsg = nullptr;
	UiTimeBar* timeBar = nullptr;

	Tree* tree = nullptr;
	Tree* tree2 = nullptr;
	Player* player = nullptr;
	Player* player2 = nullptr;

	std::list<EffectLog*> useEffectList;
	std::list<EffectLog*> unuseEffectList;

	Status currStatus;

	float duration = 3.f;
	float timer = 0.f;

	sf::Sound sfxTimeOver;

public:
	SCENE_BATTLE(SceneIds id);
	virtual ~SCENE_BATTLE();

	void SetStatus(Status newStatus);
	Status GetStatus() const { return currStatus; }
	void PlayEffectLog(Sides side);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void OnChop();
	void OnPlayerDie();

};
