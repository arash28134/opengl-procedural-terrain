// system libraries
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

// glew library
#include <GL/glew.h>

// glfw library
#include <GLFW/glfw3.h>

// glm libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, identity
#include <glm/gtc/type_ptr.hpp>

// user defined base libraries
#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "shaders.h"
#include "camera.h"

// user defined util libraries
#include "mesh_utils.h"
#include "anim_utils.h"

#include "FastNoiseLite.h"

// namespaces
using namespace std;

// main window
Window mainWindow;

// main camera
camera mainCamera;

// delta variables
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// list of meshes
std::vector<Mesh*> meshList;

// list of shaders
std::vector<Shader> shaderList;

// pyramid current angle animation variable
float pyramid_curAngle = 0.0f;

// settings
int width = 1000;
int height = 1000;

// functions
void CreateMeshes();
void CreateShaders();

int main()
{
	// // Gather noise data
	// std::vector<float> noiseData(128 * 128);

	// int index = 0;

	// for (int y = 0; y < 128; y++)
	// {
	// 	for (int x = 0; x < 128; x++)
	// 	{
	// 		noiseData[index++] = noise.GetNoise((float)x, (float)y);
	// 	}
	// }

	// for (float i: noiseData)
	// 	cout << i << endl;

	// initialize the main window
	mainWindow.initialize();

	CreateMeshes();
	CreateShaders();

	// initialize main camera
	mainCamera = camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 4.0f, 0.5f, 3.7f);

	// uniform variables
	GLuint uniformModel, uniformProjection, uniformView;

	// perspective projection, used for rendering 3d scenes
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	// Loop until windows closed
	while (!mainWindow.getShouldClose())
	{
		// deltatime calculations
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// get and handle user inputs
		glfwPollEvents();

		// control key press
		mainCamera.keyControl(mainWindow.getKeys(), deltaTime);

		// control mouse movements
		mainCamera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// clear the window with black color. we can set this to any rgba value (between 0 and 1)
		// and get a different color. for instance we could say:
		// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// and we'd have the blue color as our screen color (we'd see a blue color around the pyramid)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// use pyramid shader's program
		shaderList[0].UseShader();

		// set uniform variables to uniform locations in shader
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();

		// draw rotating animation for pyramid
		// anim_utils::DrawRotatingAnim(&pyramid_curAngle, 0.5f);

		// identity matrix
		glm::mat4 model = glm::mat4(1.0f);

		// apply translate, scale and rotation to identity matrix
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, glm::radians(pyramid_curAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		// set uniform variables using their uniform address
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.calculateViewMatrix()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		// render all meshes
		mesh_utils::RenderMeshList(meshList);

		glUseProgram(0);

		// swap main window's buffers. this is a very important part of render loop which is done
		// at the end
		mainWindow.swapBuffers();
	}

	return 0;
}

void CreateMeshes(){
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    vector<GLfloat> vertices;
	vector<int> indices;

	// Create vertices
    vertices.reserve(width * height);
    float spacing = 1.0;
	
    // Rows
    for (int r = 0; r < height; r++) {
        // Cols
        for (int c = 0; c < width; c++) {
            // NOTE: origin is not at center of mesh
            float x = c; // col
            float z = r; // row
            float y = noise.GetNoise((float)c, (float)r) * 10.0f;
			cout << y << endl;
            // glm::vec3 v(x * spacing, y * spacing, z); //
            vertices.push_back(x * spacing);
			vertices.push_back(y * spacing);
			vertices.push_back(z);
        }
    }

	// Generate faces

    // Rows (-1 for last)
    for (int r = 0; r < height - 1; r++) {
        // Cols (-1 for last)
        for (int c = 0; c < width - 1; c++) {
            // Upper triangle
            /*

                v0 -- v2
                |    /
                |  /
                v1
            */
            int f0_0 = (r * width) + c;
            int f0_1 = ((r + 1) * width) + c;
            int f0_2 = (r * width) + c + 1;

            indices.push_back(f0_0);
			indices.push_back(f0_1);
			indices.push_back(f0_2);

            // Lower triangle
            /*

                      v2
                     / |
                   /   |
                v0 --- v1
            */
            int f1_0 = ((r + 1) * width) + c;
            int f1_1 = ((r + 1) * width) + c + 1;
            int f1_2 = (r * width) + c + 1;

            indices.push_back(f1_0);
			indices.push_back(f1_1);
			indices.push_back(f1_2);
        }
    }

	// for (int i: indices)
	// 	cout << i << endl;

	// create a new object of mesh class (pyramid) and make a pointer to it
	Mesh* pyramid = new Mesh();
	pyramid->CreateMesh(vertices, indices);

	// add mesh (pyramid) to the mesh list
	meshList.push_back(pyramid);
}

void CreateShaders()
{
	// create a new object of shader class (pyramid's shader) and make a pointer to it
	Shader* pyramid_shader = new Shader();
	pyramid_shader->CreateProgram(shaders::pyramid_vShader, shaders::pyramid_fShader);

	// add it to the shader list
	shaderList.push_back(*pyramid_shader);
}