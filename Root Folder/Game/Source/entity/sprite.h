#pragma once

#include "renderable2d.h"

class Sprite : public Renderable2D {
private:

public:
	Sprite(float x, float y, float width, float height, const vec4 &color);
};