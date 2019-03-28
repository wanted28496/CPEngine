#pragma once
#ifndef __CONSOLE_PRINT_H
#define __CONSOLE_PRINT_H



namespace Engine {
	void writeline(const char* i_message, ...);


	#if defined(_DEBUG) && !defined(DISABLE_DEBUG_PRINT)
		#define DEBUG_PRINT(fmt,...) Engine::writeline(fmt,__VA_ARGS__)
	#else
		#define DEBUG_PRINT(fmt,...) void(0)
	#endif // 

}
#endif // !__CONSOLE_PRINT_H