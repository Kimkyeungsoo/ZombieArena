#include "UIManager.h"
#include "TextureHolder.h"
#include "ViewManager.h"
#include "../plyer/Player.h"
#include "GameLevelData.h"
#include "..\utils\InputMgr.h"
#include <sstream>

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
		Init_GameOverScene();
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
		window.setMouseCursorVisible(true);
		Draw_GameOverScene(window);
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

	stringstream ss;
	ss << GameLevelData::GetInstance()->GetHighScore();
	textHighScoreNumber.setString(ss.str());
	textHighScoreNumber.setPosition(1680.f, 10.f);
	textHighScoreNumber.setCharacterSize(45);
	textHighScoreNumber.setFillColor(Color::White);
	textHighScoreNumber.setFont(fontZombiecontrol);

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
	window.draw(textHighScoreNumber);
}

void UIManager::Init_PlayScene()
{	
	textScore.setString("SCORE: ");
	textScore.setPosition(150.f, 10.f);
	textScore.setCharacterSize(45);
	textScore.setFillColor(Color::White);
	textScore.setFont(fontZombiecontrol);

	textScoreNumber.setPosition(280.f, 10.f);
	textScoreNumber.setCharacterSize(45);
	textScoreNumber.setFillColor(Color::White);
	textScoreNumber.setFont(fontZombiecontrol);

	textWave.setString("WAVE:");
	textWave.setPosition(1300.f, 980.f);
	textWave.setCharacterSize(45);
	textWave.setFillColor(Color::White);
	textWave.setFont(fontZombiecontrol);

	textWaveNumber.setPosition(1430.f, 980.f);
	textWaveNumber.setCharacterSize(45);
	textWaveNumber.setFillColor(Color::White);
	textWaveNumber.setFont(fontZombiecontrol);

	textZombieCount.setString("ZOMBIES: ");
	textZombieCount.setPosition(1550.f, 980.f);
	textZombieCount.setCharacterSize(45);
	textZombieCount.setFillColor(Color::White);
	textZombieCount.setFont(fontZombiecontrol);

	textZombieCountNumber.setPosition(1730.f, 980.f);
	textZombieCountNumber.setCharacterSize(45);
	textZombieCountNumber.setFillColor(Color::White);
	textZombieCountNumber.setFont(fontZombiecontrol);

	textHealth.setPosition(450.f, 980.f);
	textHealth.setCharacterSize(45);
	textHealth.setFillColor(Color::Red);
	textHealth.setFont(fontZombiecontrol);

	textAmmo.setPosition(200.f, 980.f);
	textAmmo.setCharacterSize(45);
	textAmmo.setFillColor(Color::Yellow);
	textAmmo.setFont(fontZombiecontrol);

	textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(140.f, 975.f);
		
	// PlayScene에서 사용될 UI 초기설정 등록
}

void UIManager::Draw_PlayScene(RenderWindow& window)
{
	window.setView(ViewManager::GetInstance()->GetUiView());
	ViewManager::GetInstance()->draw(window);
	window.draw(textHighScore);
	window.draw(textHighScoreNumber);
	window.draw(textScore);
	window.draw(textScoreNumber);
	window.draw(textWave);
	window.draw(textWaveNumber);
	window.draw(textZombieCount);
	window.draw(textZombieCountNumber);
	window.draw(textAmmo);
	window.draw(spriteAmmoIcon);
	window.draw(textHealth);
	// PlayScene에서 사용되는 UI들 Draw
}

void UIManager::Update_PlayScene()
{
	int haveAmmo = Player::GetInstance()->GetHaveAmmo();
	int totalAmmo = Player::GetInstance()->GetTotalAmmo();

	stringstream ssScore;
	ssScore << GameLevelData::GetInstance()->GetScore();
	textScoreNumber.setString(ssScore.str());

	stringstream ssHighScore;
	ssHighScore << GameLevelData::GetInstance()->GetHighScore();
	textHighScoreNumber.setString(ssHighScore.str());

	stringstream ssWave;
	ssWave << GameLevelData::GetInstance()->GetWave();
	textWaveNumber.setString(ssWave.str());

	stringstream ssCountZombies;
	ssCountZombies << GameLevelData::GetInstance()->GetCountZombies();
	textZombieCountNumber.setString(ssCountZombies.str());

	stringstream ssAmmo;
	ssAmmo << haveAmmo << "/" << totalAmmo;
	textAmmo.setString(ssAmmo.str());

	stringstream sshealth;
	sshealth << Player::GetInstance()->GetHealth();
	textHealth.setString(sshealth.str());
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

void UIManager::Update_UpgradeScene()
{
	bool isChooseUpgrade = false;
	auto pos = InputMgr::GetMousePosition();

	for (int i = 0; i < 6; ++i)
	{
		if (textUpgrades[i].getGlobalBounds().contains(pos.x, pos.y))
		{
			textUpgrades[i].setFillColor(Color::Red);
			// 클릭했을 때
			if (InputMgr::GetMouseButtonDown(Mouse::Button::Left))
			{
				switch (i)
				{
				case 0:
					isChooseUpgrade = true;
					break;
				case 1:
					GameLevelData::GetInstance()->UpgradeClipSize();
					isChooseUpgrade = true;
					break;
				case 2:
					Player::GetInstance()->UpgradeMaxHealth();
					isChooseUpgrade = true;
					break;
				case 3:
					Player::GetInstance()->UpgradeSpeed();
					isChooseUpgrade = true;
					break;
				}
			}
		}
		else
		{
			textUpgrades[i].setFillColor(Color::White);
		}
	}

	if(isChooseUpgrade)
		SceneManager::GetInstance()->LoadScene(SCENE_TYPE::PLAY);
}

void UIManager::Init_GameOverScene()
{
	textGameOver.setString("~ GAME OVER ~");
	textGameOver.setPosition(730.f, 600.f);
	textGameOver.setCharacterSize(75);
	textGameOver.setFillColor(Color::White);
	textGameOver.setFont(fontZombiecontrol);

	textRestart.setString("PRESS ENTER KEY TO RESTART");
	textRestart.setPosition(525.f, 700.f);
	textRestart.setCharacterSize(75);
	textRestart.setFillColor(Color::White);
	textRestart.setFont(fontZombiecontrol);
}

void UIManager::Draw_GameOverScene(RenderWindow& window)
{
	window.draw(textGameOver);
	window.draw(textRestart);
}
