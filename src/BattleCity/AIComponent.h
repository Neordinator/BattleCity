#pragma once

class Panzer;

class AIComponent
{
public:
	AIComponent(Panzer*);

	void update(const double);

private:
	Panzer* m_pParentPanzer;
};