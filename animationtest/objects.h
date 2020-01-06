#pragma once
#include "base.h"

struct cube
{
	vao operator()();
};

struct plane
{
	vao operator()(float s = 1.f);
};

struct obj {
	vao operator()(const char* path);
	static void transform(const char* path, float s, const quat& q, const vec3& t);
};

struct wall
{
    vao v = plane()(10);
    mat4 xform;
    vec3& pos = (vec3&)xform.row[3].xyz;
	void draw();
};
