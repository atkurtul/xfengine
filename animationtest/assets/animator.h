#include "xml_parser.h"
#include "base.h"
struct bone
{
	int id;
	bone* parent;
	xfvec<bone*> children;
	mat4 bind;
	mat4 inv;
	mat4& anim;

	bone(int id, const mat4& bind, const mat4& inv, mat4& home);
	void addChild(bone* b);
	~bone();
};


struct decomp
{
	quat q;
	vec3 v;
	decomp() {}
	decomp(const quat& q, const vec3& v) :
		q(q), v(v)
	{}
	decomp(const mat4& m) :
		q(m), v(m.col[3].xyz)
	{}
	decomp interpolate(const decomp& d, float t)
	{
		if (t < 0.f) t = -t;
		return
		{
			q * (1.f - t) + d.q * sign(dot(q, d.q)) * t,
			v + (d.v - v) * cbrtf (t)
		};
	}
	operator mat4 () const
	{
		mat4 re = q;
		re.col[3].xyz = v;
		return  re;
	}
};

struct frame : xfmap<float, mat4>
{
	mat4 getFrameAt(float t) const
	{
		if (data.empty()) return m4id;
		for (auto& m : data)
			if (m.k >= t) return m.v;
	}
};
using animation = xfmap<uint, frame>;
struct armature
{
	mat4 xform;
	xfvec<bone*> bones;


	~armature();
	void init(xml_node* n, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, xfvec<mat4>& home);
	void addBone(xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, uint prefixlen, xfvec<mat4>& home);
	void addChildren(bone* parent, xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, uint prefixlen, xfvec<mat4>& home);

	void applyPose(animation&, float t);
	void applyToChildren(bone*, animation&, float, const mat4&);
};


struct model
{
	animation anim;
	armature arm;
	xfvec<mat4> home;
	vao mesh;
	uint ssbo;
	bool animated;
	float t = 0.f;
	float len = 0.f;

	model(const char*, bool = 0);
	void update();
	void draw();

};
