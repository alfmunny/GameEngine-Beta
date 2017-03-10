#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 vertexUV;
out vec3 Color;
out vec2 UV;

uniform mat4 pr_matrix = mat4(1.0); // projection matrix
uniform mat4 vw_matrix = mat4(1.0); // view matrix
uniform mat4 ml_matrix = mat4(1.0); // model matrix
uniform mat4 trans = mat4(1.0); // model matrix
uniform mat4 rotate = mat4(1.0); // model matrix
uniform mat4 scale = mat4(1.0); // model matrix

void main()
{
    gl_Position = pr_matrix * vw_matrix * trans * rotate * scale * vec4(Position, 1.0);
    //Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
    UV = vertexUV;
}