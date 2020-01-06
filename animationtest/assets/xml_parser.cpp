#include "xml_parser.h"

xml_node::~xml_node()
{
	for (auto& p : children)
		for (auto* pp : p.v)
			delete pp;
}

xml_node::xml_node(const xfstr& Line) :
	parent(nullptr)
{
	xfstr line = Line.inbtwn('<', '>');
	if (line.find(' '))
	{
		name = line.exbtwn('<', ' ');
		xfstr rest = line.exbtwn(' ', '>');
		while (rest.find(' '))
		{
			xfstr attrib = rest.inbtwn(*rest.begin(), ' ');
			attrib.erase(attrib.end());
			addAtrib(attrib);
			rest.erase(rest.find(' '), rest.rend());
		}

		addAtrib(rest);
	}
	else name = line.exbtwn('<', '>');
	xfstr rest = Line.substr(line.find('>') - line.begin() + 1);
	if (rest.size() > 0)
	{
		while (*rest.begin() == ' ' || *rest.begin() == 9) rest.erase(rest.begin());
		char* c = rest.find('<');
		if (c) rest.erase(c, rest.end());
		while (*rest.rbegin() == ' ' || *rest.rbegin() == 9) rest.erase(rest.rbegin());
		data = rest;
	}
}

void xml_node::addAtrib(const xfstr& attrib)
{
	attribs[attrib.substr(0, attrib.find('=') - attrib.begin())]
		= attrib.exbtwn('"', '"');
}

xml_node* xml_node::addChild(const xfstr& line)
{
	xml_node* child = new xml_node(line);
	child->parent = this;
	auto* c = children.find(child->name);
	if (c)
	{
		c->push(child);
	}
	else
	{
		children[child->name] = { child };
	}
	if (line.find("/>") || line.find("</")) return this;
	return child;
}

xfvec<xfstr> xml_node::readDataAsStr()
{
	xfstr arr = data;
	xfvec<xfstr> re;
	while (arr.find(' '))
	{
		re.push(arr.substr(0, arr.find(' ') - arr.begin()));
		arr.erase(arr.find(' '), arr.rend());
	}
	re.push((xfstr&&)arr);
	return re;
}

xfvec<xml_node*> xml_node::getChildren(const xfstr& cname)
{
	return children[cname];
}

xfvec<xml_node*> xml_node::getChildrenByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val)
{
	xfvec<xml_node*> re;
	xfvec<xml_node*> search = children[cname];
	for (xml_node* n : search)
	{
		auto a = n->attribs.find(key);
		if (a) if (*a == val || a->find(val)) re.push(n);
	}
	return re;
}

xml_node* xml_node::getChild(const xfstr& cname)
{
	auto* c = children.find(cname);
	if (c) return c->front();
	return 0;
}

xml_node* xml_node::getChildByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val)
{
	auto* c = children.find(cname);
	if (c) {
		for (xml_node* n : *c)
		{
			auto* a = n->attribs.find(key);
			if (a)
				if (*a == val || a->find(val)) return n;
		}
	}
	return 0;
}

xml_node* xml_node::getDescendant(const xfstr& cname)
{
	auto* c = getChild(cname);
	if (c) return c;
	for (auto& p : children)
	{
		for (auto& pp : p.v)
		{
			c = pp->getDescendant(cname);
			if (c) return c;
		}
	}
	return 0;
}

xml_node* xml_node::getDescendantByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val)
{
	auto* c = getChildByAttrib(cname, key, val);
	if (c) return c;
	for (auto& p : children)
	{
		for (auto& pp : p.v)
		{
			c = pp->getDescendantByAttrib(cname, key, val);
			if (c) return c;
		}
	}
	return 0;
}

xml_node* xml_node::getSibling(const xfstr& cname)
{
	if (parent)
		return parent->getChild(cname);
	return 0;
}

xml_node* xml_node::getSiblingbyAttrib(const xfstr& cname, const xfstr& key, const xfstr& val)
{
	if (parent)
		return parent->getChildByAttrib(cname, key, val);
	return 0;
}

uint xml_node::childrenCount()
{
	uint c = 0;
	for (auto& p : children)
		c += p.v.size();
	return c;
}

xml_parser::xml_parser(const char* path)
{
	std::ifstream s(path);
	xfstr line;
	line.getline(s);
	root = line;
	xml_node* c = &root;
	while (line.getline(s))
	{
		if (line.empty()) continue;
		while (line[0] == ' ' || line[0] == 9) line.erase(line.begin());
		if (*(line.begin() + 1) == '/')
			c = c->parent;
		else if (*line.begin() == '<')
			c = c->addChild(line);
	}
	s.close();
}
