#version 330

in float vCol;

out vec3 colour;

void main()	
{
	vec3 rampCol = vec3(vCol, vCol, vCol);

	vec3 finalColour = rampCol * vec3(rampCol.x * 0.3f, rampCol.y, 1.0f);

	colour = vec3(0.7f, 0.3f, 1.0f) - finalColour;
}