#version 460
layout (location = 0) in vec4 v;
layout (location = 1) in vec3 n;
layout (location = 2) in vec2 t;
layout (location = 3) in vec4 c;
out vec2 tex;
out vec4 col;
uniform mat4 prj;
uniform mat4 view;
uniform mat4 xform;
void main() 
{
	gl_Position = prj * view * xform * v;
	tex = vec2(t.x, 1 - t.y);
	col = vec4(1);
	if(length(c) > 1.f) col = c;
}