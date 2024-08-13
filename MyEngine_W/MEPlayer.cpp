#include "MEPlayer.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"

void ME::Player::Initialize()
{
	GameObject::Initialize();
}

void ME::Player::Update()
{
	GameObject::Update();
}

void ME::Player::LateUpdate()
{
	GameObject::LateUpdate();

	if (Input::GetKeyDown(eKeyCode::Right))
	{
		Transform *tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
}

void ME::Player::Render(HDC hdc)
{
	GameObject::Render(hdc);
}
