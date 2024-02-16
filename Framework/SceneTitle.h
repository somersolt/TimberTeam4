#pragma once

class SCENE_TITLE : public Scene
{
protected:

public:
	SCENE_TITLE(SceneIds id);
	virtual ~SCENE_TITLE();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};

