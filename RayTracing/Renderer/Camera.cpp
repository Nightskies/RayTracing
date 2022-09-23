#include "Camera.h"

LightRay Camera::GetRay(f32 u, f32 v) const
{
	return { mPosition, mLowerLeftCorner + u * mXAxis + v * mYAxis - mPosition };
}