#pragma once
#include "MEEntity.h"

namespace ME

{
	class UIBase :public Entity
	{
	public:
		UIBase();
		~UIBase();

		void Initialize();
		void Render(HDC hdc);
		void Active();

		void InActive();

		void Update();
		void LateUpdate();
	
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnClear();

		enums::eUIType GetType() { return mType; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() { return mbFullScreen; }
		

	private:

		enums::eUIType mType;
		bool mbFullScreen;
		bool mbEnabled;
	};

}
