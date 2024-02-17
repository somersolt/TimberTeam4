#pragma once

class TextGo;
class SpriteGo;

class SCENE_MODE_SELECT : public Scene
{
protected:

	TextGo* modeMsg = nullptr;
	Modes SelectMode = Modes::NONE;
	SpriteGo* modeMarker = nullptr;
	SpriteGo* singleModeIcon = nullptr;
	SpriteGo* multiModeIcon = nullptr;
	sf::Vector2f markerOffset = { 0.f , -200.f };

public:
	SCENE_MODE_SELECT(SceneIds id);
	virtual ~SCENE_MODE_SELECT();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

