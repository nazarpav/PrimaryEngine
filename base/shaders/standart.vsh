#version 460
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec2 texture_coords;
out vec3 color;
out vec2 t_coord;
uniform mat4 model_mat;
uniform mat4 projection_mat;
void main() {
    t_coord = texture_coords;
    vec4 a_vertex = projection_mat * model_mat * vec4(vertex_pos, 1.);
    gl_Position = a_vertex;
}