#pragma once
#include "Console.h"
#include"SmartPointer.h"
#include"WeakPointer.h"
class GameObjects;
class Point2D;

namespace Engine {

	class PhysicsComponent {
	public:
		PhysicsComponent() = delete;
		PhysicsComponent(SmartPointer<GameObjects>, float, Point2D);
		~PhysicsComponent();
		
		void UpdatePhysics(float);
		void ApplyForce(Point2D, float);
		void RemoveForce(float);

	private:
		WeakPointer<GameObjects> m_gameObject;
		//GameObjects* m_gameObject;
		float m_mass;
		Point2D* m_drag;
		bool m_isForce;
	};
}