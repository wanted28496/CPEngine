#include "Engine.h"
#include "GameObject.h"
#include "Point2D.h"
#include "InputManager.h"
#include "Renderer.h"
#include "PhysicsComponent.h"
#include "Timer.h"
#include "Console.h"
#include <vector>
#include <assert.h>

namespace Engine {

	static std::vector<PhysicsComponent*> PHYSICSCOMPONENTS;
	static std::vector<Renderable*> RENDERABLECOMPONENTS;
	static std::vector<SmartPointer<GameObjects>> GAMEOBJECTS;

	static bool isInput = false;
	static bool exit = false;
	
	bool __Init__() {

		DEBUG_PRINT("------- STARTING ENGINE ---------");
		InputManager::Init();

		return true;
	}

	void __Run__() {

		while (true) {

			GLib::Service(exit);

			float deltaTime = Timer::FrameTime();
			deltaTime /= 1000;

			Input::CheckForInput(deltaTime);

			Physics::Run(deltaTime);

			Renderer::DrawGraphics();

			if (exit) {
				break;
			}
		}
	}

	bool __TerminateProgram__() {
		//Freeing all allocated Memory

		SmartPointer<GameObjects> allocatedGameObjects = GAMEOBJECTS.at(0);
		GAMEOBJECTS.pop_back();


		Renderable* allocatedRenderables = RENDERABLECOMPONENTS.at(0);
		RENDERABLECOMPONENTS.pop_back();
		delete allocatedRenderables;

		PhysicsComponent* allocatedPhysics = PHYSICSCOMPONENTS.at(0);
		PHYSICSCOMPONENTS.pop_back();
		delete allocatedPhysics;

		DEBUG_PRINT("------- TERMINATING ENGINE ---------");

		return true;
	}

	void AddPhysicsToList(PhysicsComponent* i_component) {
		PHYSICSCOMPONENTS.push_back(i_component);
	}
	
	void AddRenderableComponentToList(Renderable* i_component) {
		RENDERABLECOMPONENTS.push_back(i_component);
	}

	void AddGameObjectToList(const SmartPointer<GameObjects> i_gameObject) {
		GAMEOBJECTS.push_back(i_gameObject);
	}

	void CreatePlayer(const Point2D i_location, const char* i_name, const Point2D i_velocity) {
		SmartPointer<GameObjects> player = GameObjects::Create(i_location, i_name, i_velocity);
		GAMEOBJECTS.push_back(player);

		PhysicsComponent* physicsComponent = new PhysicsComponent(player, 10.0f, Point2D::Unit);
		PHYSICSCOMPONENTS.push_back(physicsComponent);

	}

	

	namespace Physics {
		void Run(float i_deltaTime) {
			for (int i = 0; i < PHYSICSCOMPONENTS.size(); i++) {
				PHYSICSCOMPONENTS.at(i)->UpdatePhysics(i_deltaTime);
			}
		}
	}

	namespace Renderer {
		void DrawGraphics() {
			for (int i = 0; i < RENDERABLECOMPONENTS.size(); i++) {
				RENDERABLECOMPONENTS.at(i)->DrawSprite();
			}
		}
	}

	//TODO::Adding CheckName Function in PhysicsComponent
	namespace Input {
		void CheckForInput(float i_deltaTime) {
			switch (InputManager::GetKeyDown()) {
			case KEYCHAR::W: PHYSICSCOMPONENTS.at(0)->ApplyForce(Point2D(0.0, 2.0), i_deltaTime);
				break;
			case KEYCHAR::A: PHYSICSCOMPONENTS.at(0)->ApplyForce(Point2D(-2.0, 0.0), i_deltaTime);
				break;
			case KEYCHAR::S: PHYSICSCOMPONENTS.at(0)->ApplyForce(Point2D(0.0, -2.0), i_deltaTime);
				break;
			case KEYCHAR::D: PHYSICSCOMPONENTS.at(0)->ApplyForce(Point2D(2.0, 0.0), i_deltaTime);
				break;
			case KEYCHAR::Q: exit = true;
				break;
			default: PHYSICSCOMPONENTS.at(0)->RemoveForce(i_deltaTime);
				break;
			}
		}
	}
}
