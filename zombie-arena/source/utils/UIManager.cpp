#include "UIManager.h"


void UIManager::Init(SCENE_TYPE type)
{
	fontZombiecontrol.loadFromFile("fonts/zombiecontrol.ttf");

	switch (type)
	{
	case SCENE_TYPE::TITLE:
		Init_TitleScene();
		break;
	case SCENE_TYPE::PLAY:
		Init_PlayScene();
		break;
	case SCENE_TYPE::UPGRADE:
		Init_UpgradeScene();
		break;
	case SCENE_TYPE::GAME_OVER:
		break;
	case SCENE_TYPE::NONE:
		break;
	default:
		break;
	}

}

void UIManager::Draw(SCENE_TYPE type, RenderWindow& window)
{
	switch (type)
	{
	case SCENE_TYPE::TITLE:
		window.setMouseCursorVisible(true);
		Draw_TitleScene(window);
		break;
	case SCENE_TYPE::PLAY:
		window.setMouseCursorVisible(false);
		Draw_PlayScene(window);
		break;
	case SCENE_TYPE::UPGRADE:
		window.setMouseCursorVisible(true);
		Draw_UpgradeScene(window);
		break;
	case SCENE_TYPE::GAME_OVER:
		break;
	case SCENE_TYPE::NONE:
		break;
	default:
		break;
	}
}

void UIManager::Init_TitleScene()
{
	textMessage.setString("PRESS ENTER TO PLAY");
	textMessage.setPosition(250.f, 900.f);
	textMessage.setCharacterSize(75);
	textMessage.setFillColor(Color::White);
	textMessage.setFont(fontZombiecontrol);

	textHighScore.setString("HIGH SCORE: ");
	textHighScore.setPosition(1450.f, 10.f);
	textHighScore.setCharacterSize(45);
	textHighScore.setFillColor(Color::White);
	textHighScore.setFont(fontZombiecontrol);
}

void UIManager::SetTextRect(Text& text)
{
	textRect = text.getLocalBounds();
	text.setOrigin(
		textRect.left + textRect.width * 0.5f,
		textRect.top + textRect.height * 0.5f
	);
}

void UIManager::Draw_TitleScene(RenderWindow& window)
{
	window.draw(textMessage);
	window.draw(textHighScore);
}

void UIManager::Init_PlayScene()
{
	// PlayScene에서 사용될 UI 초기설정 등록
}

void UIManager::Draw_PlayScene(RenderWindow& window)
{
	// PlayScene에서 사용되는 UI들 Draw
}

void UIManager::Init_UpgradeScene()
{
	for (int i = 0; i < 6; ++i)
	{
		Text text;
		text.setPosition(250.f, 300.f + i * 80.f);
		text.setCharacterSize(70.f);
		text.setFillColor(Color::White);
		text.setFont(fontZombiecontrol);
		textUpgrades.push_back(text);
	}

	textUpgrades[0].setString("1- INCREASED RATE OF FIRE");
	textUpgrades[1].setString("2- INCREASED CLIP SIZE(NEXT RELOAD)");
	textUpgrades[2].setString("3- INCREASED MAX HEALTH");
	textUpgrades[3].setString("4- INCREASED RUN SPEED");
	textUpgrades[4].setString("5- MORE AND BETTER HEALTH PICKUPS");
	textUpgrades[5].setString("6- MORE AND BETTER AMMO PICKUPS");
}

void UIManager::Draw_UpgradeScene(RenderWindow& window)
{
	for (auto& text : textUpgrades)
		window.draw(text);
}
