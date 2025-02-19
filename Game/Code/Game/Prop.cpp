#include "Prop.hpp"

Prop::Prop(Game* owner)
	:Entity(owner)
{

}

Prop::~Prop()
{
}

void Prop::Update(float deltaSeconds)
{
	m_orientationDegrees.m_yawDegrees += m_angularVelocity.m_yawDegrees * deltaSeconds;
	m_orientationDegrees.m_pitchDegrees += m_angularVelocity.m_pitchDegrees * deltaSeconds;
	m_orientationDegrees.m_rollDegrees += m_angularVelocity.m_rollDegrees * deltaSeconds;
}

void Prop::Render() const
{
	g_theRenderer->SetBlendMode(BlendMode::OPAQUE);
	g_theRenderer->BindTexture(m_texture);
	g_theRenderer->SetModelConstants(GetModeMatrix(), m_color);
	g_theRenderer->DrawVertexArray((int)m_vertexes.size(), m_vertexes.data());
}
