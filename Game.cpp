#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h" 
#include "SplashScreen.h"
#include <iostream>
#include "GameOver.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Escape the Apocalypse");

	_mainWindow.setFramerateLimit(60);

	Player *player1 = new Player();
	player1->SetPosition((SCREEN_WIDTH / 2), 700);
	_gameObjectManager.Add("Player1", player1);
	srand(time(0));
	
	int numZ = 100;
	int i = 1;
	while (i <= numZ) {
		Zombie *ball = new Zombie();
		ball->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
		_gameObjectManager.Add("Ball" + i, ball);
		i++;
	}
	
	/*
	Zombie *ball1 = new Zombie();
	ball1->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball1", ball1);
				
	Zombie *ball2 = new Zombie();
	ball2->SetPosition(std::rand() % SCREEN_WIDTH , std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball2", ball2);

	Zombie *ball3 = new Zombie();
	ball3->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball3", ball3);
	
	Zombie *ball4 = new Zombie();
	ball4->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball4", ball4);

	Zombie *ball5 = new Zombie();
	ball5->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball5", ball5);

	Zombie *ball6 = new Zombie();
	ball6->SetPosition(std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT);
	_gameObjectManager.Add("Ball6", ball6);
	
	*/
	
	_gameState = Game::ShowingSplash;
	
	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}


sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
		case Game::ShowingMenu:
	      {
	        ShowMenu();
	        break;
	      }
		case Game::ShowingSplash:
		   {
		    ShowSplashScreen();
			break;
		   }
		case Game::Playing:
		{
			_mainWindow.clear(sf::Color(230, 230, 230));

			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.display();
			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
			}
			//std::cout << "inside gameloop" << Zombie().transform << std::endl;
			if (Zombie().transform == true)
			{
				ShowGameOver();
				std::cout << "Showing Game Over" << std::endl;
			}
			
			break;	
			}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
	std::cout << "This works!" << std::endl;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Exiting;
			break;
		case MainMenu::Play:
			_gameState = Playing;
			break;
	}
}

void Game::ShowGameOver()
{
	GameOver gameOver;
	gameOver.Show(_mainWindow);
	_gameState = Game::GOver;

}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;