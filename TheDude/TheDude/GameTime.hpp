#pragma once
#include <chrono>
#include <string>
#define cClock std::chrono::time_point<std::chrono::steady_clock>


class GameTime
{
private:
	float m_refreshRate;
	cClock m_time;
	cClock m_timer;
	int m_updates;
	int m_fpsCounter;
	float m_frequency;
	float m_unprocessed;

public:
	GameTime(float refreshRate = 60.0f);
	~GameTime();
	void Init();
	float getRefreshRate() const;
	void setRefreshRate(float refreshRate);

	void UpdateGameTime();
	bool AllowedToUpdate();
	bool HasTimePassed(float time);
	std::string GetAndResetStats();
};