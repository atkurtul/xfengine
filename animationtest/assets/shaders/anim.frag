#version 460
out vec4 fragcolor;
in vec2 tex;
uniform sampler2D Texture;
void main() {
	fragcolor = texture(Texture, tex);
}