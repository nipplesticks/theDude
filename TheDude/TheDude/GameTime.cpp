#include "GameTime.hpp"
#define CastNano std::chrono::duration_cast<nanoseconds>
#define CastMilli std::chrono::duration_cast<milliseconds>


using namespace std::chrono;

GameTime::GameTime(float refreshRate)
{
	m_refreshRate = refreshRate;
}

GameTime::~GameTime()
{
}

void GameTime::Init()
{
	m_time = steady_clock::now();
	m_timer = steady_clock::now();
	m_updates = 0;
	m_fpsCounter = 0;
	m_frequency = 1000000000.0f / m_refreshRate;
	m_unprocessed = 0.0f;
}

float GameTime::getRefreshRate() const
{
	return m_refreshRate;
}

void GameTime::setRefreshRate(float refreshRate)
{
	m_refreshRate = refreshRate;
	m_frequency = 1000000000.0f / m_refreshRate;
}

void GameTime::UpdateGameTime()
{
	cClock currentTime = steady_clock::now();
	long long dt = CastNano(currentTime - m_time).count();
	m_time = currentTime;
	m_unprocessed += dt / m_frequency;
	m_fpsCounter++;
}

bool GameTime::AllowedToUpdate()
{
	bool value = false;

	if (m_unprocessed > 1.0f)
	{
		value = true;
		m_updates++;
		m_unprocessed -= 1.0f;
	}

	return value;
}

bool GameTime::HasTimePassed(float time)
{
	bool value = false;

	if (CastMilli(steady_clock::now() - m_timer).count() > time)
	{
		value = true;
		m_timer = steady_clock::now();
	}

	return value;
}

std::string GameTime::GetAndResetStats()
{
	std::string stats = " | Fps: ";
	stats += std::to_string(m_fpsCounter);
	stats += " | Tick: ";
	stats += std::to_string(m_updates);
	m_updates = 0;
	m_fpsCounter = 0;
	return stats;
}
