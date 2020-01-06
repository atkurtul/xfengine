#version 460
out vec4 fragcolor;
in vec4 col;
in vec2 tex;
uniform sampler2D Texture;
void main() {
	fragcolor = texture(Texture, tex) * col;
}