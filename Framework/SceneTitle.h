#pragma once
#include "Scene.h"

class TextGo;

class SCENE_TITLE : public Scene
{
protected:

	TextGo* titleMsg = nullptr;
	float titleMsgTimer = 0.f;

public:
	SCENE_TITLE(SceneIds id);
	virtual ~SCENE_TITLE();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

