#include "xfstd.h"

struct xml_node
{
    xfstr name;
    xfstr data;
    xml_node* parent = nullptr;
    xfmap<xfstr, xfstr> attribs;
    xfmap<xfstr, xfvec<xml_node*>> children;
  
    xfvec<xfstr> readDataAsStr();
    template<class T>
    xfvec<T> readDataAs();
    template<class T, uint n>
    xfvec<vec<T, n>> readDataAsVec();
    template<class T>
    xfvec<matrix4<T>> readDataAsMat4();

    xml_node();
    xml_node(xfstr node);
    void addChild(xml_node* n);
    int childCount();
    xfvec<xml_node*> getChildren(const xfstr& cname);
    xfvec<xml_node*> getChildren(const xfstr& cname, const xfstr& key, const xfstr& val);
    xml_node* getChild(const xfstr& name);
    xml_node* getChild(const xfstr& cname, const xfstr& key, const xfstr& val);
    xml_node* getDescendant(const xfstr& cname);
    xml_node* getDescendant(const xfstr& cname, const xfstr& key, const xfstr& val);

};

struct xml_parser
{
    xml_node root;
    xml_parser(const char* path);
};
