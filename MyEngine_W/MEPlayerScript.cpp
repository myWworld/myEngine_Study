#include "MEPlayerScript.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEGameObject.h"

namespace ME
{
	PlayerScript::PlayerScript()
		:isJump(false)
		,jumpSeconds(0)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			Transform *tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::Down) || Input::GetKey(eKeyCode::S))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.y += 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::Up) || Input::GetKey(eKeyCode::W))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.y -= 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::Space) && isJump == false)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			
			isJump = true;

			pos.y -= 800.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (isJump == true)
		{
			

			if (jumpSeconds == 20)
			{
				isJump = false;
				jumpSeconds = 0;
				return;
			}
			jumpSeconds++;

			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();

			pos.y += 40.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hdc)
	{
	}
}