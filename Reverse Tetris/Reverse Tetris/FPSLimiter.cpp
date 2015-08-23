#include "FPSLimiter.h"



FPSLimiter::FPSLimiter()
{
	m_maxFPS = 60.0f;
}

FPSLimiter::~FPSLimiter()
{
}

void FPSLimiter::Start()
{
	m_startTicks = SDL_GetTicks();
}

float FPSLimiter::End()
{
	CalculateFPS();

	float frameTicks = SDL_GetTicks() - m_startTicks;
	// Limit the FPS to the MAXFPS
	if (1000.0f / m_maxFPS > frameTicks)
	{
		SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
	}

	return m_fps;
}

void FPSLimiter::CalculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;
	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	// Calculate FPS
	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}
}
