#pragma once
#include "MEComponent.h"
#include "MEEntity.h"
#include "METexture.h"

namespace ME
{

	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force) { mForce = force; }
		
	private:
	
		float mMass;
		float mFriction;
		
		Vector2 mAccelation;
		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mGravity;

	};

}
