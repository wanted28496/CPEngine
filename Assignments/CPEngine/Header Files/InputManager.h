#pragma once
namespace Engine {

	enum KEYCHAR {
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',
		NUM_0 = '0',
		NUM_1 = '1',
		NUM_2 = '2',
		NUM_3 = '3',
		NUM_4 = '4',
		NUM_5 = '5',
		NUM_6 = '6',
		NUM_7 = '7',
		NUM_8 = '8',
		NUM_9 = '9'
	};

	namespace InputManager {

		static bool isDown;
		static int keyId;
		void Init();
		void KeyCallback(unsigned int, bool);
		int GetKeyDown();
		int GetKeyUp();
	};
}