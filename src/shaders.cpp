#include "shaders.h"

#include <string>

std::string shaders::pyramid_vShader = R"(
#version 330

layout (location = 0) in vec3 pos;

out float vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = clamp(pos.y, -1.0f, 1.0f);
})";
std::string shaders::pyramid_fShader = R"(
#version 330

in float vCol;

out vec3 colour;

void main()	
{
	colour = vec3(vCol, vCol, vCol);
})";