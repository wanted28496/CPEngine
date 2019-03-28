#pragma once
namespace Engine {

#define DESIRED_FPS 60.0
#define DESIRED_FPS_MS (1000.0 / DESIRED_FPS)
#define MAX_FPS (3 * DESIRED_FPS_MS)

	class Timer {
	public:
		static float m_lastFrame;
		static float FrameTime();
	};
}