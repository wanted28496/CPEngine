#include"Timer.h"
#include<Windows.h>
namespace Engine {

	typedef LARGE_INTEGER TIMER_METRIC;
	static TIMER_METRIC m_currentFrameTime;

	float Timer::m_lastFrame = 0.0f;

	float Timer::FrameTime() {
		TIMER_METRIC frameEndTime;
		TIMER_METRIC microSeconds;
		TIMER_METRIC frequency;

		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&frameEndTime);

		if (m_currentFrameTime.QuadPart == NULL) {
			m_currentFrameTime = frameEndTime;
		}

		microSeconds.QuadPart = frameEndTime.QuadPart - m_currentFrameTime.QuadPart;
		microSeconds.QuadPart *= 100000;
		microSeconds.QuadPart /= frequency.QuadPart;

		m_currentFrameTime = frameEndTime;

		m_lastFrame = (float)microSeconds.QuadPart;
		if (m_lastFrame > MAX_FPS) {
			return MAX_FPS;
		}
		return m_lastFrame;
	}
}