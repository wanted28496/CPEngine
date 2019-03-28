#include"Console.h"
#include"GameObject.h"
#include"Point2D.h"
#include"Engine.h"
#include"Renderer.h"
#include"PhysicsComponent.h"
#include"Timer.h"
#include"InputManager.h"
#include "GLib.h"
#include"LuaParser.h"
#include "lua.hpp"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luaconf.h"



#define PLAYERFILEPATH "data\\player.lua"

namespace Doors {
	bool Start() {
		DEBUG_PRINT("-----GAME STARTS------");
		Engine::LuaParser* parser = new Engine::LuaParser();
		SmartPointer<GameObjects> player = parser->CreateObjectFromLua(PLAYERFILEPATH);
		delete parser;
		return true;
	}

	void Update() {

	}

	bool OnExit() {
		DEBUG_PRINT("-----EXITING GAME------");
		return true;
	}
}



/*
struct Counters
{
	long		m_strongCount;
	long		m_weakCount;

	Counters(long i_strongCount = 0, long i_weakCount = 0) :
		m_strongCount(i_strongCount),
		m_weakCount(i_weakCount)
	{

	}
};

template<typename T>
class StrongPointer
{
public:
	StrongPointer(T * i_ptr = NULL);
	~StrongPointer();

	StrongPointer(const StrongPointer & i_other);
	StrongPointer &operator=(const StrongPointer & i_other);

	T * operator->();
	T & operator*();

	operator bool() const;

	bool operator==(const StrongPointer & i_other) const;
};

template<typename T>
class WeakPointer
{
public:
	WeakPointer(T * i_ptr = NULL);

	WeakPointer(const WeakPointer & i_other);
	WeakPointer &operator=(const WeakPointer & i_other);

	StrongPointer<T> Acquire() const;

	bool IsValid() const { return m_pObject != nullptr; }
	operator bool() const { return IsValid();  }

	T * operator->();
	T & operator*();


private:
	T *			m_pObject;
	Counters *	m_pCounters;
};

class UniquePointer
{
public:
	UniquePointer(T * i_ptr = NULL);

	UniquePointer(const UniquePointer & i_other);
	UniquePointer &operator=(const UniquePointer & i_other);

	bool IsValid() const { return m_pObject != nullptr; }
	operator bool() const { return IsValid(); }

	T * operator->();
	T & operator*();

private:
	T *			m_pObject;
};
class Vector3
{
}

class GameObject
{

public:
	Vector3 GetPosition();
};

struct Renderable
{
	WeakPointer<GameObject> m_pObject;
	GLib::Sprite *			m_pSprite;
};

void Draw( Renderable & i_Renderable)
{
	StrongPointer<GameObject> MyObj = i_Renderable.m_pObject.Acquire();

	if (MyObj)
	{
		// if StrongPointer is valid draw it
		GLib::Sprites::RenderSprite(*i_Renderable.m_pSprite, MyObj->GetPosition(), 0.0f);
	}
	else
	{
		// Need to destroy this Renderable since the GameObject has been released
	}
}

void Test()
{
	// Ptr1 is the owner of the new GameObject
	UniquePointer<GameObject> Ptr1(new GameObject("Joe"));

	// Now Ptr2 is the owner and Ptr1 points to NULL
	UniquePointer<GameObject> Ptr2 = Ptr1;

	// Now Ptr1 is the owner and Ptr2 points to NULL
	Ptr1 = Ptr2;
}
*/
