#pragma once
#include "Player.h"

class SCENE_BATTLE;
class Tree;

class Player2p : public Player
{
protected:
	SCENE_BATTLE* sceneBattle;
	Tree* tree;

public:
	Player2p(const std::string& name = "");
	virtual ~Player2p() = default;

	std::string texIdPlayer2p = "graphics/player2.png";

	//void SetPosition(const sf::Vector2f& pos) override;
	//void SetScale(const sf::Vector2f& scale) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
