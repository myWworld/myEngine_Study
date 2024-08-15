#pragma once

namespace ME::math
{
	struct Vector2
	{

		static Vector2 One;
		static Vector2 Zero;

		float x;
		float y;

		Vector2()
			:x(0.0f)
			, y(0.0f)
		{

		}
		
		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{

		}


		Vector2 operator-(Vector2 other)
		{
			Vector2 rst;
			rst.x = x - other.x;
			rst.y = y - other.y;

			return rst;
		}

		Vector2 operator+(Vector2 other)
		{
			Vector2 rst;
			rst.x = x + other.x;
			rst.y = y + other.y;

			return rst;
		}
		Vector2 operator/(float value)
		{
			Vector2 rst;
			rst.x = x / value;
			rst.y = y / value;

			return rst;

		}
	};

}

