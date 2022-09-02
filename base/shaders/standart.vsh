#version 460
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 texture_coords;
out vec3 color;
out vec2 t_coord;
void main() {
    t_coord = texture_coords;
    color = vertex_color;
    gl_Position = vec4(vertex_pos, 1.);
}