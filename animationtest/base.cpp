#include "base.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void window::init(int x, int y) {
	glfwInit();
	_window = glfwCreateWindow(x, y, "OpenGL", 0, 0);
	size = vec2(float(x), float(y));
	glfwMakeContextCurrent(_window);
	gladLoadGL();
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

bool window::runs() {
	if (glfwWindowShouldClose(_window) || in(key::ESCAPE)) {
		glfwDestroyWindow(_window);
		glfwTerminate();
		return 0;
	}
	clock::elapse();
	mouse::update();
	glfwSwapBuffers(_window);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 1;

}

void clock::elapse() {
	static float time = float(glfwGetTime());
	static long long n = 0;
	++n;

	dt = float(glfwGetTime()) - time;
	timepassed += dt;
	fps = n/ timepassed;
	if (n > 300) n = 0, timepassed = 0;
	time = float(glfwGetTime());
}

void mouse::resetPos() {
	glfwSetCursorPos(window::_window, window::size.x * 0.5, window::size.y * 0.5);
}
void mouse::hide() {
	if (status) {
		resetPos();
		status = 0;
	}
	glfwSetInputMode(window::_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void mouse::show() {
	status = 1;
	glfwSetInputMode(window::_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void mouse::toggle() {
	status = !status;
	status ? show() : hide();
}

void mouse::update() {
	glfwGetCursorPos(window::_window, &x, &y);
	pos.x = float(x);
	pos.y = float(y);
	if (status) {
		vec2 prev = pos;
		delta = pos - prev;
		prev = pos;
	}
	else {
		delta = pos - window::size * 0.5f;
		glfwSetCursorPos(window::_window, window::size.x * 0.5, window::size.y * 0.5);
	}
}

vec4 mouse::normalized()
{
	vec2 re = 2.f * (mouse::pos / window::size);
	re.y = 2.f - re.y;
	return vec4(re - 1.f, 0.f, 1.f);
}

shader::shader() : id(-1) {}
shader::shader(const char* cs_path)
{
	ifstream ifs(cs_path);
	xfstr code;
	ifs >> code;
	ifs.close();
	const char* p = code.c_str();
	uint cs = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(cs, 1, &p, NULL);
	glCompileShader(cs);
	id = glCreateProgram();
	glAttachShader(id, cs);
	glLinkProgram(id);
	glUseProgram(id);
	{
		int infolen, res;
		glGetShaderiv(cs, GL_COMPILE_STATUS, &res);
		glGetShaderiv(cs, GL_INFO_LOG_LENGTH, &infolen);
		xfstr errormsg(infolen);
		glGetShaderInfoLog(cs, infolen, NULL, errormsg.data());
		cout << errormsg << '\n';
	}
	{
		int infolen, res;
		glGetProgramiv(id, GL_COMPILE_STATUS, &res);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infolen);
		xfstr errormsg(infolen);
		glGetShaderInfoLog(id, infolen, NULL, errormsg.data());
		cout << errormsg << '\n';
	}
}

shader::shader(const char* vs_path, const char* fs_path) {
	ifstream vs_ifs(vs_path);
	xfstr vs_code; 
	vs_ifs >> vs_code;
	vs_ifs.close();
	const char* p = vs_code.c_str();
	uint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &p, NULL);
	glCompileShader(vs);
	ifstream fs_ifs(fs_path);
	xfstr fs_code; 
	fs_ifs >> fs_code;
	fs_ifs.close();
	const char* pp = fs_code.c_str();
	uint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &pp, NULL);
	glCompileShader(fs);
	id = glCreateProgram();
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glUseProgram(id);
	active = this;
	{
		int infolen, res;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &res);
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infolen);
		xfstr errormsg(infolen);
		glGetShaderInfoLog(vs, infolen, NULL, errormsg.data());
		cout << errormsg << '\n';
	}
	{
		int infolen, res;
		glGetShaderiv(fs, GL_COMPILE_STATUS, &res);
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infolen);
		xfstr errormsg(infolen);
		glGetShaderInfoLog(fs, infolen, NULL, errormsg.data());
		cout << errormsg << '\n';
	}
	{
		int infolen, res;
		glGetProgramiv(id, GL_COMPILE_STATUS, &res);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infolen);
		xfstr errormsg(infolen);
		glGetShaderInfoLog(id, infolen, NULL, errormsg.data());
		cout << errormsg << '\n';
	}
}

shader::shader(const shader& s) : id(s.id)
{
}

void shader::use()
{
	glUseProgram(id);
	active = this;
}

vao::vao() : id(-1), size(0) {}
vao::vao(const vao& v) : id(v.id), size(v.size){}

vao& vao::operator=(const vao& vao)
{
	id = vao.id;
	size = vao.size;
	return *this;
}


void vao::gen() {
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}
void vao::bind() {
	glBindVertexArray(id);
}
void vao::attrib(uint layout, uint size, uint stride, uint ptr) {
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride * 4, (void*)(ptr * 4));
}

void vao::attribI(uint layout, uint size, uint stride, uint ptr)
{
	glEnableVertexAttribArray(layout);
	glVertexAttribIPointer(layout, size, GL_UNSIGNED_INT, stride * 4, (void*)(ptr * 4));
}

void shader::uniform(const char* uni, const vec2& v) { glUniform2fv(glGetUniformLocation(id, uni), 1, v.data); }
void shader::uniform(const char* uni, const vec3& v) { glUniform3fv(glGetUniformLocation(id, uni), 1, v.data); }
void shader::uniform(const char* uni, const vec4& v) { glUniform4fv(glGetUniformLocation(id, uni), 1, v.data); }
void shader::uniform(const char* uni, const mat2& m) { glUniformMatrix2fv(glGetUniformLocation(id, uni), 1, 0, m.data); }
void shader::uniform(const char* uni, const mat3& m) { glUniformMatrix3fv(glGetUniformLocation(id, uni), 1, 0, m.data); }
void shader::uniform(const char* uni, const mat4& m) { glUniformMatrix4fv(glGetUniformLocation(id, uni), 1, 0, m.data); }
void shader::uniform(const char* uni, const xfvec<vec2>& v) { glUniform2fv(glGetUniformLocation(id, uni), v.size(), (float*)v.data()); }
void shader::uniform(const char* uni, const xfvec<vec3>& v) { glUniform3fv(glGetUniformLocation(id, uni), v.size(), (float*)v.data()); }
void shader::uniform(const char* uni, const xfvec<vec4>& v) { glUniform4fv(glGetUniformLocation(id, uni), v.size(), (float*)v.data()); }
void shader::uniform(const char* uni, const xfvec<mat2>& v) { glUniformMatrix2fv(glGetUniformLocation(id, uni), v.size(), 0, (float*)v.data()); }
void shader::uniform(const char* uni, const xfvec<mat3>& v) { glUniformMatrix3fv(glGetUniformLocation(id, uni), v.size(), 0, (float*)v.data()); }
void shader::uniform(const char* uni, const xfvec<mat4>& v) { glUniformMatrix4fv(glGetUniformLocation(id, uni), v.size(), 0, (float*)v.data()); }
void shader::uniform(const char* uni, float x) { glUniform1f(glGetUniformLocation(id, uni), x); }
void shader::uniform(const char* uni, int x) { glUniform1i(glGetUniformLocation(id, uni), x); }
void shader::uniform(const char* uni, uint x) { glUniform1ui(glGetUniformLocation(id, uni), x); }
void shader::uniform(const char* uni, float x, float y) { glUniform2f(glGetUniformLocation(id, uni), x, y); }
void shader::uniform(const char* uni, int x, int y) { glUniform2i(glGetUniformLocation(id, uni), x, y); }
void shader::uniform(const char* uni, uint x, uint y) { glUniform2ui(glGetUniformLocation(id, uni), x, y); }
void shader::uniform(const char* uni, float x, float y, float z) { glUniform3f(glGetUniformLocation(id, uni), x, y, z); }
void shader::uniform(const char* uni, int x, int y, int z) { glUniform3i(glGetUniformLocation(id, uni), x, y, z); }
void shader::uniform(const char* uni, uint x, uint y, uint z) { glUniform3ui(glGetUniformLocation(id, uni), x, y, z); }
void shader::uniform(const char* uni, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(id, uni), x, y, z, w); }
void shader::uniform(const char* uni, int x, int y, int z, int w) { glUniform4i(glGetUniformLocation(id, uni), x, y, z, w); }
void shader::uniform(const char* uni, uint x, uint y, uint z, uint w) { glUniform4ui(glGetUniformLocation(id, uni), x, y, z, w); }

texture::texture(const char* path) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int w, h, d;
	unsigned char* data = stbi_load(path, &w, &h, &d, 0);
	if (data)
	{
		if (d == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

ui::ui(const char* vs, const char* fs, const char* font) {
	s = shader(vs, fs);
	s.uniform("projection", ortho(0.0f, window::size.x, 0, window::size.y));
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	FT_Face face;
	if (FT_New_Face(ft, font, 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++){
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		uint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character = {
			texture,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(c, character);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void ui::render(const xfstr& text, float x, float y, float scale, const vec3& color)
{
	s.use();
	s.uniform("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	const char* c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.Advance >> 6)* scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

struct material {
	material(const xfstr& s) : name(s) {}
	xfstr name;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float emission;
	float phong;
	float halo_factor;
	float refractive_index;
};

struct part {
	part(const xfstr& s) : name(s) {}
	xfstr name;
	xfvec<vec3> vertices;
	xfvec<vec3> normals;
	xfvec<vec2> textures;
	xfvec<uvec3> indices;
};

void readmtl(xfvec<material>& mats, const xfstr& matpath) {
	ifstream s(matpath.data());
	xfstr code;
	xfstr sub;
	while (code.getline(s)) {
		sub = code.substr(0, 2);
		if (code.substr(0, 6) == "newmtl") {
			mats.push(code.substr(7));
		}
		if (sub == "Ns") {
			code.substr(3) >> mats.back().phong;
		}
		if (sub == "Ka") {
			vec3& v = mats.back().ambient;
			code.substr(3) >> v.x >> v.y >> v.z;
		}
		if (sub == "Kd") {
			vec3& v = mats.back().diffuse;
			code.substr(3) >> v.x >> v.y >> v.z;
		}
		if (sub == "Ks") {
			vec3& v = mats.back().specular;
			code.substr(3) >> v.x >> v.y >> v.z;
		}
		if (sub == "Ke") {
			code.substr(3) >> mats.back().emission;
		}
		if (sub == "Ni") {
			code.substr(3) >> mats.back().refractive_index;
		}
		if (sub == "d ") {
			code.substr(2) >> mats.back().halo_factor;
		}

	}
}

crosshair::crosshair()
{
	float l = 0.0025f;
	xfvec<vec3> verts = {
		{0, l, -0.1}, {0, -l, -0.1},
		{-l, 0, -0.1}, {l, 0, -0.1}
	};
	vao.gen();
	buffer(verts, GL_ARRAY_BUFFER);
	vao.attrib(0, 3, 0, 0);
}

void crosshair::draw() {
	vao.bind();
	shader::active->uniform("view", m4id);
	shader::active->uniform("xform", m4id);
	glDrawArrays(GL_LINES, 0, 4);
}

