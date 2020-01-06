#pragma once
#include "xml_parser.h"
#include "base.h"

struct frame
{
    xfvec<float> input;
    xfvec<mat4> output;
    mat4* getPoseAt(float t) const;
};

struct animation
{
    xfmap<uint, frame> frames;
    float len = 0.f;
    mutable float t = 0.f;
    void update() const;
};

struct bone
{
    uint id;
    bone* parent;
    xfvec<bone*> children;
    mat4& inv;
    mat4& anim;
    mat4& bind;
    xfstr& name;
    bone(uint id, xfstr& name, mat4& inv, mat4& anim, mat4& bind)
        : parent(nullptr), id(id), name(name), inv(inv), anim(anim), bind(bind) {}
    void setPose(const animation& animation, const mat4& parentxf);

};

struct model
{
    vao mesh;
    mat4 xform;
    model(const char*);
    void draw();
};

struct a_model
{
    vao mesh;
    mat4 xform;
    xfvec<bone*> bones;
    xfvec<mat4>  xforms;
    xfvec<xfstr> namearray;
    xfvec<mat4>  invbinds;
    xfvec<mat4>  binds;
    xfvec<animation> animations;
    uint activeAnimation = 0;
    a_model(const char* model);
    void update();
    void draw();
    void handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv);
    void addAnim(const char* path);
    xfvec<xfcouple<uvec3, vec3>> sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v);
};