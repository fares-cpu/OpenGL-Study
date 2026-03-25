#include <iostream>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "stb_image.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "FPScamera.hpp"
#include "orbitCamera.hpp"


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
Camera* camera = new FPSCamera();
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



int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int GL_WIDTH = 800, GL_HIGHT = 600;
	GLFWwindow* window = glfwCreateWindow(GL_WIDTH, GL_HIGHT, "OpenGL - DA", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);



	//buffer data ---------------------------------------------------------------------------------------------
	float vertices[] = {
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
	
	unsigned int indices[] = {
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
//--------------------------------------------------------------------------------------------------------------------------------
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//---------------------------------------------------- Light Vertex Array ------------------------------------------------------------
	
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//==========================================================================================================================
	
	Shader shader("vertex.glsl", "fragment.glsl");
	Shader lightShader("vertex.glsl", "lightCubeFragment.glsl");
	
	//textures
	//----------------------------------------------------------------------------------------------------------------------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	const char* texpath = "C:\\Users\\knightu\\Desktop\\cpp\\openGL - DA\\OpenGL-Study\\OpenGL-Study\\res\\wall.jpg";
	int width, hight, nrchannels;
	unsigned char* data = stbi_load(texpath, &width, &hight, &nrchannels, NULL);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, hight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------

	//transformation
	glm::mat4 model(1.0f);
	//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	int projectionLoc = glGetUniformLocation(shader.ID, "projection");

	int lightmodelLoc = glGetUniformLocation(lightShader.ID, "model");
	int lightviewLoc = glGetUniformLocation(lightShader.ID, "view");
	int lightprojectionLoc = glGetUniformLocation(lightShader.ID, "projection");

	//--------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------- light model --------------------------------------------------------
	
	glm::mat4 light_Base(1.0f);
	glm::mat4 lightModel(1.0f);
	glm::vec3 lightPosition(0.0f, 0.0f, 0.0f);
	
	light_Base = glm::scale(light_Base, glm::vec3(0.1f));
	


	//----------------------------------------------------------------------------------------------------------
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	while (!glfwWindowShouldClose(window)) {
		// calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << 1/deltaTime;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//handle input
		process_input(window);

		//draw cube (wall cube)
				//texture phase
		shader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->perspective()));
		glm::vec3 camPos = camera->getPosition();
		shader.set_vec3("viewPos", camPos.x, camPos.y, camPos.z);
		shader.set_vec3("lightPos", lightPosition.x, lightPosition.y, lightPosition.z);
		shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
				//draw phase
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//draw light source
				//manipulate light
		
		glm::mat4 orbit(1.0f);
		orbit = glm::rotate(orbit, (float)glfwGetTime(), glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)));
		orbit = glm::translate(orbit, glm::vec3(2.0f, 0.0f, 0.0f));
		//lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));


		lightModel = orbit * light_Base;
		lightPosition = lightModel[3];
			//shader phase
		
		lightShader.use();
		glUniformMatrix4fv(lightviewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(lightprojectionLoc, 1, GL_FALSE, glm::value_ptr(camera->perspective()));
		glUniformMatrix4fv(lightmodelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
		

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		system("cls");
	}
	glfwTerminate();
	return 0;


}