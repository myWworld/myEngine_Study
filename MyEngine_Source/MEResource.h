#pragma once
#include "MEEntity.h"


namespace ME
{


	class Resource abstract: public Entity // �޸� �Ҵ� X ���� ��ӹ޾Ƽ� ���
	{
	public:
	
		Resource(enums::eResourceType type);
		virtual~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;
		
		const std::wstring& GetPath(){ return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:

		const enums::eResourceType mType;
		std::wstring mPath;
	};

}
