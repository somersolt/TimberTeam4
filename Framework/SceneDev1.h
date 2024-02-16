#pragma once

class SCENE_DEV1 : public Scene
{
protected:

public:
	SCENE_DEV1(SceneIds id);
	virtual ~SCENE_DEV1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

