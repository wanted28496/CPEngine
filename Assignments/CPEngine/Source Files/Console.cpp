
#include<assert.h>
#include<stdarg.h>
#include<stdio.h>
#include<windows.h>
namespace Engine {
	void writeline(const char * i_message, ...)
	{
		assert( i_message );
	
	const size_t lenTemp = 256;
	char strTemp[lenTemp] = "LOG: ";

	strcat_s(strTemp, i_message);
	strcat_s(strTemp, "\n");

	const size_t lenOutput = lenTemp + 32;

	char strOutput[lenOutput];

	// define a variable argument list variable 
	va_list args;
	
	// initialize it. second parameter is variable immediately
	// preceeding variable arguments
	va_start(args, i_message);

	// (safely) print our formatted string to a char buffer
	vsprintf_s(strOutput, lenOutput, strTemp, args);

	va_end(args);

	OutputDebugStringA(strOutput);
	}
}