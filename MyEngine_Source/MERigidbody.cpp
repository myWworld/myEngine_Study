#include "MERigidbody.h"
#include "METime.h"
#include "METransform.h"
#include "MEGameObject.h"
namespace ME
{
	Rigidbody::Rigidbody()
		:Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(10.0f)
	, mForce(Vector2::Zero)
	, mVelocity(Vector2::Zero)
	, mLimitVelocity(Vector2(50.0f,1000.0f))
	, mGravity(Vector2(0.0f, 800.0f))
	, mAccelation(Vector2::Zero)

	{


	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// f = ma
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = math::Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		
		}
		else
		{
			//공중

			mVelocity += mGravity * Time::DeltaTime();
		}

		//최대속도 제한


		Vector2 gravity = mGravity;
		gravity.normalize();

		float dot = math::Vector2::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;

		if (mLimitVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitVelocity.x;
		}

		mVelocity = gravity + sideVelocity;

		if (!(mVelocity == Vector2::Zero))
		{
			//속도에 반대방향으로 마찰력 착용
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			//마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우
			if (mVelocity.length() <= friction.length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}

			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();

			pos = pos + mVelocity * Time::DeltaTime();
			tr->SetPosition(pos);

			mForce.clear();
		}
		

	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
}