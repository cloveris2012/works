#ifndef SKEL_COLOR_H
#define SKEL_COLOR_H

#include "utils/MathUtil.h"

namespace skel {
class SK_API Color : public SkelObject {
public:
	Color() : r(0), g(0), b(0), a(0) {
	}

	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
		clamp();
	}

	inline Color &set(float _r, float _g, float _b, float _a) {
		this->r = _r;
		this->g = _g;
		this->b = _b;
		this->a = _a;
		clamp();
		return *this;
	}

	inline Color &set(const Color &other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		clamp();
		return *this;
	}

	inline Color &add(float _r, float _g, float _b, float _a) {
		this->r += _r;
		this->g += _g;
		this->b += _b;
		this->a += _a;
		clamp();
		return *this;
	}

	inline Color &add(const Color &other) {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		clamp();
		return *this;
	}

	inline Color &clamp() {
		r = MathUtil::clamp(this->r, 0, 1);
		g = MathUtil::clamp(this->g, 0, 1);
		b = MathUtil::clamp(this->b, 0, 1);
		a = MathUtil::clamp(this->a, 0, 1);
		return *this;
	}

	static float toColor(const char *value, size_t index) {
		char digits[3];
		char *error;
		int color;

		if (index >= strlen(value) / 2) return -1;

		value += index * 2;

		digits[0] = *value;
		digits[1] = *(value + 1);
		digits[2] = '\0';
		color = (int)strtoul(digits, &error, 16);
		if (*error != 0) return -1;

		return color / (float)255;
	}

	float r, g, b, a;
};
}


#endif //SKEL_COLOR_H
