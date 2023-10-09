#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>

#include "DynamicObject.h"
#include "Utility.h"

#include <iostream>

DynamicObject::DynamicObject()
{
	_force = glm::vec3(0.0f, 0.0f, 0.0f);
	_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	_mass = 0.0f;
	_bRadius = 0.0f;

	_torque = glm::vec3(0.0f, 0.0f, 0.0f);
	_angular_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	_angular_momentom = glm::vec3(0.0f, 0.0f, 0.0f);

	_R = glm::mat3(1.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f,
				   0.0f, 0.0f, 1.0f);

	_rotQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_start = false;
	_stop = false;
}

DynamicObject::~DynamicObject()
{

}

void DynamicObject::StartSimulation(bool start)
{
	_start = start;

	_rotQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat3 bodyInertia = glm::mat3
	((2.0f / 5.0f) * _mass * std::pow(_bRadius, 2), 0, 0,
	  0, (2.0f / 5.0f) * _mass * std::pow(_bRadius, 2), 0,
	  0, 0, (2.0f / 5.0f) * _mass * std::pow(_bRadius, 2));

	_body_inertia_tensor_inverse = glm::inverse(bodyInertia);

	ComputeInverseInertiaTensor();

	_angular_velocity = _inertia_tensor_inverse * _angular_momentom;
}

void DynamicObject::ComputeInverseInertiaTensor()
{
	_inertia_tensor_inverse = _R * _body_inertia_tensor_inverse * glm::transpose(_R);
}

void DynamicObject::Euler(float deltaTs)
{
	float oneOverMass = 1 / _mass;

	_velocity += (_force * oneOverMass) * deltaTs;

	_position += _velocity * deltaTs;
}

void DynamicObject::RungeKutta2(float deltaTs)
{
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;

	force = _force;
	acceleration = force / _mass;
	k0 = acceleration * deltaTs;

	force = _force + k0 / 2.0f;
	acceleration = force / _mass;
	k1 = acceleration * deltaTs;

	_velocity += k1;
	_position += _velocity * deltaTs;
}

void DynamicObject::RungeKutta4(float deltaTs)
{
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 k0 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 k1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 k2 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 k3 = glm::vec3(0.0f, 0.0f, 0.0f);

	if (force != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		std::cout << " " << force.x;
		std::cout << " " << force.y;
		std::cout << " " << force.z;
	}

	force = _force;
	acceleration = force / _mass;
	k0 = acceleration * deltaTs;

	force = _force + k0 / 2.0f;
	acceleration = force / _mass;
	k1 = acceleration * deltaTs;

	force = _force + k1 / 2.0f;
	acceleration = force / _mass;
	k2 = acceleration * deltaTs;

	force = _force + k2;
	acceleration = force / _mass;
	k3 = acceleration * deltaTs;


	_velocity += (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;
	//_velocity += k3;
	_position += _velocity * deltaTs;


	glm::vec3 tempTorque = glm::vec3(0.0f, 0.0f, 0.0f);

	tempTorque = _torque;
	k0 = deltaTs * tempTorque;

	tempTorque = _torque + k0 / 2.0f;
	k1 = deltaTs * tempTorque;

	tempTorque = _torque + k1 / 2.0f;
	k2 = deltaTs * tempTorque;

	tempTorque = _torque + k2;
	k3 = deltaTs * tempTorque;

	_angular_momentom += (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;

	if (_stop == true)
		_angular_momentom = glm::vec3(0.0f, 0.0f, 0.0f);

	ComputeInverseInertiaTensor();

	_angular_velocity = _inertia_tensor_inverse * _angular_momentom;

	glm::mat3 omega_star = glm::mat3(0.0f, -_angular_momentom.z, _angular_velocity.y,
									 _angular_velocity.z, 0.0f, -_angular_velocity.x,
								     -_angular_velocity.y, _angular_velocity.x, 0.0f);

	_R += omega_star * _R * deltaTs;
}

void DynamicObject::Verlet(float deltaTs)
{
	glm::vec3 pos;

	pos = _position;

	
	pos = pos + _velocity * deltaTs + 0.5f * (_force / _mass) * (deltaTs * deltaTs);
	_velocity = (pos - _position) / deltaTs;
	

	_position += _velocity * deltaTs;
}

void DynamicObject::Update(float deltaTs, std::vector<GameObject*> gameObject, std::vector<DynamicObject*> physicsObjects)
{
	if (_start == true)
	{
		ClearForces();
		ClearTorque();

		glm::vec3 gravityForce = glm::vec3(0.0f, -9.8f * _mass, 0.0f);
		AddForce(gravityForce);

		for each(GameObject* object in gameObject)
		{
			PlaneCollisionResponse(object, deltaTs);
		}

		for each(DynamicObject* object in physicsObjects)
		{
			SphereCollisionResponse(object, deltaTs);
		}

		//Euler(deltaTs);
		//RungeKutta2(deltaTs);
		RungeKutta4(deltaTs);

	}
	UpdateModelMatrix();
}

void DynamicObject::SphereCollisionResponse(DynamicObject* object, float deltaTs)
{
	if (object != this)
	{
		if (object->GetType() == 0)
		{
			glm::vec3 contactNormal = glm::normalize(GetPosition() - object->GetPosition());
			glm::vec3 cp = glm::vec3(0.0f, 0.0f, 0.0f);
			bool collide = PFG::SphereToSphereCollision(GetPosition(), object->GetPosition(), GetBoundingRadius(), object->GetBoundingRadius(), cp);
			if (collide)
			{
				float e = 0.7f;
				float impulse = (-(1.0f + e) * glm::dot(_velocity - object->GetVelocity(), contactNormal)) / ((1.0f / _mass) + (1.0f / object->GetMass()));
				glm::vec3 collisionForce = impulse * contactNormal / deltaTs;
				glm::vec3 contactForce = -(_force)* contactNormal;

				AddForce(collisionForce + contactForce);
				_velocity += (impulse / _mass);
			}
		}
	}
}

void DynamicObject::PlaneCollisionResponse(GameObject* object, float deltaTs)
{

	if (object->GetType() == 1)
	{
		glm::vec3 contactNormal = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 nextPosition = _position + _velocity * deltaTs;
		glm::vec3 ci = glm::vec3(0.0f, 0.0f, 0.0f);

		bool collide = PFG::MovingSphereToPlaneCollision(contactNormal, _position, nextPosition, object, GetBoundingRadius(), ci);

		if (collide)
		{
			_stop = false;

			float linearImpulse = 0.0f;
			float angularImpulse = 0.0f;
			float friction = 0.5f;
			glm::vec3 r1 = _bRadius * glm::vec3(0.0f, 1.0f, 0.0f);

			glm::vec3 relativeVelocity = _velocity - object->GetVelocity();

			linearImpulse = (glm::dot(-(1.0f + friction) * (_velocity), contactNormal)) / ((1.0f / _mass) + (1.0f / object->GetMass()));
			angularImpulse = (glm::dot(-(1.0f + friction) * (relativeVelocity), contactNormal)) / ((1.0f / _mass) + (1.0f / object->GetMass()) + glm::dot(_inertia_tensor_inverse * (r1 * contactNormal), contactNormal));

			glm::vec3 impulseForce = (linearImpulse + angularImpulse) * contactNormal;
			glm::vec3 contactForce = -(_force)* contactNormal;
			AddForce(impulseForce + contactForce);
			_velocity += (impulseForce / _mass);


			glm::vec3 forwardRelativeVelocity = relativeVelocity - glm::dot(relativeVelocity, contactNormal) * contactNormal;
			glm::vec3 forwardRelativeDirection = glm::vec3(0.0f, 0.0f, 0.0f);

			if (forwardRelativeVelocity != glm::vec3(0.0f, 0.0f, 0.0f))
			{
				forwardRelativeDirection = glm::normalize(forwardRelativeVelocity);
			}

			float mu = 0.5f;
			glm::vec3 frictionDirection = forwardRelativeDirection * -1.0f;
			glm::vec3 frictionForce = frictionDirection * mu * glm::length(contactForce);
			if (glm::length(forwardRelativeVelocity) - ((glm::length(frictionForce) / _mass) * deltaTs) > 00.00f)
			{
				AddForce(frictionForce);
			}
			else
			{
				frictionForce = forwardRelativeVelocity * -1.0f;
				AddForce(frictionForce);
				_stop = true;
			}

			glm::vec3 tempTorque = (glm::cross(r1, contactForce)) + (glm::cross(r1, frictionForce));

			tempTorque.x -= _angular_momentom.x * 20.0f;
			tempTorque.z -= _angular_momentom.z * 20.0f;

			AddTorque(tempTorque);

		}
	}
}

void DynamicObject::UpdateModelMatrix()
{
	glm::mat4 model_rotation = glm::mat4(_R);

	glm::quat rot = glm::normalize(glm::quat_cast(_R));

	_R = glm::mat3_cast(rot);

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_modelMatrix = _modelMatrix * glm::mat4_cast(rot);
	_modelMatrix = glm::scale(_modelMatrix, _scale);
	_invModelMatrix = glm::inverse(_modelMatrix);
}