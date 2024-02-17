#pragma once
#include "Player.h"

class SCENE_BATTLE;
class Tree;

class Player1p : public Player
{
protected:
    SCENE_BATTLE* sceneBattle;
    Tree* tree;

public:
    Player1p(const std::string& name = "");
    virtual ~Player1p() = default;

    std::string texIdPlayer1p = "graphics/player.png";

	//void SetPosition(const sf::Vector2f& pos) override;
	//void SetScale(const sf::Vector2f& scale) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

