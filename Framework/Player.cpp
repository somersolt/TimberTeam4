#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "SceneBattle.h"
#include "Tree.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{
}

void Player::SetSide(Sides s)
{
	side = s;
	SetScale(scale);
	SetPosition(position);
}

void Player::OnDie()
{
	isAlive = false;
	isChopping = false;

	SetTexture(texIdRip);
	SetScale(scale);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sf::Vector2f spritePos = position;
	switch (side)
	{
	case Sides::LEFT:
		spritePos.x -= offsetPositionX;
		break;
	case Sides::RIGHT:
		spritePos.x += offsetPositionX;
		break;
	}
	sprite.setPosition(spritePos);
	sf::Vector2f axePos = spritePos;
	switch (side)
	{
	case Sides::LEFT:
		axePos.x -= axeLocalPosition.x;
		axePos.y += axeLocalPosition.y;
		break;
	case Sides::RIGHT:
		axePos.x += axeLocalPosition.x;
		axePos.y += axeLocalPosition.y;
		break;
	}
	spriteAxe.setPosition(axePos);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sf::Vector2f playerScale = scale;
	sf::Vector2f axeScale = scale;

	bool playerFilpX = playerSide != side;
	bool axeFilpX = axeSide != side;

	if (playerFilpX)
	{
		playerScale.x = -scale.x;
	}
	if (axeFilpX)
	{
		axeScale.x = -scale.x;
	}

	if (isFlipY)
	{
		playerScale.y = -scale.y;
		axeScale.y = -scale.y;
	}

	if (isAlive)
	{
		sprite.setScale(playerScale);
	}
	else
	{
		sprite.setScale(scale);
	}
	spriteAxe.setScale(axeScale);
}


void Player::Init()
{
	RES_MGR_SOUND_BUFFER.Load("sound/chop.wav");
	RES_MGR_SOUND_BUFFER.Load("sound/death.wav");

	SpriteGo::Init();
	SetTexture(texIdPlayer);
	spriteAxe.setTexture(ResourceMgr<sf::Texture>::Instance().Get(texIdAxe));

	SetOrigin(Origins::BC);
	Utils::SetOrigin(spriteAxe, Origins::ML);

	sfxChop.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/chop.wav"));
	sfxDeath.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/death.wav"));
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	SetTexture(texIdPlayer); 
	isAlive = true;
	isChopping = false;


	sceneBattle = dynamic_cast<SCENE_BATTLE*>(SCENE_MGR.GetCurrentScene());
	tree = dynamic_cast<Tree*>(sceneBattle->FindGo("Tree"));


	//if (sceneGame)
	//{
	//	sceneGame = dynamic_cast<SCENE_GAME*>(SCENE_MGR.GetCurrentScene());
	//	tree = dynamic_cast<Tree*>(sceneGame->FindGo("Tree"));
	//}
	//else if (sceneBattle)
	//{
	//	
	//}
	

	SetSide(Sides::RIGHT);
}

void Player::MultiInput()
{
	Sides inputSide = Sides::NONE;

	if (sceneBattle->GetStatus() == SCENE_BATTLE::Status::Game)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			inputSide = Sides::LEFT;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			inputSide = Sides::RIGHT;
		}

		if (inputSide != Sides::NONE)
		{
			isChopping = true;
			sfxChop.play();

			Sides branchSide = tree->Chop(inputSide);



			SetSide(inputSide);

			if (side != branchSide)
			{
				sceneBattle->OnChop();
				//sceneGame->OnChop();
			}
			else
			{
				sceneBattle->OnPlayerDie();
				//sceneGame->OnPlayerDie();
				OnDie();
				sfxDeath.play();
			}
			if (sceneBattle->GetStatus() != SCENE_BATTLE::Status::GameOver)
			{
				sceneBattle->PlayEffectLog(inputSide);
				//sceneGame->PlayEffectLog(inputSide);
			}
		}
	}



	if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		isChopping = false;
	}
}

void Player::Update(float dt)
{
	if (sceneBattle->GetStatus() != SCENE_BATTLE::Status::Game)
		return;

	//if (sceneGame->GetStatus() != SCENE_GAME::Status::Game)
	//	return;

	MultiInput();

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (isChopping)
	{
		window.draw(spriteAxe);
	}
}
