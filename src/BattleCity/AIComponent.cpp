#include "AIComponent.h"
#include "GameObjects/Panzer.h"

AIComponent::AIComponent(Panzer* pParentPanzer) : m_pParentPanzer(pParentPanzer)
{
}

void AIComponent::update(const double delta)
{
	m_pParentPanzer->fire();
}
