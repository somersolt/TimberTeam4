#include "pch.h"
#include "Player1p.h"
#include "SceneBattle.h"
#include "Tree.h"

Player1p::Player1p(const std::string& name)
	: Player(name)
{
}


void Player1p::Init()
{
	RES_MGR_SOUND_BUFFER.Load("sound/chop.wav");
	RES_MGR_SOUND_BUFFER.Load("sound/death.wav");

	SpriteGo::Init();
	SetTexture(texIdPlayer1p);
	spriteAxe.setTexture(ResourceMgr<sf::Texture>::Instance().Get(texIdAxe));

	SetOrigin(Origins::BC);
	Utils::SetOrigin(spriteAxe, Origins::ML);

	sfxChop.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/chop.wav"));
	sfxDeath.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/death.wav"));
}

void Player1p::Release()
{
	SpriteGo::Release();
}

void Player1p::Reset()
{
	SpriteGo::Reset();

	SetTexture(texIdPlayer1p);
	isAlive = true;
	isChopping = false;

	sceneBattle = dynamic_cast<SCENE_BATTLE*>(SCENE_MGR.GetCurrentScene());
	tree = dynamic_cast<Tree*>(sceneBattle->FindGo("Tree1"));

	SetSide(Sides::RIGHT);
}

void Player1p::Update(float dt)
{
	if (!isAlive)
		return;

	Sides inputSide = Sides::NONE;

	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		inputSide = Sides::LEFT;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
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
		}
		else //나뭇가지 방향과 플레이어 방향이 일치할때(죽어야할때)
		{
			//sceneBattle->OnPlayerDie(); //게임오버 호출(두명이면 문제)
			OnDie();
			sfxDeath.play();
			
		}
		if (isAlive)
		{
			sceneBattle->PlayEffectLog1(inputSide);
		}
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::A) || InputMgr::GetKeyUp(sf::Keyboard::D))
	{
		isChopping = false;
	}
}

void Player1p::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (isChopping)
	{
		window.draw(spriteAxe);
	}
}
