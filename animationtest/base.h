#pragma once
#include "xfstd.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "enumkey.h"
using namespace std;
inline const mat2 m2id;
inline const mat3 m3id;
inline const mat4 m4id;

struct window {
	inline static vec2 size;
	inline static GLFWwindow* _window = nullptr;
	static void init(int x, int y);
	static bool runs();
};

struct clock {
	inline static float dt;
	inline static float timepassed = 0;
	inline static float fps;
	static void elapse();
};

struct mouse {
	inline static double x = 0, y = 0;
	inline static bool status = 1;
	inline static vec2 pos = 0;
	inline static vec2 delta = 0;
	static void resetPos();
	static void hide();
	static void show();
	static void toggle();
	static void update();
	static vec4 normalized();
};

class shader {
	uint id;
public:
	inline static shader* active = nullptr;
	shader();
	shader(const char* cs_path);
	shader(const char* vs_path, const char* fs_path);
	shader(const shader&);
	void use();
	void uniform(const char* uni, const vec2& v);
	void uniform(const char* uni, const vec3& v);
	void uniform(const char* uni, const vec4& v);
	void uniform(const char* uni, const mat2& m);
	void uniform(const char* uni, const mat3& m);
	void uniform(const char* uni, const mat4& m);
	void uniform(const char* uni, const xfvec<vec2>& v);
	void uniform(const char* uni, const xfvec<vec3>& v);
	void uniform(const char* uni, const xfvec<vec4>& v);
	void uniform(const char* uni, const xfvec<mat2>& v);
	void uniform(const char* uni, const xfvec<mat3>& v);
	void uniform(const char* uni, const xfvec<mat4>& v);
	void uniform(const char* uni, float x);
	void uniform(const char* uni, int x);
	void uniform(const char* uni, uint x);
	void uniform(const char* uni, float x, float y);
	void uniform(const char* uni, int x, int y);
	void uniform(const char* uni, uint x, uint y);
	void uniform(const char* uni, float x, float y, float z);
	void uniform(const char* uni, int x, int y, int z);
	void uniform(const char* uni, uint x, uint y, uint z);
	void uniform(const char* uni, float x, float y, float z, float w);
	void uniform(const char* uni, int x, int y, int z, int w);
	void uniform(const char* uni, uint x, uint y, uint z, uint w);
};

struct vao {
	uint id, size;
	vao();
	vao(const vao& v);
	vao& operator =(const vao&);
	void gen();
	void bind();
	void attrib(uint layout, uint size, uint stride, uint ptr);
	void attribI(uint layout, uint size, uint stride, uint ptr);
};

struct indexed {
	vec3 v, n;
	vec2 t;
};	


template<class T>
inline uint buffer(const xfvec<T>& verts, int type = GL_ARRAY_BUFFER) {
	uint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, verts.size() * sizeof(T), verts.data(), GL_STATIC_DRAW);
	return vbo;
}

inline static bool in(int key) {
	return key < 3 ? glfwGetMouseButton(window::_window, key) : glfwGetKey(window::_window, key);
}

struct texture {
	uint id;
	texture() : id(-1) {}

	texture(const char* path);

	void bind();

};

struct ui {
	struct Character {
		uint TextureID;   // ID handle of the glyph texture
		ivec2 Size;    // Size of glyph
		ivec2 Bearing;  // Offset from baseline to left/top of glyph
		uint Advance;    // Horizontal offset to advance to next glyph
	};

	xfmap<char, Character> Characters;
	uint VAO, VBO;
	shader s;

	ui(const char* vs, const char* fs, const char* font);

	void render(const xfstr& text, float x, float y, float scale = 0.4, const vec3& color = 0);

};

struct crosshair
{
	vao vao;
	crosshair();
	void draw();
};

