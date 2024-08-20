#include "MECamera.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "MEApplication.h"

extern ME::Application application;

namespace ME
{
	Camera::Camera()
		:Component(enums::eComponentType::Camera)
		, mDistance(Vector2::Zero)
		, mResolution(Vector2(1600,900))
		, mLookPosition(Vector2::One)
		, mTarget(nullptr)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
	}
	void Camera::Update()
	{
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();

			mLookPosition = cameraTr->GetPosition();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);

	}

	void Camera::LateUpdate()
	{

	}
	void Camera::Render(HDC hdc)
	{
	}
}