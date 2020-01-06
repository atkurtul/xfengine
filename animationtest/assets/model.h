#include "xml_parser.h"
#include "base.h"

struct model;

struct frame : xfmap<float, mat4>
{
	mat4 getFrameAt(float t) const;
};

struct bone
{
	uint id;
	bone* parent = nullptr;
	xfvec<bone*> children;
	mat4 inv;
	mat4& xform;
	bone(uint id, const mat4& inv, mat4& home)
		: id(id), inv(inv), xform(home)
	{}
};

struct animation : xfmap<uint, frame>
{
	float len = 0.f;
	float t = 0.f;
	model& m;
	animation(model& m) : m(m) {}
	void update();

	void applyPose(xfvec<bone*>& v, const mat4& parentxf);
};
struct model
{
	xfvec<mat4>  home;
	xfvec<bone*> bones;
	mat4 xform;
	animation anim = *this;
	vao mesh;
	uint ssbo;
	model(const char* path);

	void addChildren(bone* parent, xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, xfvec<mat4>& home);

	struct weight
	{
		uint i;
		float w;
		bool operator <= (const weight& W) { return w <= W.w; }
	};

	struct vweight
	{
		uvec3 i;
		vec3 w;
	};

	xfvec<vweight> sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v);
	void draw();
};

