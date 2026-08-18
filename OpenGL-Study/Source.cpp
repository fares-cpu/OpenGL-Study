#include <iostream>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include "FPScamera.hpp"
#include "orbitCamera.hpp"
#include "Texture.hpp"
#include <assimp/Importer.hpp>


float vertices[288] = {
	//			posistions					  normals			text coords
			-0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,	   -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	   -1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	   -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	   -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	   -1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	   -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		0.0f, 1.0f



};

unsigned int indices[36] = {
	//front face
	0, 1, 3,
	1, 2, 3,
	//upper face
	0, 3, 4,
	3, 4, 7,
	//left face
	2, 3, 7,
	2, 6, 7,
	//right face
	0, 1, 4,
	1, 4, 5,
	//down face
	1, 2, 5,
	2, 5, 6,
	//back face
	4, 5, 6,
	4, 6, 7,

};

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct Mesh {
	unsigned int VAO; //vertex array object
	unsigned int VBO; //vertex buffer object
	unsigned int EBO; //element buffer object

	Mesh() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

	}

	void draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int hight) {
	glViewport(0, 0, width, hight);
}

bool isDragging = false;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			isDragging = true;
		}
		else if (action == GLFW_RELEASE) {
			isDragging = false;
		}
	}
}

bool first_mouse = true;
Camera* camera = new FPSCamera ();
float lastX, lastY;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset, yoffset;
	if (first_mouse) {
		lastX = xpos;
		lastY = ypos;
		first_mouse = false;
	}
	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	camera->processMouseInput(xoffset, yoffset, isDragging);
}

float deltaTime = 0.0f; 
float lastFrame = 0.0f;
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		/*GLint polymode[2];
		glGetIntegerv(GL_POLYGON_MODE, polymode);
		if (polymode[0] == GL_LINE && polymode[1]== GL_LINE) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if(polymode[0] == GL_FILL && polymode[1]==GL_FILL) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboardInput('w', deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->processKeyboardInput('s', deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->processKeyboardInput('a', deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->processKeyboardInput('d', deltaTime);
	}
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera->processMouseScroll((float)yoffset, deltaTime);
}



GLFWwindow* window;
Material ruby;
Light light;
void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int GL_WIDTH = 800, GL_HIGHT = 600;
	window = glfwCreateWindow(GL_WIDTH, GL_HIGHT, "OpenGL - DA", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
		exit(-1);
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);

}



int main() {
	init();
	
	Mesh mesh = Mesh();

	Shader lightShader("vertex.glsl", "lightCubeFragment.glsl");
	Shader shader_texPro("vertex.glsl", "lights.glsl");
	
	
	Texture diffuseMap("C:\\Users\\knightu\\Desktop\\cpp\\openGL - DA\\OpenGL-Study\\OpenGL-Study\\res\\container2.png");
	Texture specularMap("C:\\Users\\knightu\\Desktop\\cpp\\openGL - DA\\OpenGL-Study\\OpenGL-Study\\res\\container2_specular.png");

	//transformation
	glm::mat4 model(1.0f);

	glm::mat4 light_Base(1.0f);
	glm::mat4 lightModel(1.0f);
	glm::vec3 lightPosition(0.0f, 0.0f, 0.0f);
	
	light_Base = glm::scale(light_Base, glm::vec3(0.1f));

	shader_texPro.use();
	shader_texPro.set_int("material.diffuse", 0);
	shader_texPro.set_int("material.specular", 1);
	shader_texPro.set_float("material.shininess", 64);
	
	// directional light
	shader_texPro.set_vec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader_texPro.set_vec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader_texPro.set_vec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader_texPro.set_vec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	shader_texPro.set_vec3("pointLights[0].position", pointLightPositions[0]);
	shader_texPro.set_vec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	shader_texPro.set_vec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	shader_texPro.set_vec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	shader_texPro.set_float("pointLights[0].constant", 1.0f);
	shader_texPro.set_float("pointLights[0].linear", 0.09f);
	shader_texPro.set_float("pointLights[0].quadratic", 0.032f);
	// point light 2
	shader_texPro.set_vec3("pointLights[1].position", pointLightPositions[1]);
	shader_texPro.set_vec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	shader_texPro.set_vec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	shader_texPro.set_vec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	shader_texPro.set_float("pointLights[1].constant", 1.0f);
	shader_texPro.set_float("pointLights[1].linear", 0.09f);
	shader_texPro.set_float("pointLights[1].quadratic", 0.032f);
	// point light 3
	shader_texPro.set_vec3("pointLights[2].position", pointLightPositions[2]);
	shader_texPro.set_vec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	shader_texPro.set_vec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	shader_texPro.set_vec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	shader_texPro.set_float("pointLights[2].constant", 1.0f);
	shader_texPro.set_float("pointLights[2].linear", 0.09f);
	shader_texPro.set_float("pointLights[2].quadratic", 0.032f);
	// point light 4
	shader_texPro.set_vec3("pointLights[3].position", pointLightPositions[3]);
	shader_texPro.set_vec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	shader_texPro.set_vec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	shader_texPro.set_vec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	shader_texPro.set_float("pointLights[3].constant", 1.0f);
	shader_texPro.set_float("pointLights[3].linear", 0.09f);
	shader_texPro.set_float("pointLights[3].quadratic", 0.032f);
	// spotLight
	
	shader_texPro.set_vec3("flashLight.ambient", 0.0f, 0.0f, 0.0f);
	shader_texPro.set_vec3( "flashLight.diffuse", 0.5f, 0.5f, 0.5f);
	shader_texPro.set_vec3( "flashLight.specular", 2.0f, 2.0f, 2.0f);
	shader_texPro.set_float("flashLight.constant", 1.0f);
	shader_texPro.set_float("flashLight.linear", 0.09f);
	shader_texPro.set_float("flashLight.quadratic", 0.032f);
	shader_texPro.set_float("flashLight.cutoff", glm::cos(glm::radians(12.0f)));
	shader_texPro.set_float("flashLight.outerCutoff", glm::cos(glm::radians(15.0f)));


	while (!glfwWindowShouldClose(window)) {
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cout << 1/deltaTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		process_input(window);

		glm::mat4 orbit(1.0f);
		orbit = glm::rotate(orbit, (float)glfwGetTime(), glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)));
		orbit = glm::translate(orbit, glm::vec3(2.0f, 0.0f, 0.0f));

		glm::mat4 trans(1.0f);
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, (float)glfwGetTime()/1.7));

		lightModel = orbit * light_Base;
		light.position = lightModel[3];


		//shader texture pro
		shader_texPro.use();
		shader_texPro.set_mat4("model", model);
		shader_texPro.set_mat4("view", camera->GetViewMatrix());
		shader_texPro.set_mat4("projection", camera->perspective());
		shader_texPro.set_vec3("viewPos", camera->getPosition());
		shader_texPro.set_vec3("flashLight.position", camera->getPosition());
		shader_texPro.set_vec3("flashLight.direction", camera->getFront());
		


		glActiveTexture(GL_TEXTURE0);
		diffuseMap.bind();
		glActiveTexture(GL_TEXTURE1);
		specularMap.bind();

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader_texPro.set_mat4("model", model);

			mesh.draw();
		}
		
		mesh.draw();
		
		lightShader.use();
		lightShader.set_mat4("model", lightModel);
		lightShader.set_mat4("view", camera->GetViewMatrix());
		lightShader.set_mat4("projection", camera->perspective());
		
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightShader.set_mat4("model", model);
			mesh.draw();
		}
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		//system("cls");
	}
	glfwTerminate();
	return 0;


}