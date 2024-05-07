#include "pch.h"
#include "Game.h"
#include <iostream>
#include <Texture.h>
#include <utils.h>
using namespace utils;
#include "Matrix2x3.h"
#include <random>	

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pConsolasFont = TTF_OpenFont("Fonts/Inconsolata-Regular.ttf", 24);

	m_pSwitchText = new Texture(m_StringCounter, m_pConsolasFont, Color4f{ 1,1,1,1 });
	m_pSwitchHp = new Texture(m_StringHp, m_pConsolasFont, Color4f{ 1,1,1,1 });

	m_CoinPos = Point2f( rand() % 750 + 50.f , rand() % 400 + 50.f) ;
}

void Game::Cleanup( )
{
	TTF_CloseFont(m_pConsolasFont);
	delete m_pSwitchText;
	delete m_pSwitchHp;
}

void Game::Update(float elapsedSec)
{
	if (gameState == 1)
	{
		m_StringCounter = "Score: " + to_string(m_Score);
		delete m_pSwitchText;
		m_pSwitchText = new Texture(m_StringCounter, m_pConsolasFont, Color4f{ 1,1,1,1 });

		m_StringHp = "Health: " + to_string(m_Health);
		delete m_pSwitchHp;
		m_pSwitchHp = new Texture(m_StringHp, m_pConsolasFont, Color4f{ 1,1,1,1 });
	}
	else 
	{
		m_StringCounter = "Final Score: " + to_string(m_Score);
		m_pSwitchText = new Texture(m_StringCounter, m_pConsolasFont, Color4f{ 1,1,1,1 });
	}



	m_EnemyPos.x += ((m_Pos.x - m_EnemyPos.x) * m_EnemySpeed / (sqrt(pow(m_Pos.x - m_EnemyPos.x, 2) + pow(m_Pos.y - m_EnemyPos.y, 2)))) * elapsedSec;
	m_EnemyPos.y += ((m_Pos.y - m_EnemyPos.y) * m_EnemySpeed / (sqrt(pow(m_Pos.x - m_EnemyPos.x, 2) + pow(m_Pos.y - m_EnemyPos.y, 2)))) * elapsedSec;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_D])m_Pos.x += m_PlayerSpeed*elapsedSec;
	if (pStates[SDL_SCANCODE_S])	m_Pos.y -= m_PlayerSpeed*elapsedSec;
	if (pStates[SDL_SCANCODE_A])	m_Pos.x -= m_PlayerSpeed*elapsedSec;
	if (pStates[SDL_SCANCODE_W])	m_Pos.y += m_PlayerSpeed*elapsedSec;

	//std::cout << m_Pos.x << "   " << m_EnemyPos.x << std::endl;
	//std::cout << m_Pos.y << "    " << m_EnemyPos.y << std::endl;

	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.0f));
	//sword
	// SETTING TIMER
	if (gameState == 1)
	{
	if (m_SwordTimer == 0)
	{
		//left
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_SwordTimerLeft = 35;
			m_SwordTimer = 85;
		}
		//up
		if (pStates[SDL_SCANCODE_DOWN] && m_SwordTimer == 0)
		{
			m_SwordTimerUp = 35;
			m_SwordTimer = 85;
		}
		//right
		if (pStates[SDL_SCANCODE_RIGHT] && m_SwordTimer == 0)
		{
			m_SwordTimerRight = 35;
			m_SwordTimer = 85;
		}
		//down
		if (pStates[SDL_SCANCODE_UP] && m_SwordTimer == 0)
		{
			m_SwordTimerDown = 35;
			m_SwordTimer = 85;
		}
	}
	//timer counting down
	if (m_SwordTimer >0)
	{
		m_SwordTimer-=(1*elapsedSec);
	}
	if (m_SwordTimerLeft >0)
	{
		m_SwordTimerLeft -= (1 * elapsedSec);
	}
	if (m_SwordTimerUp >0)
	{
		m_SwordTimerUp -= (1 * elapsedSec);

	}if (m_SwordTimerRight >0)
	{
		m_SwordTimerRight -= (1 * elapsedSec);
	}
	if (m_SwordTimerDown >0)
	{
		m_SwordTimerDown -= (1 * elapsedSec);
	}

	
	Rectf(m_Pos.x-m_PlayerSize/2, m_Pos.y - m_PlayerSize / 2,m_PlayerSize, m_PlayerSize);

	// drawing attack hitboxes
	if (m_SwordTimerLeft > 0)
	{
		//utils::FillRect(m_Pos.x - m_PlayerSize * 2, m_Pos.y - m_PlayerSize * 2, m_PlayerSize * 1.5, m_PlayerSize * 4);
		if (utils::IsOverlapping(Rectf(m_EnemyPos.x - m_EnemySize / 2, m_EnemyPos.y - m_EnemySize / 2, m_EnemySize, m_EnemySize), Rectf(m_Pos.x - (m_PlayerSize / 2 + m_attacksize), m_Pos.y - m_attacksize / 2 - m_PlayerSize / 2, m_attacksize, m_attacksize + m_PlayerSize)))
		{
			m_Score += 10;
			m_EnemySpeed *= 1.01;
			//m_PlayerSpeed *= 0.998;
			int randomNumber = rand() % 4;
			if (randomNumber == 0)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 1)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 2)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 500.f;
			}
			if (randomNumber == 3)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 500.f;
			}
		}
	}
	//up
	if (m_SwordTimerUp > 0)
	{
		//utils::DrawRect(m_Pos.x - m_PlayerSize * 2, m_Pos.y - m_PlayerSize * 2, m_PlayerSize * 4, m_PlayerSize * 1.5);

		if (utils::IsOverlapping(Rectf(m_EnemyPos.x - m_EnemySize / 2, m_EnemyPos.y - m_EnemySize / 2, m_EnemySize, m_EnemySize), Rectf(m_Pos.x - m_PlayerSize / 2 - m_attacksize / 2, m_Pos.y - m_PlayerSize / 2 - m_attacksize, m_PlayerSize + m_attacksize, m_attacksize)))
		{
			//m_PlayerSpeed *= 0.998;
			m_Score += 10;
			m_EnemySpeed *= 1.01;
			int randomNumber = rand() % 4;
			if (randomNumber == 0)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 1)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 2)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 500.f;
			}
			if (randomNumber == 3)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 500.f;
			}
		}
	}
	//right
	if (m_SwordTimerRight > 0)
	{
		//utils::DrawRect(m_Pos.x + m_PlayerSize / 2, m_Pos.y - m_PlayerSize * 2, m_PlayerSize * 1.5, m_PlayerSize * 4);
		if (utils::IsOverlapping(Rectf(m_EnemyPos.x - m_EnemySize / 2, m_EnemyPos.y - m_EnemySize / 2, m_EnemySize, m_EnemySize), Rectf(m_Pos.x + m_PlayerSize / 2, m_Pos.y - m_attacksize / 2 - m_PlayerSize / 2, m_attacksize, m_attacksize + m_PlayerSize)))
		{
			//m_PlayerSpeed *= 0.998;
			m_Score += 10;
			m_EnemySpeed *= 1.01;
			int randomNumber = rand() % 4;
			if (randomNumber == 0)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 1)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 2)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 500.f;
			}
			if (randomNumber == 3)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 500.f;
			}
		}
	}
	//down
	if (m_SwordTimerDown > 0)
	{

		//utils::DrawRect(m_Pos.x - m_PlayerSize * 2, m_Pos.y + m_PlayerSize / 2, m_PlayerSize * 4, m_PlayerSize * 1.5);
		if (utils::IsOverlapping(Rectf(m_EnemyPos.x - m_EnemySize / 2, m_EnemyPos.y - m_EnemySize / 2, m_EnemySize, m_EnemySize), Rectf(m_Pos.x - m_PlayerSize / 2 - m_attacksize / 2, m_Pos.y + m_PlayerSize / 2, m_PlayerSize + m_attacksize, m_attacksize)))
		{
			//m_PlayerSpeed *= 0.998;
			m_Score += 10;
			m_EnemySpeed *= 1.01;
			int randomNumber = rand() % 4;
			if (randomNumber == 0)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 1)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 2)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 500.f;
			}
			if (randomNumber == 3)
			{
				m_EnemyPos.x = 850.f;
				m_EnemyPos.y = 500.f;
			}
		}
	}


		//enemy player collision
		if (m_Pos.x - m_PlayerSize / 2 < m_EnemyPos.x - m_EnemySize / 2 + m_EnemySize &&
			m_Pos.x - m_PlayerSize / 2 + m_PlayerSize > m_EnemyPos.x - m_EnemySize / 2 &&
			m_Pos.y - m_PlayerSize / 2 < m_EnemyPos.y - m_EnemySize / 2 + m_EnemySize &&
			m_Pos.y - m_PlayerSize / 2 + m_PlayerSize > m_EnemyPos.y - m_EnemySize / 2)
		{
			//std::cout << "hit";

			--m_Health;
			if (m_Health < 1)
			{
				std::cout << "Press R to retry" << std::endl;
				GameOver();
			}

			m_PlayerSpeed *= 0.9;
			m_PlayerSize += 10;


			int randomNumber = (rand() % 4);

			if (randomNumber == 0)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 1)
			{
				m_EnemyPos.x = 850;
				m_EnemyPos.y = 0;
			}
			if (randomNumber == 2)
			{
				m_EnemyPos.x = 0;
				m_EnemyPos.y = 500;
			}
			if (randomNumber == 3)
			{
				m_EnemyPos.x = 850;
				m_EnemyPos.y = 500;
			}
		}
		//coin player collision
		if (m_Pos.x - m_PlayerSize / 2 < m_CoinPos.x - m_CoinSize / 2 + m_CoinSize &&
			m_Pos.x - m_PlayerSize / 2 + m_PlayerSize > m_CoinPos.x - m_CoinSize / 2 &&
			m_Pos.y - m_PlayerSize / 2 < m_CoinPos.y - m_CoinSize / 2 + m_CoinSize &&
			m_Pos.y - m_PlayerSize / 2 + m_PlayerSize > m_CoinPos.y - m_CoinSize / 2)
		{
			m_CoinPos = Point2f(rand() % 750 + 50.f, rand() % 400 + 50.f);;
			m_Score += 50;
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	if (gameState == 1)
	{
		//Player
		utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		utils::FillRect(m_Pos.x - m_PlayerSize / 2, m_Pos.y - m_PlayerSize / 2, m_PlayerSize, m_PlayerSize);

		// draw enemies
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::FillRect(m_EnemyPos.x - m_EnemySize / 2, m_EnemyPos.y - m_EnemySize / 2, m_EnemySize, m_EnemySize);

		// draw coin
		utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
		utils::FillRect(m_CoinPos.x - m_CoinSize / 2, m_CoinPos.y - m_CoinSize / 2, m_CoinSize, m_CoinSize);

		
		//sword
		// drawing attack hitboxes
		utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.0f));
		if (m_SwordTimerLeft > 0)
		{
			utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.0f));
			utils::FillRect(m_Pos.x - (m_PlayerSize/2 +m_attacksize) , m_Pos.y - m_attacksize/2 -m_PlayerSize/2 , m_attacksize, m_attacksize + m_PlayerSize);
		}
		//down
		if (m_SwordTimerUp > 0)
		{
			utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.0f));
			utils::FillRect(m_Pos.x - m_PlayerSize/2 - m_attacksize/2 , m_Pos.y - m_PlayerSize/2-m_attacksize, m_PlayerSize + m_attacksize, m_attacksize);

		}
		//right
		if (m_SwordTimerRight > 0)
		{
			utils::FillRect(m_Pos.x + m_PlayerSize / 2, m_Pos.y - m_attacksize/2 -m_PlayerSize/2, m_attacksize, m_attacksize + m_PlayerSize);
		}
		//up
		if (m_SwordTimerDown > 0)
		{

			utils::FillRect(m_Pos.x - m_PlayerSize / 2 - m_attacksize / 2, m_Pos.y +m_PlayerSize/2, m_PlayerSize + m_attacksize, m_attacksize);
		}

		
		
	}

	//std::cout << m_Score << std::endl;
	if (gameState == 1)
	{
		m_pSwitchText->Draw(Point2f(0, 475));
		m_pSwitchHp->Draw(Point2f(0, 450));
	}
	else if (gameState == 0)
	{
		m_pSwitchText->Draw(Point2f(330, 350));
	}

	//utils::FillRect(m_Pos.x - m_PlayerSize / 2, m_Pos.y - m_PlayerSize / 2, m_PlayerSize, m_PlayerSize);
		//utils::FillRect(m_Pos.x - (m_PlayerSize / 2 + m_attacksize), m_Pos.y - m_attacksize / 2 - m_PlayerSize / 2, m_attacksize, m_attacksize + m_PlayerSize);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (gameState == 0)
	{
		//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
		switch (e.keysym.sym)
		{
		case SDLK_r:
			Reset();
			break;

	}

	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::GameOver()
{
	gameState = 0;
}

void Game::Reset()
{
	m_Pos = Point2f(500.f, 100.f);
	m_PlayerSize = 50;
	m_PlayerSpeed = 250.f;

	m_EnemyPos = Point2f(00.f, 00.f);
	m_EnemySpeed = 450.0f;

	m_CoinPos = Point2f(rand() % 650 + 100.f, rand() % 300 + 100.f);

	m_Score = 0;
	m_Health = 10;

	gameState = 1;
}