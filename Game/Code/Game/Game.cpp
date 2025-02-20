#include "Game/Game.hpp"
#include "Game/Player.hpp"
#include "Game/Prop.hpp"
#include "Game/Entity.hpp"

Game::Game()
{


}
//..............................
Game::~Game()
{

}
//..............................
void Game::Startup()
{
	m_player = new Player(this);
	m_player->m_position = Vec3(0.f, 0.f, 0.f);
	m_player->m_orientationDegrees = EulerAngles(0.f, 0.f, 0.f);
	m_entityList.push_back((Entity*)m_player);
	m_screenCamera.SetOrthographicView(Vec2(0, 0), Vec2(g_gameConfigBlackboard.GetValue("screenSizeX", 1600.f), g_gameConfigBlackboard.GetValue("screenSizeY", 800.f)));
	m_clock = new Clock(*Clock::s_theSystemClock);

	SwitchState(GameState::ATTRACT_MODE);
	m_cubeColorTimer = new Timer(2.f, m_clock);
	m_cubeColorTimer->Start();
	m_testTexture = g_theRenderer->CreateOrGetTextureFromFile("Data/Images/TestUV.png");

	m_cubeOne = CreateProp();
	m_cubeTwo = CreateProp();
	m_sphere = CreateProp();
	m_cylinder = CreateProp();


	Vec3 BLNear = Vec3(-0.5f, 0.5f, -0.5f);
	Vec3 BRNear = Vec3(-0.5f, -0.5f, -0.5f);
	Vec3 TLNear = Vec3(-0.5f, 0.5f, 0.5f);
	Vec3 TRNear = Vec3(-0.5f, -0.5f, 0.5f);

	Vec3 BLFar = Vec3(0.5f, 0.5f, -0.5f);
	Vec3 BRFar = Vec3(0.5f, -0.5f, -0.5f);
	Vec3 TLFar = Vec3(0.5f, 0.5f, 0.5f);
	Vec3 TRFar = Vec3(0.5f, -0.5f, 0.5f);

	AddVertsForQuad3D(m_cubeOne->m_vertexes, BRFar, BLFar, TRFar, TLFar, Rgba8::COLOR_RED); // X
	AddVertsForQuad3D(m_cubeOne->m_vertexes, BLNear, BRNear, TLNear, TRNear, Rgba8::COLOR_CYAN); // -X
	AddVertsForQuad3D(m_cubeOne->m_vertexes, BRNear, BRFar, TRNear, TRFar, Rgba8::COLOR_GREEN); // Y
	AddVertsForQuad3D(m_cubeOne->m_vertexes, BLFar, BLNear, TLFar, TLNear, Rgba8::COLOR_MAGNETA); // -Y
	AddVertsForQuad3D(m_cubeOne->m_vertexes, TLNear, TRNear, TLFar, TRFar, Rgba8::COLOR_BLUE); // Z
	AddVertsForQuad3D(m_cubeOne->m_vertexes, BRNear, BLNear, BRFar, BLFar, Rgba8::COLOR_YELLOW); // -Z

	AddVertsForQuad3D(m_cubeTwo->m_vertexes, BRFar, BLFar, TRFar, TLFar, Rgba8::COLOR_RED); // X
	AddVertsForQuad3D(m_cubeTwo->m_vertexes, BLNear, BRNear, TLNear, TRNear, Rgba8::COLOR_CYAN); // -X
	AddVertsForQuad3D(m_cubeTwo->m_vertexes, BRNear, BRFar, TRNear, TRFar, Rgba8::COLOR_GREEN); // Y
	AddVertsForQuad3D(m_cubeTwo->m_vertexes, BLFar, BLNear, TLFar, TLNear, Rgba8::COLOR_MAGNETA); // -Y
	AddVertsForQuad3D(m_cubeTwo->m_vertexes, TLNear, TRNear, TLFar, TRFar, Rgba8::COLOR_BLUE); // Z
	AddVertsForQuad3D(m_cubeTwo->m_vertexes, BRNear, BLNear, BRFar, BLFar, Rgba8::COLOR_YELLOW); // -Z

	AddVertsForSphere(m_sphere->m_vertexes, Vec3(0, 0, 0), 1.f);

	AddVertsForCylinder3D(m_cylinder->m_vertexes, Vec3(1, 4, 7), Vec3(8, 2, 15), 2);

	m_cubeOne->m_position = Vec3(-3.f, -3.f, 0);
	m_cubeOne->m_angularVelocity.m_pitchDegrees = 30.f;
	m_cubeOne->m_angularVelocity.m_yawDegrees = 30.f;
	m_cubeTwo->m_position = Vec3(3.f, 3.f, 0);
	m_cubeTwo->m_color = m_cubeColor;
	m_sphere->m_position = Vec3(10, -5, 1);
	m_sphere->m_texture = m_testTexture;
	m_sphere->m_angularVelocity.m_yawDegrees = 45.f;
	m_cylinder->m_position = Vec3(3, 3, 5);
	m_cylinder->m_texture = m_testTexture;

	DebugAddWorldBasis(Mat44(), -1);

	Mat44 textXTransform;
	textXTransform.AppendTranslation3D(Vec3(1.3f, 0.f, 0.2f));
	textXTransform.AppendZRotation(90);
	DebugAddWorldText("X - FORWARD", textXTransform, 0.2f, Vec2(0.5f, 0.5f), -1, Rgba8::COLOR_RED);
	Mat44 textYTransform;
	textYTransform.AppendTranslation3D(Vec3(0.f, 1.0f, 0.2f));
	DebugAddWorldText("Y - LEFT", textYTransform, 0.2f, Vec2(0.5f, 0.5f), -1, Rgba8::COLOR_GREEN);
	Mat44 textZTransform;
	textZTransform.AppendTranslation3D(Vec3(-0.4f, 0.0f, 1.0f));
	textZTransform.AppendYRotation(90);
	textZTransform.AppendZRotation(90);
	DebugAddWorldText("Z - UP", textZTransform, 0.2f, Vec2(0.5f, 0.5f), -1, Rgba8::COLOR_BLUE);
}
//..............................
void Game::Shutdown()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------
// UPDATE

void Game::Update(float deltaSeconds)
{
	m_secondIntoMode += deltaSeconds;

	//UpdateCamera();

	if (m_gameState == GameState::PLAY_MODE)
	{
		UpdatePlayMode(deltaSeconds);
	}
	if (m_gameState == GameState::ATTRACT_MODE)
	{
		UpdateAttractMode(deltaSeconds);
	}


}
//..............................
void Game::UpdatePlayMode(float deltaSeconds)
{

	for (size_t i = 0; i < m_entityList.size(); i++)
	{
		m_entityList[i]->Update(deltaSeconds);
	}
	HandleInput();
	if (m_cubeColorTimer->DecrementPeriodIfElapsed())
	{
		m_cubeColorSwitch = !m_cubeColorSwitch;
	}
	if (m_cubeColorSwitch)
	{
		m_cubeColor = Interpolate(Rgba8::COLOR_WHITE, Rgba8::COLOR_DARK_GRAY, m_cubeColorTimer->GetElapsedFraction());
	}
	else
	{
		m_cubeColor = Interpolate(Rgba8::COLOR_DARK_GRAY, Rgba8::COLOR_WHITE, m_cubeColorTimer->GetElapsedFraction());
	}

	DebugAddScreenText(Stringf("Time: %.1f, FPS: %.1f, Scale: %.1f", Clock::s_theSystemClock->GetTotalSeconds(), 1.f / Clock::s_theSystemClock->GetDeltaSeconds(), Clock::s_theSystemClock->GetTimeScale()),
		Vec2(1050.f, 780.f), 15.f);
	DebugAddMessage(Stringf("Player Position: %.1f, %.1f, %.1f", m_player->m_position.x, m_player->m_position.y, m_player->m_position.z), 0);
}
//..............................
void Game::UpdateAttractMode(float deltaSeconds)
{
	if (g_theInput->WasKeyJustPressed(KEYCODE_SPACE))
	{
		SwitchState(GameState::PLAY_MODE);
	}
	m_timer += deltaSeconds;

	if (m_timer > 4.f)
	{
		m_isFlip = !m_isFlip;
		m_timer = 0.f;
	}

	m_sizeChange = (m_isFlip) ? Interpolate(0.f, 20.f, m_timer) : -Interpolate(-20.f, 0.f, m_timer);

}
//..............................
void Game::UpdateCamera(float deltaSeconds)
{
	UNUSED(deltaSeconds);
	float shakeX = g_theRNG->RollRandomFloatInRange(-m_screenShakeAmount, m_screenShakeAmount);
	float shakeY = g_theRNG->RollRandomFloatInRange(-m_screenShakeAmount, m_screenShakeAmount);
	m_player->GetCamera()->Translate2D(Vec2(shakeX, shakeY));
	m_screenShakeAmount -= SHAKE_REDUCTION_PER_SEC * Clock::s_theSystemClock->GetDeltaSeconds();
	m_screenShakeAmount = Clamp(m_screenShakeAmount, 0.f, MAX_SHAKE);
}

//----------------------------------------------------------------------------------------------------------------------------------------
// RENDER 

void Game::Render() const
{
	if (m_gameState == GameState::PLAY_MODE)
	{
		RenderPlayMode();
		DebugRenderWorld(*m_player->GetCamera());
		DebugRenderScreen(m_screenCamera);
	}
	if (m_gameState == GameState::ATTRACT_MODE)
	{
		RenderAttractMode();
	}
	RenderScreenWorld();
}
//..............................

void Game::RenderPlayMode() const
{
	g_theRenderer->ClearScreen(Rgba8(100, 100, 100, 255));
	g_theRenderer->BeginCamera(*m_player->GetCamera());
	g_theRenderer->SetRasterizerMode(RasterizerMode::SOLID_CULL_BACK);
	g_theRenderer->SetDepthStencilMode(DepthMode::ENABLED);
	for (auto i : m_entityList)
	{
		i->Render();
	}

	DrawGrid();

	g_theRenderer->EndCamera(*m_player->GetCamera());

	g_theRenderer->BeginCamera(m_screenCamera);

	g_theRenderer->EndCamera(m_screenCamera);
}
//..............................
void Game::RenderAttractMode() const
{
	g_theRenderer->ClearScreen(Rgba8(255, 0, 255, 255));
	g_theRenderer->BeginCamera(m_screenCamera);
	g_theRenderer->SetDepthStencilMode(DepthMode::DISABLED);
	g_theRenderer->SetBlendMode(BlendMode::ALPHA);
	g_theRenderer->SetRasterizerMode(RasterizerMode::SOLID_CULL_NONE);
	g_theRenderer->SetSamplerMode(SampleMode::POINT_CLAMP);

	std::vector<Vertex_PCU> drawVertexList;
	drawVertexList.reserve(100);

	AddVertsForAABB2D(drawVertexList, AABB2(400.f + m_sizeChange, 200.f + m_sizeChange, 1200.f + m_sizeChange, 600.f + m_sizeChange), Rgba8::COLOR_GREEN);

	g_theRenderer->SetModelConstants();
	g_theRenderer->BindTexture(nullptr);
	g_theRenderer->DrawVertexArray((int)drawVertexList.size(), drawVertexList.data());
	g_theRenderer->EndCamera(m_screenCamera);
}
//..............................
void Game::RenderScreenWorld() const
{
	g_theRenderer->BeginCamera(m_screenCamera);
	g_theRenderer->SetDepthStencilMode(DepthMode::DISABLED);
	g_theRenderer->SetBlendMode(BlendMode::ALPHA);
	g_theRenderer->SetRasterizerMode(RasterizerMode::SOLID_CULL_NONE);
	g_theRenderer->SetSamplerMode(SampleMode::POINT_CLAMP);

	AABB2 screenBound = AABB2(m_screenCamera.GetOrthographicBottomLeft(), m_screenCamera.GetOrthographicTopRight());

	std::vector<Vertex_PCU> UIVerts;
	UIVerts.reserve(6);

	if (m_clock->IsPaused())
	{
		AddVertsForAABB2D(UIVerts, screenBound, Rgba8::DARK);
	}

	g_theRenderer->SetModelConstants();
	g_theRenderer->BindTexture(nullptr);
	g_theRenderer->DrawVertexArray((int)UIVerts.size(), UIVerts.data());

	g_theDevConsole->Render(screenBound, g_theRenderer);
}

void Game::DrawGrid() const
{
	// Drawing Grid

	g_theRenderer->BindTexture(nullptr);
	g_theRenderer->SetRasterizerMode(RasterizerMode::SOLID_CULL_BACK);

	std::vector<Vertex_PCU> gridVertexes;

	float smallSize = 0.02f;
	float medSize = 0.03f;
	float largeSize = 0.06f;

	for (int x = -50; x <= 50; x++)
	{
		AABB3 cube;
		Rgba8 color;

		if (x % 5 == 0)
		{
			cube = AABB3(-medSize + x, -50.f, -medSize, medSize + x, 50.f, medSize);
			color = Rgba8(0, 180, 0);
		}
		else
		{
			cube = AABB3(-smallSize + x, -50.f, -smallSize, smallSize + x, 50.f, smallSize);
			color = Rgba8::COLOR_GRAY;
		}
		if (x == 0)
		{
			cube = AABB3(-largeSize + x, -50.f, -largeSize, largeSize + x, 50.f, largeSize);
			color = Rgba8::COLOR_GREEN;
		}
		AddVertsForAABB3D(gridVertexes, cube, color);
	}
	for (int y = -50; y <= 50; y++)
	{
		AABB3 cube;
		Rgba8 color;

		if (y % 5 == 0)
		{
			cube = AABB3(-50.f, -medSize + y, -medSize, 50.f, medSize + y, medSize);
			color = Rgba8(180, 0, 0);
		}
		else
		{
			cube = AABB3(-50.f, -smallSize + y, -smallSize, 50.f, smallSize + y, smallSize);
			color = Rgba8::COLOR_GRAY;
		}
		if (y == 0)
		{
			cube = AABB3(-50.f, -largeSize + y, -largeSize, 50.f, largeSize + y, largeSize);
			color = Rgba8::COLOR_RED;
		}
		AddVertsForAABB3D(gridVertexes, cube, color);
	}
	g_theRenderer->SetModelConstants();
	g_theRenderer->DrawVertexArray((int)gridVertexes.size(), gridVertexes.data());
}

Prop* Game::CreateProp()
{
	Prop* newProp = new Prop(this);
	m_entityList.push_back((Entity*)newProp);
	return newProp;
}

//----------------------------------------------------------------------------------------------------------------------------------------
// GAME RESTART

void Game::GameRestart()
{
	Shutdown();
	Startup();
	SwitchState(GameState::PLAY_MODE);
}

//----------------------------------------------------------------------------------------------------------------------------------------
// HANDLE INPUT

void Game::HandleInput()
{

}

void Game::SwitchState(GameState state)
{
	m_gameState = state;
}

GameState Game::GetCurrentState()
{
	return m_gameState;
}
