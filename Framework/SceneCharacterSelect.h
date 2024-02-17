#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

class SceneCharacterSelect : public Scene
{
protected:

	int characterNumber = 5;
	float characterInterval = 0.f;

	bool isP2Turn = false;
	int selectNumP1 = 0;
	int selectNumP2 = 0;
	SpriteGo* selectMarkerP1 = nullptr;
	SpriteGo* selectMarkerP2 = nullptr;

	TextGo* selectMessage = nullptr;

public:
	SceneCharacterSelect(SceneIds id);
	virtual ~SceneCharacterSelect();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void MoveSelectMarker(SpriteGo* selectMarker, int& selectNum, Sides markerDir);
};