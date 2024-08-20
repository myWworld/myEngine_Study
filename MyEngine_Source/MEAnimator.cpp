#include "MEAnimator.h"
#include "../MyEngine_Source/CommonInclude.h"


namespace ME
{
	Animator::Animator()
		:Component(enums::eComponentType::Animator)
		,mActiveAnimation(nullptr)
		,mAnimations{}
		,mbLoop(false)
		,mEvents {}
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto &iter: mEvents )
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->GetName());


			if (mActiveAnimation->IsComplete() == true)
			{	
				if (events)
				{
					events->CompleteEvent();
				}

				if(mbLoop == true)
					mActiveAnimation->Reset();
			}

		}
	}

	void Animator::LateUpdate()
	{
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}


	void Animator::CreateAnimation(const std::wstring& name,
		graphics::Texture* spriteSheet,
		Vector2 leftTop, Vector2 size, 
		Vector2 offset
		,float duration
		,UINT spriteLength, UINT spriteLength2 )
	{
		Animation* animation = nullptr;

		animation = FindAnimation(name);

		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, leftTop,
			size, offset
			, duration, spriteLength,spriteLength2);

		animation->SetAnimator(this);

		Events* events = new Events();
		mEvents.insert({ name, events });

		mAnimations.insert({ name, animation });

	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;


	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;


		if (mActiveAnimation)
		{
			Events* currentEvents
				= FindEvents(mActiveAnimation->GetName());
			
			if (currentEvents)
			{
				currentEvents->EndEvent();
			}
		}

		Events* nextEvents
			= FindEvents(animation->GetName());

		if (nextEvents)
		{
			nextEvents->StartEvent();
		}

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;

	}

	Animator::Events* Animator::FindEvents(const std::wstring & name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->StartEvent.mEvent;

	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->CompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->EndEvent.mEvent;
	}
}