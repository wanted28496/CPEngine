All the class are forward declared.

Use of _BitScanReverse64 and _BitScanReverse at 
"Assignments\CPEngine\Source Files\BitArray.cpp", lines 185 and 191 

Added Gaurdband at
"Assignments\CPEngine\Source Files\FSA.cpp", line 43 
"Assignments\CPEngine\Source Files\HeapManger.cpp" line 110

Created a Memory Instance file which stores the instances of HeapManager and Fixed size Allocator
"Assignments\CPEngine\Source Files\MemoryInstance.cpp"
"Assignments\CPEngine\Header Files\MemoryInstance.h"

Created a Player Instance file which stores the instances of the player
"Assignments\CPEngine\Source Files\PlayerInstance.cpp"
"Assignments\CPEngine\Header Files\PlayerInstance.h"

Created a CharacterName class for dealing with name of monster and player
"Assignments\CPEngine\Source Files\CharacterName.cpp"
"Assignments\CPEngine\Header Files\CharacterName.h"

Created a namespace Conversion in StringToNum.cpp for converting string to number and visa versa (not handling all test case, only normal unsigned int)
"Assignments\CPEngine\Source Files\StringToNum.cpp"
"Assignments\CPEngine\Header Files\StringToNum.h"

Run:
Made changes so that on running the project it will run the Unit_Test

Problems:
There is one problem in Release 64 build only which gives memory access violation error, which I dont know why, I tried printing at all the locations possible which can give information which can be found at hash: 06fc7127,

There is also a minor problem that happens sometime while initailizing FSA which crashes the program, but when you run it again the program runs perfectly.