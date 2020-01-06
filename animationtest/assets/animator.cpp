#include "animator.h"

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

xfvec<vweight> sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v)
{
	xfvec<vweight> re;
	uint current = 0;
	for (uint i : vcount) {
		xfvec<weight> temp;
		for (uint j = 0; j < i * 2; j += 2)
		{
			temp.push({ v[j + current * 2], weights[v[j + 1 + current * 2]] });
		}

		temp.sort();
		temp.reverse();
		vweight t;
		for (uint j = 0; j < 3 && j < temp.size(); ++j)
		{
			t.i[j] = temp[j].i;
			t.w[j] = temp[j].w;
		}
		float l = 1.f / (t.w.x + t.w.y + t.w.z);
		t.w.x *= l;
		t.w.y *= l;
		t.w.z *= l;
		re.push(t);
		current += i;
	}
	return re;
}


bone::bone(int id, const mat4& bind, const mat4& inv, mat4& home)
	: id(id), bind(bind), inv(inv), anim(home)
{}

void bone::addChild(bone* b)
{
	b->parent = this;
	children.push(b);
}

bone::~bone()
{
	for (bone* b : children) delete b;
}

armature::~armature()
{
	for (bone* b : bones) delete b;
}

void armature::init(xml_node* n, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, xfvec<mat4>& home)
{
	home.resize(namearray.size());
	xform = n->getChild("matrix")->readDataAsMat4<float>().front();
	auto bones = n->getChildrenByAttrib("node", "type", "JOINT");
	uint prefixlen = xfstr(n->attribs["id"]).size() + 1;
	for (xml_node* n : bones)
		addBone(n, namearray, invbinds, prefixlen, home);
}

void armature::addBone(xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, uint prefixlen, xfvec<mat4>& home)
{
	xfstr xid = node->attribs["id"];
	int id = namearray.find(xid.substr(prefixlen)) - namearray.begin();
	mat4 bind = node->getChild("matrix")->readDataAsMat4<float>().front();
	bone* b = new bone(id, bind, invbinds[id], home[id]);
	bones.push(b);
	auto bones = node->getChildrenByAttrib("node", "type", "JOINT");
	for (xml_node* n : bones)
		addChildren(b, n, namearray, invbinds, prefixlen, home);
}

void armature::addChildren(bone* parent, xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, uint prefixlen, xfvec<mat4>& home)
{
	xfstr xid = node->attribs["id"];
	int id = namearray.find(xid.substr(prefixlen)) - namearray.begin();
	mat4 bind = node->getChild("matrix")->readDataAsMat4<float>().front();
	bone* b = new bone(id, bind, invbinds[id], home[id]);
	parent->addChild(b);
	auto bones = node->getChildrenByAttrib("node", "type", "JOINT");
	for (xml_node* n : bones)
		addChildren(b, n, namearray, invbinds, prefixlen, home);
}


void armature::applyPose(animation& anim, float t)
{
	for (bone* b : bones)
	{
		mat4 xf = anim[b->id].ref().getFrameAt(t);
		b->anim = xf * b->inv;
		applyToChildren(b, anim, t, xf);
	}
}

void armature::applyToChildren(bone* parent, animation& anim, float t, const mat4& parentxf)
{
	for (bone* b : parent->children)
	{
		mat4 xf = anim[b->id].ref().getFrameAt(t);
		b->anim = parentxf * xf * b->inv;
		applyToChildren(b, anim, t, parentxf * xf);
	}
}


model::model(const char* path, bool addanim) : animated(addanim)
{
	xml_parser p(path);

	//geometry
	auto vertices = p.root.getDescendantByAttrib("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
	auto normals = p.root.getDescendantByAttrib("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
	auto textures = p.root.getDescendantByAttrib("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
	uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
	auto indices = p.root.getDescendant("p")->readDataAs<uint>();

	//controllers
	auto namearray = p.root.getDescendantByAttrib("Name_array", "id", "skin-joints-array")->readDataAsStr();
	auto invbinds = p.root.getDescendantByAttrib("float_array", "id", "skin-bind_poses-array")->readDataAsMat4<float>();
	auto weights = p.root.getDescendantByAttrib("float_array", "id", "skin-weights-array")->readDataAs<float>();
	auto vcount = p.root.getDescendant("vcount")->readDataAs<uint>();
	auto vs = p.root.getDescendant("v")->readDataAs<uint>();
	auto sorted = sortWeights(weights, vcount, vs);

	//bone hierarchy
	arm.init(p.root.getDescendantByAttrib("node", "id", "Armature"), namearray, invbinds, home);


	if (addanim)
	{
		//animation
		auto root = p.root.getDescendantByAttrib("animation", "id", "action_container");
		for (xfstr& n : namearray)
		{
			auto q = root->getDescendantByAttrib("float_array", "id", n + "_pose_matrix-input-array");
			if (q)
			{
				uint id = &n - namearray.begin();
				auto in = q->readDataAs<float>();
				auto out = root->getDescendantByAttrib("float_array", "id", n + "_pose_matrix-output-array")->readDataAsMat4<float>();
				frame f;
				for (int i = 0; i < in.size(); ++i)
				{
					f[in[i]] = out[i];
					if (in[i] > len) len = in[i];
				}
				cout << f.size() << "\n";
				anim[id] = f;
			}
		}
	}


	struct layout
	{
		vec3 v;
		vec3 c;
		vec3 n;
		vec2 t;
		uvec3 j;
		vec3 w;
	};

	xfvec<layout> finalbuffer;
	for (int i = 0; i < indices.size(); i += dim) {

		finalbuffer.push(
			{
				vertices[indices[i]],
				vertices[indices[i]], // color
				normals[indices[i + 1]], // normal
				textures[indices[i + 2]], // uv
				sorted[indices[i]].i, // joint index
				sorted[indices[i]].w // joint weight
			});
	}
	mesh.gen();
	buffer(finalbuffer);
	mesh.attrib(0, 3, 17, 0);
	mesh.attrib(1, 3, 17, 3);
	mesh.attrib(2, 3, 17, 6);
	mesh.attrib(3, 2, 17, 9);
	mesh.attribI(4, 3, 17, 11);
	mesh.attrib(5, 3, 17, 14);
	mesh.size = finalbuffer.size();

	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, home.size() * 64, home.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
}

void model::update()
{
	t += clock::dt;
	if (t > len) t -= len;
	arm.applyPose(anim, t);
}

void model::draw()
{
	if(animated) update();
	mesh.bind();
	glNamedBufferSubData(ssbo, 0, home.size() * 64, home.data());
	glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}