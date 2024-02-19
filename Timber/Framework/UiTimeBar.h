#pragma once
#include "GameObject.h"
class UiTimeBar :
	public GameObject
{
protected:


public:
	UiTimeBar(const std::string& name = "");

	void Reset() override;

	void SetValue(float value);

	void Update(float dt) override;

	void AddTime(float addedTime); //매개변수로 조절가능하게

	void SetPosition(const sf::Vector2f pos);

	void SetOrigin(Origins preset) override;

	void SetOrigin(const sf::Vector2f& newOrigin) override;


	void SetSize(const sf::Vector2f size);

	void Draw(sf::RenderWindow& window) override;

	void SetColor(sf::Color color);

	sf::RectangleShape timeBar;
	sf::Vector2f timeBarSize;
	sf::Vector2f timeBarCurrSize;
	float timeBarDuration;
	float timeBarSpeed = -timeBarSize.x / timeBarDuration;
};

