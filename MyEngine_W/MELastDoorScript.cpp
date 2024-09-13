#include "MELastDoorScript.h"
#include "MESceneManager.h"
#include "MEAnimator.h"

namespace ME
{
	LastDoorScript::LastDoorScript()
	{
	}
	LastDoorScript::~LastDoorScript()
	{
	}
	void LastDoorScript::Initialize()
	{
	}
	void LastDoorScript::Update()
	{
	}
	void LastDoorScript::LateUpdate()
	{
	}
	void LastDoorScript::Render(HDC hdc)
	{
	}
	void LastDoorScript::OnCollisionEnter(Collider* other)
	{
		
	}
	void LastDoorScript::OnCollisionStay(Collider* other)
	{

		if (other->GetName() == L"Player")
		{
			if (other->GetOwner()->GetComponent<Animator>()->IsComplete())
				SceneManager::LoadScene(L"Stage2");
		}
	}
	void LastDoorScript::OnCollisionExit(Collider* other)
	{
	}
}