#pragma once
#include "objects.h"

struct cam
{
	float speed = 45.f;
    vec3 ray;
    mat4 view;
    dvec3& right = view.col[0].xyz;
    dvec3& up = view.col[1].xyz;
    dvec3& dir = view.col[2].xyz;
    vec3 pos = 1.2f;
    float& dt = clock::dt;
};

struct tpscam : cam
{
    mat4 xform;
    vec3& ppos = (vec3&)xform.row[3].xyz;
    float radius = 3.f;
    vao character; 
    void look();
    void move();
    void updateRay();
    void update();
};


struct terrain {
	vec2 size;
	uint div;
	xfvec<vec3> vertices;
	xfvec<uvec3> indices;
	vao mesh;
	uint vbo;
	uint drawsize;
	mat4 xform;
	texture t;
	terrain(float xx, float yy, uint div);
	void draw();
	float height(vec3 pos);
	void highlight(vec3 pos, const vec3& ray);
};

struct fpscam : cam
{
    void look();
	void move(terrain& t);
	void update(terrain& t);
};

struct shooter
{
	struct prj
	{
		mat4 xform;
		vec3& pos = (vec3&)xform.row[3].xyz;
		float y = 0;
		const vec3 dir;
		int f = 0;
		prj(const vec3& p, const vec3& d);
		void draw();
		bool ttd();
	};
	struct pptr {
		prj* p;
		~pptr() { delete p; }
		pptr(const vec3& p, const vec3& d) : p(new prj(p, d))
		{}
	};
	void update(const cam& cam);
	xfvec<pptr> projectiles;
	vao v = obj()("assets/models/sphere.obj");
};