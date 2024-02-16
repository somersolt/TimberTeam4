#pragma once

class SCENE_MOD_SELECT : public Scene
{
protected:

public:
	SCENE_MOD_SELECT(SceneIds id);
	virtual ~SCENE_MOD_SELECT();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

