#include "pch.h"
#include "UiScore.h"

UiScore::UiScore(const std::string& name)
	: TextGo(name)
{
}

void UiScore::Reset()
{
	SetScore(0);
}

void UiScore::SetScore(int score)
{
	this->score = score;
	text.setString(textFormat + std::to_string(score));
}

void UiScore::AddScore(int addedScore)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		score += addedScore;
		SetScore(score);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		score += addedScore;
		SetScore(score);
	}
}
