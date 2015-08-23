#pragma once
#include <SDL/SDL.h>
#include <iostream>
class FPSLimiter
{
public:
	FPSLimiter();
	~FPSLimiter();

	void Start();
	float End();

	void CalculateFPS();

private:
	float m_fps;
	float m_maxFPS;
	float m_frameTime;
	Uint32 m_startTicks;
};

