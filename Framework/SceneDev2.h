#pragma once

class SCENE_DEV2 : public Scene
{
protected:

public:
	SCENE_DEV2(SceneIds id);
	virtual ~SCENE_DEV2();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

