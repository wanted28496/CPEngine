#pragma once
#include "SmartPointer.h"
#include "GameObject.h"
#include "Point2D.h"
struct lua_State;

namespace Engine {
	class LuaParser {
	public:
		LuaParser();

		SmartPointer<GameObjects> CreateObjectFromLua(const char*);
	private:
		Point2D getPoint2DData(lua_State*, const char*);
	};
}