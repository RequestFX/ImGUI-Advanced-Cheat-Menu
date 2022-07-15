#pragma once
#include "MH.hpp"

class Vec2i {
public:
	int x;
	int y;

	Vec2i() : x(0), y(0) {}
	Vec2i(int _x, int _y) : x(_x), y(_y) {}

	float len() {
		return MH::len(x, y);
	}
};

class Vec2f {
public:
	float x;
	float y;

	Vec2f() : x(0), y(0) {}
	Vec2f(float _x, float _y) : x(_x), y(_y) {}

	float len() {
		return MH::len(x, y);
	}
};

class Vec2d {
public:
	double x;
	double y;

	Vec2d() : x(0), y(0) {}
	Vec2d(double _x, double _y) : x(_x), y(_y) {}

	float len() {
		return MH::len(x, y);
	}
};

class Vec3i {
public:
	int x;
	int y;
	int z;

	Vec3i() : x(0), y(0), z(0) {}
	Vec3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

	float len() {
		return MH::len3(x, y, z);
	}
};

class Vec3f {
public:
	float x;
	float y;
	float z;

	Vec3f() : x(0), y(0), z(0) {}
	Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float len() {
		return MH::len3(x, y, z);
	}
};

class Vec3d {
public:
	double x;
	double y;
	double z;

	Vec3d() : x(0), y(0), z(0) {}
	Vec3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	double len() {
		return MH::len3(x, y, z);
	}
};