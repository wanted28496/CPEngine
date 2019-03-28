#pragma once
#include "GLib.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include"PhysicsComponent.h"
#include"Renderer.h"

class GameObjects;
class Point2D;

namespace Engine {


	bool __Init__();

	void __Run__();

	bool __TerminateProgram__();

	void AddPhysicsToList(PhysicsComponent*);

	void AddRenderableComponentToList(Renderable*);

	void AddGameObjectToList(const SmartPointer<GameObjects>);

	void CreatePlayer(const Point2D, const char*, const Point2D);

	
	//void CreatePhysicsComponent(GameObjects *, float, Point2D);

	//void CreateRenderableComponent(GameObjects *, GLib::Sprites::Sprite *);

	//GameObjects* CreateGameObject(Point2D);

	namespace Physics {
		void Run(float);
	}

	namespace Renderer {
		void DrawGraphics();
	}

	namespace Input {
		void CheckForInput(float);
	}
}
