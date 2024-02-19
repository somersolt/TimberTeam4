#include "pch.h"
#include "UiTimeBar.h"


UiTimeBar::UiTimeBar(const std::string& name)
	:GameObject(name)
{
}

void UiTimeBar::Reset()
{
	timeBarCurrSize = timeBarSize;
	timeBar.setSize(timeBarSize);
}

void UiTimeBar::SetValue(float value)
{
	if (value < 0.f)
	{
		value = 0.f;
	}
	if (value > timeBarSize.x)
	{
		value = timeBarSize.x;
	}

}

void UiTimeBar::Update(float dt)
{
	timeBarCurrSize.x += timeBarSpeed * dt;
	timeBar.setSize(timeBarCurrSize);

	if (timeBarCurrSize.x <= 0.f)
	{
		timeBarCurrSize.x = 0.f;
	}
	if (timeBarCurrSize.x >= timeBarSize.x)
	{
		timeBarCurrSize.x = timeBarSize.x;
	}

}

void UiTimeBar::AddTime(float addedTime)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) || InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		timeBarCurrSize.x += addedTime;
	}
	timeBar.setSize(timeBarCurrSize);
}


void UiTimeBar::SetPosition(const sf::Vector2f pos)
{
	timeBar.setPosition(pos);
}

void UiTimeBar::SetOrigin(Origins preset)
{
	if (preset == Origins::CUSTOM)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(timeBar, originPreset);
}

void UiTimeBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::CUSTOM;
	origin = newOrigin;
	timeBar.setOrigin(newOrigin);
}

void UiTimeBar::SetSize(const sf::Vector2f size)
{
	timeBar.setSize(size);
}

void UiTimeBar::SetColor(sf::Color color)
{
	timeBar.setFillColor(color);
}

void UiTimeBar::Draw(sf::RenderWindow& window)
{
	window.draw(timeBar);
}


//
////시간에 따라 감소할 타임 바
//sf::Vector2f timeBarSize(400.f, 80.f);
//sf::Vector2f timeBarCurrentSize = timeBarSize;
//sf::RectangleShape timeBar;
//timeBar.setSize(timeBarCurrentSize);
//timeBar.setFillColor(sf::Color::Red);
//Utils::SetOrigin(timeBar, Origins::MC);
//timeBar.setPosition(1920 / 2, 1080 - 100);
//
////시간감소에 필요한 변수
//float timeBarDuration = 3.f;
//float timeBarSpeed = -timeBarSize.x / timeBarDuration;
