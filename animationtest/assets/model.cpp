#include "model.h"
#include "xfstd.h"
model::model(const char* path)

{
	xml_parser p(path);


	//geometry
	auto vertices = p.root.getDescendant("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
	auto normals = p.root.getDescendant("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
	auto textures = p.root.getDescendant("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
	uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
	auto indices = p.root.getDescendant("p")->readDataAs<uint>();

	//controllers
	auto namearray = p.root.getDescendant("Name_array", "id", "skin-joints-array")->readDataAsStr();
	auto invbinds = p.root.getDescendant("float_array", "id", "skin-bind_poses-array")->readDataAsMat4<float>();
	auto weights = p.root.getDescendant("float_array", "id", "skin-weights-array")->readDataAs<float>();
	auto vcount = p.root.getDescendant("vcount")->readDataAs<uint>();
	auto vs = p.root.getDescendant("v")->readDataAs<uint>();
	auto sorted = sortWeights(weights, vcount, vs);


	//bones
	home.resize(namearray.size());
	auto root = p.root.getDescendant("node", "id", "Armature");
	xform = root->getChild("matrix")->readDataAsMat4<float>().front();
	auto bonenodes = root->getChildren("node", "type", "JOINT");
	for (xml_node* n : bonenodes)
	{
		xfstr xid = n->attribs["id"];
		int id = namearray.find(xid.substr(9)) - namearray.begin();
		bone* b = new bone(id, invbinds[id], home[id]);
		bones.push(b);
		auto children = n->getChildren("node", "type", "JOINT");
		for (xml_node* n : children)
			addChildren(b, n, namearray, invbinds, home);
	}

	//animation
	auto animroot = p.root.getDescendant("animation", "id", "action_container");
	for (xfstr& n : namearray)
	{
		auto q = animroot->getDescendant("float_array", "id", n + "_pose_matrix-input-array");
		if (q)
		{
			uint id = &n - namearray.begin();
			auto in = q->readDataAs<float>();
			auto out = animroot->getDescendant("float_array", "id", n + "_pose_matrix-output-array")->readDataAsMat4<float>();
			frame f;
			for (int i = 0; i < in.size(); ++i)
			{
				float t = in[i];
				f[t] = out[i];
				if (t > anim.len) anim.len = t;
			}
			anim[id] = f;
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

void model::addChildren(bone* parent, xml_node* node, xfvec<xfstr>& namearray, xfvec<mat4>& invbinds, xfvec<mat4>& home)
{
	int id = namearray.find(node->attribs["id"].ref().substr(9)) - namearray.begin();
	bone* b = new bone(id, invbinds[id], home[id]);
	b->parent = parent;
	parent->children.push(b);
	auto bonenodes = node->getChildren("node", "type", "JOINT");
	for (xml_node* n : bonenodes)
		addChildren(b, n, namearray, invbinds, home);
}

xfvec<model::vweight> model::sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v)
{
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
}

void model::draw()
{
	anim.update();
	mesh.bind();
	glNamedBufferSubData(ssbo, 0, home.size() * 64, home.data());
	glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}

void animation::update()
{
	t += clock::dt;
	if (t > len) t -= len;

	for (bone* b : m.bones)
	{
		mat4 xf = operator[](b->id).ref().getFrameAt(t);
		b->xform = xf * b->inv;
		applyPose(b->children, xf);
	}
}


void animation::applyPose(xfvec<bone*>& v, const mat4& parentxf)
{
	for (bone* b : v)
	{
		mat4 xf = operator[](b->id).ref().getFrameAt(t);
		b->xform = parentxf * xf * b->parent->inv;
		applyPose(b->children, parentxf * xf);
	}
}

mat4 frame::getFrameAt(float t) const
{
	for (auto& a : data)
		if (a.k >= t) return a.v;
	return m4id;
}