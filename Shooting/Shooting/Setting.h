#pragma once
#include"Game2d.h"
#include "math.h"

#define PI    3.141592654f
#define framesize_X 3.0f
#define framesize_Y 2.0f

namespace jm {

	//두점사이의 각도 반환
	inline float GetDirectionAngle(const vec2& center, const vec2& direction) {	
		float x = direction.x - center.x;
		float y = direction.y - center.y;
		float Angle = atan2(y, x) * 57.3f;
		if (0 > Angle)
			Angle += 360;
		return Angle;
	}

	//두점사이의 직선길이 반환
	inline float GetDirectionLength(const vec2& center, const vec2& direction) {
		float result = sqrt((center.x - direction.x) * (center.x - direction.x) + (center.y - direction.y) * (center.y - direction.y) );
		return result;
	}
}