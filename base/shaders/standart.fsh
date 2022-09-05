#version 460
in vec2 t_coord;
out vec4 frag_color;

uniform sampler2D sampler0;
void main() {
    frag_color = texture(sampler0, t_coord);
}