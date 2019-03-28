#include"LuaParser.h"
#include<assert.h>
#include "lua.hpp"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luaconf.h"
#include "Engine.h"
#include "SmartPointer.h"
#include "Point2D.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Renderer.h"
#include "GLib.h"

namespace Engine {
	LuaParser::LuaParser() {

	}

	SmartPointer<GameObjects> LuaParser::CreateObjectFromLua(const char* i_fileName) {
		lua_State* state = luaL_newstate();
		assert(state);

		luaL_openlibs(state);

		size_t luaFileSize = 0;
		uint8_t* luaFileData = static_cast<uint8_t*>(Renderer::LoadFile(i_fileName, luaFileSize));

		if (luaFileData && luaFileSize) {
			int callResult = 0;

			callResult = luaL_loadbuffer(state, reinterpret_cast<char*>(luaFileData), luaFileSize, nullptr);
			assert(callResult == 0);

			callResult = lua_pcall(state, 0, 0, 0);
			assert(callResult == 0);

			callResult = lua_getglobal(state, "Player");
			assert(callResult == LUA_TTABLE);
			lua_pushstring(state, "Name");

			callResult = lua_gettable(state, -2);
			assert(callResult = LUA_TSTRING);

			const char* playerName = lua_tostring(state, -1);
			lua_pop(state, 1);

			Point2D playerLocation = getPoint2DData(state, "Location");
			Point2D playerVelocity = getPoint2DData(state, "Velocity");
			Point2D drag = getPoint2DData(state, "drag");
			SmartPointer<GameObjects> player = GameObjects::Create(playerLocation, playerName, playerVelocity);
			AddGameObjectToList(player);

			lua_pushstring(state, "Physics");

			callResult = lua_gettable(state, -2);
			assert(callResult == LUA_TTABLE);

			lua_pushnil(state);
			lua_next(state, -2);
			callResult = lua_type(state, -1);

			float mass = 15;
			if (callResult == LUA_TNUMBER) {
				mass = static_cast<float>(lua_tonumber(state, -1));
			}

			lua_pop(state, 2);

			
			PhysicsComponent* physicsComponent = new PhysicsComponent(player, mass, drag);
			AddPhysicsToList(physicsComponent);
			
			lua_pop(state, 1);

			lua_pushstring(state, "Renderer");

			callResult = lua_gettable(state, -2);
			assert(callResult == LUA_TTABLE);

			lua_pushnil(state);
			lua_next(state, -2);

			callResult = lua_type(state, -1);
			assert(callResult == LUA_TSTRING);

			const char* imagePath = lua_tostring(state, -1);

			GLib::Sprites::Sprite* objectImage = Renderer::CreateSprite(imagePath);
			Renderable* objectRenderer = new Renderable(player, objectImage);

			if (objectRenderer) {
				AddRenderableComponentToList(objectRenderer);
			}

			lua_close(state);
			return player;
		} else {
			DEBUG_PRINT("File Not Loaded! Please Check the File Path or the File");
			assert(false);
			return nullptr;
		}
	}

	Point2D LuaParser::getPoint2DData(lua_State* i_state, const char* i_key) {
		lua_pushstring(i_state, i_key);

		int type = lua_gettable(i_state, 1);
		assert(type == LUA_TTABLE);

		lua_pushnil(i_state);
		float values[2];
		int i = 0;

		while (lua_next(i_state, -2) != 0) {
			int value = lua_type(i_state, -1);

			assert(value == LUA_TNUMBER);

			values[i] = (float)lua_tonumber(i_state, -1);
			lua_pop(i_state, 1);
			i++;
			if (i > 2) {
				DEBUG_PRINT("Not a Point2D valriable");
				assert(false);
			}
		}
		lua_pop(i_state, 1);
		return Point2D(values[0], values[1]);
	}
}