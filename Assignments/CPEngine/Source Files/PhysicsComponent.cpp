#include"GameObject.h"
#include"Point2D.h"
#include"PhysicsComponent.h"
#include<assert.h>
#include"SmartPointer.h"
#include"WeakPointer.h"

namespace Engine {

#pragma region Overload Methods

	PhysicsComponent::PhysicsComponent(SmartPointer<GameObjects> i_gameObject, float i_mass, Point2D i_drag):
		m_gameObject(i_gameObject), m_mass(i_mass) {
		m_drag = &i_drag;
	}

	PhysicsComponent::~PhysicsComponent() {
		/*assert(m_gameObject);
		delete m_gameObject;*/
		assert(m_drag);
		delete m_drag;
	}

#pragma endregion

#pragma region Physics Manipulation Methods

	void PhysicsComponent::UpdatePhysics(float i_deltaTime) {
		if (m_isForce) {
			//m_gameObject->Location((m_gameObject->Location() + (m_gameObject->Velocity() * i_deltaTime)));
			SmartPointer<GameObjects> tempObject = m_gameObject.AquireOwnership();
			Point2D updatedLocation = tempObject->Location() + (tempObject->Velocity() * i_deltaTime);
			tempObject->Location(updatedLocation);

		}
	}

	void PhysicsComponent::ApplyForce(Point2D i_force, float i_deltaTime) {
	
		SmartPointer<GameObjects> tempObject = m_gameObject.AquireOwnership();

		Point2D Accelaration = i_force / m_mass;

		Point2D velocity = tempObject->Velocity() + (Accelaration + i_deltaTime);

		tempObject->Velocity(((tempObject->Velocity() + velocity) / 2));

		m_isForce = true;
	}

	void PhysicsComponent::RemoveForce(float i_deltaTime) {
		Point2D drag = Point2D::Zero;
		SmartPointer<GameObjects> tempObject = m_gameObject.AquireOwnership();
		float vel_X = tempObject->Velocity().X();
		float vel_Y = tempObject->Velocity().Y();

		if (!(tempObject->Velocity() == Point2D::Zero)) {
			// Calculate drag to apply based on velocity

			if (vel_X) {
				drag = drag + ((vel_X > 0) ? Point2D(-m_drag->X(), 0) : Point2D(m_drag->X(), 0));
			}
			if (vel_Y) {
				drag = drag + ((vel_Y > 0) ? Point2D(0, -m_drag->Y()) : Point2D(0, m_drag->Y()));
			}
			drag = drag / m_mass;

			Point2D velocity = tempObject->Velocity() + (drag * i_deltaTime);

			tempObject->Velocity(velocity);
		}
	}

#pragma endregion


}