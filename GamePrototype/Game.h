#pragma once
#include "BaseGame.h"
class Texture;
#include "SVGParser.h"
#include "SoundEffect.h"
#include "SoundStream.h"
#pragma once
#include <iostream>
using namespace std;
#include <utils.h>
#include <string>

using namespace utils;


class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:


	Point2f m_Pos{ Point2f(500.f, 100.f) };
	int m_PlayerSize{ 30 };
	float m_PlayerSpeed{ 250.f };

	int m_SwordTimer{ 0 };
	int m_SwordTimerLeft{ 0 };
	int m_SwordTimerUp{ 0 };
	int m_SwordTimerRight{ 0 };
	int m_SwordTimerDown{ 0 };

	Point2f	m_EnemyPos{ Point2f(00.f, 00.f) };
	int		m_EnemySize{ 50 };
	float	m_EnemySpeed{ 450.0f };
	float	m_EnemySpeedIncrease{ 1.002 };
	int gameState{ 1 };
	int m_attacksize{ 50 };
	

	int m_Score{};
	TTF_Font* m_pConsolasFont;
	Texture* m_pSwitchText;
	string m_StringCounter = "SCORE: 0";

	int m_Health{10};
	Texture* m_pSwitchHp;
	string m_StringHp = "HEALTH: 10";
	Texture* m_pSwitchPressR;
	string m_PressR = "PRESS R TO RETRY";

	Point2f m_CoinPos;
	int m_CoinSize{ 20 };

	Point2f m_GreenPos;
	int		m_GreenSize{ 30 };
	int		m_GreenCounter{ 1500 };
	bool	m_GreenActive{ false };


	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void GameOver();
	void Reset();
};