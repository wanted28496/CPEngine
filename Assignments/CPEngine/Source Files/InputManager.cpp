#include"InputManager.h"
#include"Console.h"
#include"GLib.h"

namespace Engine {
	namespace InputManager {

		void Init() {
			GLib::SetKeyStateChangeCallback(KeyCallback);
		}

		void KeyCallback(unsigned int i_keyID, bool i_isDown) {
			keyId = i_keyID;
			isDown = i_isDown;
			DEBUG_PRINT("Key %d is pressed", i_keyID);
		}

		int GetKeyDown() {
			return keyId;
		}

		int GetKeyUp() {
			return keyId;
		}

	}
}