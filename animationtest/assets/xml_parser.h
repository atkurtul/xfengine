#pragma once
#include "xfstd.h"

struct xml_node
{
	xml_node* parent;
	xfmap<xfstr, xfvec<xml_node*>> children;
	xfmap<xfstr, xfstr> attribs;
	xfstr name;
	xfstr data;
	~xml_node();
	xml_node() : parent(nullptr) {}
	xml_node(const xfstr& Line);
	void addAtrib(const xfstr& attrib);
	xml_node* addChild(const xfstr& line);

	template<class T>
	xfvec<T> readDataAs();
	template<class T, uint n>
	xfvec<vec<T, n>> readDataAsVec();
	template<class T>
	xfvec<matrix4<T>> readDataAsMat4();
	xfvec<xfstr> readDataAsStr();

	xfvec<xml_node*> getChildren(const xfstr& cname);
	xfvec<xml_node*> getChildrenByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val);
	xml_node* getChild(const xfstr& cname);
	xml_node* getChildByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val);
	xml_node* getDescendant(const xfstr& cname);
	xml_node* getDescendantByAttrib(const xfstr& cname, const xfstr& key, const xfstr& val);

	xml_node* getSibling(const xfstr& cname);
	xml_node* getSiblingbyAttrib(const xfstr& cname, const xfstr& key, const xfstr& val);
	uint childrenCount();
};

struct xml_parser
{
	xml_node root;
	xml_parser(const char* path);
};

template<class T>
inline xfvec<T> xml_node::readDataAs()
{
	xfstr arr = data;
	xfvec<T> re;
	while (arr.size() > 0)
	{
		re.emplace(0);
		arr >> re.back();
	}
	return re;
}

template<class T, uint n>
inline xfvec<vec<T, n>> xml_node::readDataAsVec()
{
	xfstr arr = data;
	xfvec<vec<T, n>> re;
	while (arr.size() > 0)
	{
		re.push({});
		for (int i = 0; i < n; ++i) arr >> re.back()[i];
	}
	return re;
}

template<class T>
inline xfvec<matrix4<T>> xml_node::readDataAsMat4()
{
	return (xfvec<matrix4<T>>&)readDataAsVec<float, 16>();
}

