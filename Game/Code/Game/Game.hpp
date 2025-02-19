#pragma once
#include "Game/GameCommon.hpp"

class Entity;
class Player;
class Prop;

enum class GameState 
{
	ATTRACT_MODE,
	PLAY_MODE,
};
class Game
{
public:
	Game();
	~Game();

	void Startup();
	void Update(float deltaSeconds);
	void Render() const;
	void Shutdown();

	Camera m_screenCamera;
	GameState m_gameState = GameState::ATTRACT_MODE;

	// STATE
	void SwitchState(GameState state);
	GameState GetCurrentState();

	// GAME RESTART
	void GameRestart();

public:
	std::vector<Entity*> m_entityList;
	Player* m_player = nullptr;
	Prop* m_cubeOne = nullptr;
	Prop* m_cubeTwo = nullptr;
	Prop* m_sphere = nullptr;
	Prop* m_cylinder = nullptr;
	Clock* m_clock = nullptr;

private:
	// VARIABLES
	Texture* m_testTexture = nullptr;

	float m_screenShakeAmount = 0.0f;
	float m_secondIntoMode = 0.f;

	float m_sizeChange = 0.f;
	float m_timer = 0.f;
	bool m_isFlip = false;

	Timer* m_cubeColorTimer = nullptr;
	bool m_cubeColorSwitch = false;
	Rgba8 m_cubeColor;
	float m_CubeRotationDegree;
	float m_SphereRotationDegree;

	// UPDATE
	void UpdatePlayMode(float deltaSeconds);
	void UpdateAttractMode(float deltaSeconds);
	void UpdateCamera(float deltaSeconds);
	void HandleInput();

	// RENDER
	void RenderPlayMode() const;
	void RenderAttractMode() const;
	void RenderScreenWorld() const;
	void DrawGrid() const;

	// FUNC
	Prop* CreateProp();

};