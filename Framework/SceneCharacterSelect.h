#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;

class SceneCharacterSelect : public Scene
{
protected:
	const int characterNumber = 16;
	const int characterRowNum = 4;
	const int characterColNum = 4;

	float characterIntervalX = 0.f;
	float characterIntervalY = 0.f;

	bool isP2Turn = false;
	int selectNumP1 = 0;
	int selectNumP2 = 0;
	SpriteGo* selectMarkerP1 = nullptr;
	SpriteGo* selectMarkerP2 = nullptr;
	float markerInterval = 100.f;

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