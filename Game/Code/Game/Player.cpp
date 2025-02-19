#include "Player.hpp"
#include "Game/GameCommon.hpp"

Player::Player(Game* owner)
	:Entity(owner)
{
	m_playerCamera = new Camera();
	m_playerCamera->SetPerspectiveView(Window::GetMainWindowInstance()->GetAspect(), 60.f, 0.1f, 100.f);
	m_playerCamera->SetRenderBasis(Vec3(0.f, 0.f, 1.f), Vec3(-1.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
}

Player::~Player()
{
}

void Player::Update(float deltaSeconds)
{
	HandleInput(deltaSeconds);
	Movement(deltaSeconds);
	m_playerCamera->SetTransform(m_position, m_orientationDegrees);
}

void Player::Render() const
{
}

Camera* Player::GetCamera()
{
	return m_playerCamera;
}

void Player::HandleInput(float deltaSeconds)
{
	Vec3 forwardDir = GetModeMatrix().GetIBasis3D().GetNormalized();
	Vec3 rightDir = GetModeMatrix().GetJBasis3D().GetNormalized();
	Vec3 upDir = GetModeMatrix().GetKBasis3D().GetNormalized();

	m_velocity = Vec3::ZERO;

	// CONTROLLER
	if (g_theInput->GetController(0).GetLeftStick().GetMagnitude() > 0)
	{
		float leftStickPosX = g_theInput->GetController(0).GetLeftStick().GetPosition().x;
		float leftStickPosY = g_theInput->GetController(0).GetLeftStick().GetPosition().y;
		m_velocity += forwardDir * leftStickPosY * m_movingSpeed;
		m_velocity -= rightDir * leftStickPosX * m_movingSpeed;
	}
	if (g_theInput->GetController(0).GetRightStick().GetMagnitude() > 0)
	{
		float rightStickPosX = g_theInput->GetController(0).GetRightStick().GetPosition().x;
		float rightStickPosY = g_theInput->GetController(0).GetRightStick().GetPosition().y;
		m_orientationDegrees.m_pitchDegrees -= rightStickPosY * m_rotatingSpeed;
		m_orientationDegrees.m_yawDegrees -= rightStickPosX * m_rotatingSpeed;
	}
	if (g_theInput->GetController(0).IsButtonDown(XBOX_BUTTON_START))
	{
		m_position = Vec3::ZERO;
		m_orientationDegrees = EulerAngles();
	}
	if (g_theInput->GetController(0).IsButtonDown(XBOX_BUTTON_SHOULDER_LEFT))
	{
		m_velocity += Vec3(0, 0, m_movingSpeed);
	}
	if (g_theInput->GetController(0).IsButtonDown(XBOX_BUTTON_SHOULDER_RIGHT))
	{
		m_velocity -= Vec3(0, 0, m_movingSpeed);
	}
	if (m_orientationDegrees.m_rollDegrees >= -45.f)
	{
		m_orientationDegrees.m_rollDegrees -= g_theInput->GetController(0).GetLeftTrigger() * m_rotatingSpeed * deltaSeconds;
	}
	if (m_orientationDegrees.m_rollDegrees <= 45.f)
	{
		m_orientationDegrees.m_rollDegrees += g_theInput->GetController(0).GetRightTrigger() * m_rotatingSpeed * deltaSeconds;
	}
	if (g_theInput->GetController(0).IsButtonDown(XBOX_BUTTON_A))
	{
		m_velocity *= 10.f;
	}

	// MKB
	m_orientationDegrees.m_pitchDegrees += g_theInput->GetCursorClientDelta().y  * 0.075f;
	m_orientationDegrees.m_yawDegrees -= g_theInput->GetCursorClientDelta().x  * 0.075f;

	if (g_theInput->IsKeyDown('H'))
	{
		m_position = Vec3::ZERO;
		m_orientationDegrees = EulerAngles();
	}

	if (g_theInput->IsKeyDown('W'))
	{
		m_velocity += forwardDir * m_movingSpeed;
	}
	if (g_theInput->IsKeyDown('S'))
	{
		m_velocity -= forwardDir * m_movingSpeed;
	}
	if (g_theInput->IsKeyDown('A'))
	{
		m_velocity += rightDir * m_movingSpeed;
	}
	if (g_theInput->IsKeyDown('D'))
	{
		m_velocity -= rightDir * m_movingSpeed;
	}
	if (g_theInput->IsKeyDown('Z'))
	{
		m_velocity += Vec3(0, 0, m_movingSpeed);
	}
	if (g_theInput->IsKeyDown('C'))
	{
		m_velocity -= Vec3(0, 0, m_movingSpeed);
	}
	if (g_theInput->IsKeyDown(KEYCODE_SHIFT))
	{
		m_velocity *= 10.f;
	}
	// 	if (g_theInput->IsKeyDown(KEYCODE_UPARROW))
	// 	{
	// 		m_orientationDegrees.m_pitchDegrees -= m_rotatingSpeed * deltaSeconds;
	// 	}
	// 	if (g_theInput->IsKeyDown(KEYCODE_DOWNARROW))
	// 	{
	// 		m_orientationDegrees.m_pitchDegrees += m_rotatingSpeed * deltaSeconds;
	// 	}
	// 	if (g_theInput->IsKeyDown(KEYCODE_LEFTARROW))
	// 	{
	// 		m_orientationDegrees.m_yawDegrees += m_rotatingSpeed * deltaSeconds;
	// 	}
	// 	if (g_theInput->IsKeyDown(KEYCODE_RIGHTARROW))
	// 	{
	// 		m_orientationDegrees.m_yawDegrees -= m_rotatingSpeed * deltaSeconds;
	// 	}

	if (g_theInput->IsKeyDown('Q'))
	{
		if (m_orientationDegrees.m_rollDegrees >= -45.f)
		{
			m_orientationDegrees.m_rollDegrees -= m_rotatingSpeed * deltaSeconds;
		}

	}
	if (g_theInput->IsKeyDown('E'))
	{
		if (m_orientationDegrees.m_rollDegrees <= 45.f)
		{
			m_orientationDegrees.m_rollDegrees += m_rotatingSpeed * deltaSeconds;
		}
	}
	if (g_theInput->WasKeyJustPressed(49))
	{
		DebugAddWorldLine(m_position, m_position + forwardDir * 20.f, 0.1f, 10.f, Rgba8::COLOR_YELLOW, Rgba8::COLOR_YELLOW, DebugRenderMode::XRAY);
	}
	if (g_theInput->IsKeyDown(50))
	{
		DebugAddWorldPoint(Vec3(m_position.x, m_position.y, 0.f), 0.5f, 60.f, Rgba8(150, 75, 0), Rgba8(150, 75, 0));
	}
	if (g_theInput->WasKeyJustPressed(51))
	{
		DebugAddWorldWireSphere(m_position + forwardDir * 2.f, 1.f, 5.f, Rgba8::COLOR_GREEN, Rgba8::COLOR_RED);
	}
	if (g_theInput->WasKeyJustPressed(52))
	{
		DebugAddWorldBasis(GetModeMatrix(), 20.f);
	}
	if (g_theInput->WasKeyJustPressed(53))
	{
		DebugAddWorldBillboardText(Stringf("Position: %.1f, %.1f, %.1f\nOrientation : %.1f, %.1f, %.1f", m_position.x, m_position.y, m_position.z, m_orientationDegrees.m_yawDegrees, m_orientationDegrees.m_pitchDegrees, m_orientationDegrees.m_rollDegrees),
			m_position + forwardDir * 2.f, 0.3f, Vec2(0.5f, 0.5f), 10.f, Rgba8::COLOR_WHITE, Rgba8::COLOR_RED);
	}
	if (g_theInput->WasKeyJustPressed(54))
	{
		DebugAddWorldWireCylinder(m_position, m_position + Vec3(0.f, 0.f, 2.f), 1.f, 10.f, Rgba8::COLOR_WHITE, Rgba8::COLOR_RED);
	}
	if (g_theInput->WasKeyJustPressed(55))
	{
		EulerAngles eA = m_playerCamera->GetOrientation();
		DebugAddMessage(Stringf("Camera Orientation: %.1f, %.1f, %.1f", eA.m_yawDegrees, eA.m_pitchDegrees, eA.m_rollDegrees), 5);
	}
}

void Player::Movement(float deltaSeconds)
{
	m_orientationDegrees.m_pitchDegrees = Clamp(m_orientationDegrees.m_pitchDegrees, -85.f, 85.f);
	m_position += m_velocity * deltaSeconds;
}
