#include "pch.h"
#include "SceneBattle.h"
#include "SpriteGo.h"
#include "BgMovingGo.h"
#include "BgBeeGo.h"
#include "UiScore.h"
#include "UiTimeBar.h"
#include "Tree.h"
#include "EffectLog.h"
#include "Player.h"
#include "Player1p.h"
#include "Player2p.h"


SCENE_BATTLE::SCENE_BATTLE(SceneIds id)
	: Scene(id)
{
}

SCENE_BATTLE::~SCENE_BATTLE()
{
}

void SCENE_BATTLE::Init()
{

	soundResMgr.Load("sound/out_of_time.wav");
	sfxTimeOver.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/out_of_time.wav"));


	SpriteGo* newSpriteGo = new SpriteGo("BG");
	newSpriteGo->SetTexture("graphics/background.png");
	AddGo(newSpriteGo);

	sf::FloatRect movingBounds({ -200.f, 0.f }, { 1920.f + 400.f, 600.f });

	for (int i = 0; i < 3; ++i)
	{
		BgMovingGo* newMovingGo = new BgMovingGo(std::string("Cloud") + std::to_string(i));
		newMovingGo->SetTexture("graphics/cloud.png");
		newMovingGo->SetOrigin(Origins::MC);
		newMovingGo->SetFlipX(true);
		newMovingGo->bounds = movingBounds;
		AddGo(newMovingGo);
	}

	tree1 = new Tree("Tree1");
	tree1->SetPosition({ 1920.f / 2 - 400, 900.f });
	AddGo(tree1);

	tree2 = new Tree("Tree2");
	tree2->SetPosition({ 1920.f / 2 + 400, 900.f });
	AddGo(tree2);


	player1 = new Player1p("Player1");
	AddGo(player1);

	player2 = new Player2p("Player2");
	AddGo(player2);

	BgBeeGo* beeGo = new BgBeeGo("Bee");
	beeGo->SetTexture(texResMgr.Get("graphics/bee.png"));
	beeGo->SetOrigin(Origins::MC);
	beeGo->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGo(beeGo);

	sf::Vector2f uiTimeBarPos = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	uiTimeBarPos.x *= 0.5f;
	uiTimeBarPos.x -= 200.f;
	uiTimeBarPos.y *= 0.9f;

	// UI OBJECTS
	uiScore1 = new UiScore("Ui Score1");
	uiScore1->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 40, sf::Color::White);
	AddGo(uiScore1);

	uiScore2 = new UiScore("Ui Score2");
	uiScore2->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 40, sf::Color::White);
	uiScore2->SetPosition({ 1920.f * 0.5, 0 });
	AddGo(uiScore2);



	sf::Vector2f timeSize(400.f, 80.f);
	float timeBarDuration = 10.f;

	timeBar = new UiTimeBar("Time Bar");
	timeBar->timeBarSize = timeSize;
	timeBar->Reset();
	timeBar->timeBarSpeed = -timeSize.x / timeBarDuration;
	timeBar->SetOrigin(Origins::ML);
	timeBar->SetPosition({ 1920 / 2 - 200, 1080 - 100 });
	timeBar->SetColor(sf::Color::Red);
	timeBar->SetValue(timeBar->timeBarCurrSize.x);
	AddGo(timeBar);

	uiMsg = new TextGo("Center Message");
	uiMsg->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"),
		"PRESS ENTER TO START!", 75, sf::Color::White);
	uiMsg->SetPosition({ 1920.f / 2, 1080.f / 2 });
	uiMsg->SetOrigin(Origins::MC);
	AddGo(uiMsg);


	uiWinner = new TextGo("Center Message");
	uiWinner->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"),
		"Draw", 100, sf::Color::White);
	uiWinner->SetPosition({ 1920.f / 2, 1080.f / 2 - 200 });
	uiWinner->SetOrigin(Origins::MC);
	AddGo(uiWinner);


	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SCENE_BATTLE::Release()
{
	Scene::Release();

	uiScore1 = nullptr;
	uiScore2 = nullptr;
	uiMsg = nullptr;
}

void SCENE_BATTLE::Enter()
{
	player1->SetPosition(tree1->GetPosition());
	player2->SetPosition(tree2->GetPosition());

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SCENE_BATTLE::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SCENE_BATTLE::Update(float dt)
{
	Scene::Update(dt);

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SCENE_BATTLE::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SCENE_BATTLE::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
	}
	//timeBar->AddTime(50);

	auto it = useEffectList.begin();
	while (it != useEffectList.end())
	{
		EffectLog* effectGo = *it;
		if (!effectGo->GetActive())
		{
			RemoveGo(effectGo);
			it = useEffectList.erase(it);
			unuseEffectList.push_back(effectGo);
		}
		else
		{
			++it;
		}
	}
	if (timeBar->timeBarCurrSize.x == 0)
	{
		SetStatus(Status::GameOver);
	}
	OnPlayerDie();

}

void SCENE_BATTLE::UpdateGameOver(float dt)
{
	WinnerCheck();
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		uiScore1->Reset();
		uiScore2->Reset();
		timeBar->Reset();
	}

}

void SCENE_BATTLE::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}


void SCENE_BATTLE::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SCENE_BATTLE::OnChop()
{
	// ���� ����
	uiScore1->AddScore(10);
	uiScore2->AddScore2(10);
}

void SCENE_BATTLE::OnPlayerDie()
{
	if (!(player1->IsAlive()) && !(player2->IsAlive()))
	{
		SetStatus(Status::GameOver);
	}
}


void SCENE_BATTLE::WinnerCheck()
{
	if (uiScore1->GetScore() == uiScore2->GetScore())
	{
		uiWinner->SetString("Draw!");
	}
	else if (uiScore1->GetScore() > uiScore2->GetScore())
	{
		uiWinner->SetString("Winner is Player 1!");
	}
	else
	{
		uiWinner->SetString("Winner is Player 2!");
	}
}

void SCENE_BATTLE::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Awake:
		timer = duration;
		timeBar->SetValue(timer / duration);
		FRAMEWORK.SetTimeScale(0.f);
		uiMsg->SetActive(true);
		uiMsg->SetString("PRESS ENTER TO START!");
		uiWinner->SetActive(false);
		break;
	case Status::Game:
		if (prevStatus == Status::GameOver)
		{
			timer = duration;
			timeBar->SetValue(timer / duration);
			player1->Reset();
			tree1->Reset();
			player2->Reset();
			tree2->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		uiMsg->SetActive(false);
		uiMsg->SetString("");
		uiWinner->SetActive(false);
		break;
	case Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		uiMsg->SetActive(true);
		uiMsg->SetString("PRESS ENTER TO RESTART!");
		uiWinner->SetActive(true);
		break;
	case Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		uiMsg->SetActive(true);
		uiMsg->SetString("PRESS ESC TO RESUME!");
		uiWinner->SetActive(false);
		break;
	}
}



void SCENE_BATTLE::PlayEffectLog1(Sides side)
{
	EffectLog* effectLog1 = nullptr;
	if (unuseEffectList.empty())
	{
		effectLog1 = new EffectLog();
		effectLog1->SetTexture("graphics/log.png");
		effectLog1->SetOrigin(Origins::BC);
		effectLog1->Init();
	}
	else
	{
		effectLog1 = unuseEffectList.front();
		unuseEffectList.pop_front();
	}

	effectLog1->SetActive(true);
	effectLog1->Reset();
	effectLog1->SetPosition(tree1->GetPosition());

	sf::Vector2f velocity(1000.f, -1000.f);
	if (side == Sides::RIGHT)
	{
		velocity.x *= -1.f;
	}
	effectLog1->Fire(velocity);

	useEffectList.push_back(effectLog1);
	AddGo(effectLog1);
}

void SCENE_BATTLE::PlayEffectLog2(Sides side)
{
	EffectLog* effectLog2 = nullptr;
	if (unuseEffectList.empty())
	{
		effectLog2 = new EffectLog();
		effectLog2->SetTexture("graphics/log.png");
		effectLog2->SetOrigin(Origins::BC);
		effectLog2->Init();
	}
	else
	{
		effectLog2 = unuseEffectList.front();
		unuseEffectList.pop_front();
	}

	effectLog2->SetActive(true);
	effectLog2->Reset();
	effectLog2->SetPosition(tree2->GetPosition());

	sf::Vector2f velocity(1000.f, -1000.f);
	if (side == Sides::RIGHT)
	{
		velocity.x *= -1.f;
	}
	effectLog2->Fire(velocity);

	useEffectList.push_back(effectLog2);
	AddGo(effectLog2);
}