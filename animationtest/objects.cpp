#include "base.h"
#include "objects.h"
#include <fstream>

vao cube::operator()()
{
	static vao v = vao();
	if (v.id == -1)
	{
		xfvec<vec3> verts =
		{
			{0, 0, 0},
			{1, 0, 0}, {0, 1, 0}, {0, 0, 1},
			{0, 1, 1}, {1, 0, 1}, {1, 1, 0},
			{1, 1, 1}
		};
		verts = verts.map([](const vec3& v) { return v - 0.5f; });
		xfvec<uint> is =
		{
			0, 1, 2, 6, 2, 1,
			1, 5, 6, 7, 6, 5,
			5, 3, 7, 4, 7, 3,
			3, 0, 4, 2, 4, 0,
			2, 6, 4, 7, 4, 6,
			5, 3, 1, 0, 1, 3
		};
		v.gen();
		buffer(verts, GL_ARRAY_BUFFER);
		v.attrib(0, 3, 0, 0);
		v.attrib(1, 3, 0, 0);
		buffer(is, GL_ELEMENT_ARRAY_BUFFER);
		v.size = is.size();
	}
	return v;
}

vao plane::operator()(float s)
{
	static vao v = vao();
	if (v.id == -1)
	{
		xfvec<vec3> verts =
		{
			{0, 0, 0}, {s, 0, 0}, {0, s, 0}, 
			{s, s, 0}, {0, s, 0}, {s, 0, 0}	
		};
		v.gen();
		buffer(verts, GL_ARRAY_BUFFER);
		v.attrib(0, 3, 0, 0);
		v.attrib(1, 3, 0, 0);
		v.size = verts.size();
	}
	return v;
}

vao obj::operator()(const char* path)
{
	ifstream s;
	s.open(path);
	if (s.is_open()) std::cout << path << " obj file is open\n";
	else std::cout << "cant open obj file : " << path << "\n";
	xfstr code;
	xfstr sub;
	vec3 v;
	xfvec<vec3> vertices;
	xfvec<vec3> normals;
	xfvec<vec2> textures;
	xfvec<uvec3> indices;
	while (code.getline(s)) {
		sub = code.substr(0, 2);
		if (sub == "v ") {
			code.substr(2) >> v.x >> v.y >> v.z;
			vertices.push(v);

		}
		if (sub == "vt") {
			code.substr(3) >> v.x >> v.y;
			textures.push(v.xy);
		}
		if (sub == "vn") {
			code.substr(3) >> v.x >> v.y >> v.z;
			normals.push(v);
		}
		if (sub == "f ") {
			xfstr ssub = code.substr(2);
			while (ssub.find('/')) {
				uvec3 uv;
				ssub >> uv.x; --uv.x;
				ssub.erase(ssub.begin());
				ssub >> uv.y; --uv.y;
				ssub.erase(ssub.begin());
				ssub >> uv.z; --uv.z;
				indices.push(uv);
			}
		}
	}
	s.close();
	xfvec<indexed> is;
	is.resize(indices.size());
	for (uint i = 0; i < indices.size(); ++i) {
		is[i] =
		{
			vertices[indices[i].x],
			normals[indices[i].z],
			textures[indices[i].y]
		};
	}
	vao vao;
	vao.gen();
	buffer(is, GL_ARRAY_BUFFER);
	vao.attrib(0, 3, 8, 0);
	vao.attrib(1, 3, 8, 3);
	vao.attrib(2, 2, 8, 6);
	vao.size = is.size();
	return vao;
}

void obj::transform(const char* path, float scalar, const quat& q, const vec3& t)
{
	ifstream s; 
	s.open(path);
	if (s.is_open()) std::cout << path << " obj file is open\n";
	else
	{
		std::cout << "cant open obj file : " << path << "\n";
		return;
	}
	xfstr code;
	xfstr sub;
	vec3 v;

	xfvec<vec3> vertices;
	xfvec<vec2> textures;
	xfvec<vec3> normals;
	xfvec<xfstr> faces;
	while (code.getline(s)) {
		sub = code.substr(0, 2);
		if (sub == "v ") {
			code.substr(2) >> v.x >> v.y >> v.z;
			vertices.push(( q * (v * scalar)) + t);
		}
		if (sub == "vt") {
			code.substr(3) >> v.x >> v.y;
			textures.push(v.xy);
		}
		if (sub == "vn") {
			code.substr(3) >> v.x >> v.y >> v.z;
			normals.push(q * v);
		}
		if (sub == "f ") {
			faces.push(code.c_str());
		}
	}
	s.close();
	ofstream so;
	so.open((xfstr(path) + path).c_str());

	for (vec3& v : vertices) so << "v " << v;
	for (vec2& v : textures) so << "vt " << v;
	for (vec3& v : normals)  so << "vn " << v;
	for (xfstr& s : faces)   so << s << "\n";
}

void wall::draw() {
	shader::active->uniform("xform", xform);
	v.bind();
	glDrawArrays(GL_TRIANGLES, 0, v.size);
}
