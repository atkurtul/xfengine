#pragma once
#include "xml_parser.h"
#include "base.h"

struct frame
{
    xfvec<float> input;
    xfvec<mat4>  output;
    mat4* getPoseAt(float t) const;
};

struct animation
{
    xfmap<uint, frame> frames;
    float len = 0.f;
    float t = 0.f;
    void update();
};

struct bone
{
    bone* parent;
    xfvec<bone*> children;
    mat4 inv;
    mat4& anim;
    mat4 bind;
    uint id;
    xfstr name;
    bone(uint id, xfstr name, const mat4& inv, mat4& anim, const mat4& bind) 
        : id(id), name(name), inv(inv), anim(anim), bind(bind) {}
    void setPose(const animation& animation, const mat4& parentxf);
};


struct model
{
    xfvec<bone*> bones;
    xfvec<mat4> xforms;
    animation anim;
    vao mesh;
    model(const char* path);
    void draw();

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
    void update();
    void handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv);
    xfvec<vweight> sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v);

};
