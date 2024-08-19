#include "METurtle.h"

namespace ME
{
	Turtle::Turtle()
	{
	}
	Turtle::~Turtle()
	{
	}
	void Turtle::Initialize()
	{
		GameObject::Initialize();
	}
	void Turtle::Update()
	{
		GameObject::Update();
	}
	void Turtle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Turtle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}