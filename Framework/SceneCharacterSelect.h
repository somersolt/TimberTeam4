#pragma once
#include "Scene.h"

class SpriteGo;

class SceneCharacterSelect : public Scene
{
protected:
	// Modes mode = Modes::SINGLE;

	int characterNumber = 3;
	float characterInterval = 0.f;

	int currentSelectNum = 0;
	SpriteGo* selectSprite = nullptr;

public:
	SceneCharacterSelect(SceneIds id);
	virtual ~SceneCharacterSelect();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	// void SetMode(Modes mode);
};