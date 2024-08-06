
#include "CommonInclude.h"

namespace ME {

	using namespace std;

	enum class eKeystate
	{
		Down,
		Pressed,
		Up,
		None,

	};

	enum class eKeyCode
	{
		Q,W,E,R,T,Y,U,I,O,P
		,A,S,D,F,G,H,J,K,L
		,Z,X,C,V,B,N,M,
		End,
	};

	class Input
	{

	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeystate state;
			bool bPressed;

		};

		static void Initialize();
		static void Update();

		static bool GetKeyDown(eKeyCode code) { return mKeys[(UINT)code].state == eKeystate::Down; }
		static bool GetKeyUp(eKeyCode code){ return mKeys[(UINT)code].state == eKeystate::Up; }
		static bool GetKey(eKeyCode code) {
			return mKeys[(UINT)code].state == eKeystate::Pressed;
		}

	private:

		static vector<Key> mKeys;
	};
}
