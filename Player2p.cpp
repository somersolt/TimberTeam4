#include "pch.h"
#include "Player2p.h"
#include "SceneBattle.h"
#include "Tree.h"

Player2p::Player2p(const std::string& name)
	: Player(name)
{
}


void Player2p::Init()
{
	RES_MGR_SOUND_BUFFER.Load("sound/chop.wav");
	RES_MGR_SOUND_BUFFER.Load("sound/death.wav");

	SpriteGo::Init();
	SetTexture(texIdPlayer2p);
	spriteAxe.setTexture(ResourceMgr<sf::Texture>::Instance().Get(texIdAxe));

	SetOrigin(Origins::BC);
	Utils::SetOrigin(spriteAxe, Origins::ML);

	sfxChop.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/chop.wav"));
	sfxDeath.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/death.wav"));
}

void Player2p::Release()
{
	SpriteGo::Release();
}

void Player2p::Reset()
{
	SpriteGo::Reset();

	SetTexture(texIdPlayer2p);
	isAlive = true;
	isChopping = false;

	sceneBattle = dynamic_cast<SCENE_BATTLE*>(SCENE_MGR.GetCurrentScene());
	tree = dynamic_cast<Tree*>(sceneBattle->FindGo("Tree2"));

	SetSide(Sides::RIGHT);
}

void Player2p::Update(float dt)
{
	if (sceneBattle->GetStatus() != SCENE_BATTLE::Status::Game)
		return;

	Sides inputSide = Sides::NONE;

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
		}
		else
		{
			sceneBattle->OnPlayerDie();
			OnDie();
			sfxDeath.play();
		}
		if (sceneBattle->GetStatus() != SCENE_BATTLE::Status::GameOver)
		{
			sceneBattle->PlayEffectLog(inputSide);
		}
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		isChopping = false;
	}
}

void Player2p::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (isChopping)
	{
		window.draw(spriteAxe);
	}
}
