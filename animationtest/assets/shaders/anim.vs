#version 460
layout (location = 0) in vec4 v;
layout (location = 1) in vec3 n;
layout (location = 2) in vec2 t;
layout (location = 3) in uvec3 j;
layout (location = 4) in vec3 w;
out vec2 tex;

uniform mat4 prj;
uniform mat4 view;
uniform mat4 xform;

mat3 toMat3(in vec4 q);

uniform mat4 bones[50];

void main() 
{
	vec4 pos = 
	(v * bones[j.x]) * w.x + 
	(v * bones[j.y]) * w.y + 
	(v * bones[j.z]) * w.z;
	gl_Position = prj * view * xform * pos;
	tex = vec2(t.x, 1 - t.y);
}

mat3 toMat3(in vec4 q)
{
	float i2 = q.x + q.x, j2 = q.y + q.y, k2 = q.z + q.z;
	float ii = q.x * i2, ij = q.x * j2, ik = q.x * k2;
	float jj = q.y * j2, jk = q.y * k2, kk = q.z * k2;
	float si = q.w * i2, sj = q.w * j2, sk = q.w * k2;
	return mat3( 1 - (jj + kk),	ij - sk, ik + sj, 
				ij + sk, 1 - (ii + kk), jk - si, 
				ik - sj, jk + si,	1 - (ii + jj));
}