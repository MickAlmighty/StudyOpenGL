#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Model.h>
#include <GraphNode.h>
#include <Mesh.h>
#include <Camera.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat deltaTime = 0.0f; // Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹  
GLfloat lastFrame = 0.0f; // Czas ostatniej ramki
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = SCR_WIDTH / 2.0f;
GLfloat lastY = SCR_HEIGHT / 2.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	    // Setup window
	    glfwSetErrorCallback(glfw_error_callback);
	    if (!glfwInit())
	        return 1;
	
	    // Decide GL+GLSL versions
	#if __APPLE__
	    // GL 3.2 + GLSL 150
	    const char* glsl_version = "#version 150";
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
	#else
	    // GL 4.3 + GLSL 430
	    const char* glsl_version = "#version 430";
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSwapInterval(1); // Enable vsync
	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	srand(static_cast <unsigned> (time(0)));
	// build and compile our shader zprogram
	// ------------------------------------
	Shader* ourShader = new Shader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shaderPBR.frag");
	//Shader* ourShader = new Shader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.fs");
	Shader* ourShader2 = new Shader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader2.fs");
	
	bool PBR = true;

	Model* ourModel = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\nanosuit\\nanosuit.obj");
	Model* ourModel2 = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\chair\\Armchair Quinti Amelie.3ds");
	Model* nanosuit = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\nanosuit\\nanosuit.obj");
	Model* lightBox = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\lightBox\\LightBox.fbx");
	Model* latarka = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\lightBox\\LightBox.fbx");
	Model* latarka2 = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\lightBox\\LightBox.fbx");
	Model* grass = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\Rockwall.fbx");
	
	ourModel->SetShader(ourShader);
	ourModel2->SetShader(ourShader);
	nanosuit->SetShader(ourShader);
	lightBox->SetShader(ourShader2);
	latarka->SetShader(ourShader2);
	grass->SetShader(ourShader);
	latarka2->SetShader(ourShader2);
	GraphNode root(true);
	GraphNode* lightB = new GraphNode(true, lightBox);
	GraphNode* spotLight = new GraphNode(true, latarka);
	GraphNode* sun = new GraphNode(true, ourModel);
	GraphNode* sun2 = new GraphNode(true, nanosuit);
	GraphNode* floor = new GraphNode(true, grass);
	GraphNode* pointLightPivot = new GraphNode(true, new Model());
	GraphNode* spotLight2 = new GraphNode(true, latarka2);

	root.AddChild(sun);
	root.AddChild(sun2);
	root.AddChild(pointLightPivot);
	pointLightPivot->AddChild(lightB);
	lightB->Translate(glm::vec3(-10.0f, 1, 0));


	root.AddChild(spotLight);
	root.AddChild(spotLight2);
	root.AddChild(floor);

	
	sun->Translate(glm::vec3(0.0f, -1.75f, 0.0f));
	sun->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

	//moon->Translate(glm::vec3(15, 0, 0));
	sun2->Scale(glm::vec3(0.15, 0.15, 0.15));
	sun2->Translate(glm::vec3(-12, -15, -3));
	sun2->Rotate(30, glm::vec3(0, 1, 0));
	floor->Translate(glm::vec3(0, -2, 0));
	floor->Scale(glm::vec3(0.01f, 0.01f, 0.01f));


	glm::mat4 view(1);
	glm::mat4 projection(1);
	bool isWireframeModeActive = false;
	float x_axis = 1.0f;
	float y_axis = 0.0f;
	float metallines = 0.5f, roughness = 0.1f, ao = 0.05f;
	glm::vec3 lightAmbient(0.2f, 0.2f, 0.8f);
	glm::vec3 lightDiffuse(0.5f, 0.5f, 0.5f);
	glm::vec3 lightSpecular(1.0f, 1.0f, 1.0f);
	glm::vec3 lightDirection(0.0f, 1.0f, 0.0f);
	float slPosX = -1.3f, slPosY = -0.84f, slPosZ = 0.84f;
	float slPosX1 = 1.485f, slPosY1 = -0.89f, slPosZ1 = 1.683f;
	glm::vec3 spotLightDirection(0.5f, 0.02f, -0.34f);
	glm::vec3 spotLightDirection1(-0.89f, -0.792f, -1.683f);

	glEnable(GL_PROGRAM_POINT_SIZE);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Hello, world!");
			ImGui::Text("Pozycja œwiat³a punktowego");
			ImGui::SliderFloat("x", &x_axis, -10.0f, 10.0f);
			ImGui::SliderFloat("y", &y_axis, -10.0f, 10.0f);
			ImGui::ColorEdit3("Ambient Light", (float*)&lightAmbient); // Edit 3 floats representing a color
			ImGui::ColorEdit3("Diffuse Light", (float*)&lightDiffuse);
			ImGui::ColorEdit3("Specular Light", (float*)&lightSpecular);
			ImGui::Text("DirLight light direction");
			ImGui::SliderFloat("x-direction", &lightDirection.x, -1.0f, 1.0f);
			ImGui::SliderFloat("y-direction", &lightDirection.y, 0.0f, 1.0f);
			ImGui::SliderFloat("z-direction", &lightDirection.z, -1.0f, 1.0f);
			ImGui::Text("Pozycja reflektora_1");
			ImGui::SliderFloat("pos_x", &slPosX, -10.0f, 10.0f);
			ImGui::SliderFloat("pos_y", &slPosY, -10.0f, 10.0f);
			ImGui::SliderFloat("pos_z", &slPosZ, -10.0f, 10.0f);
			ImGui::Text("Kierunek swiatla reflektora_1");
			ImGui::SliderFloat("dirX", &spotLightDirection.x, -10.0f, 10.0f);
			ImGui::SliderFloat("dirY", &spotLightDirection.y, -10.0f, 10.0f);
			ImGui::SliderFloat("dirZ", &spotLightDirection.z, -10.0f, 10.0f);
			ImGui::Text("Pozycja reflektora_2");
			ImGui::SliderFloat("pos_x1", &slPosX1, -10.0f, 10.0f);
			ImGui::SliderFloat("pos_y1", &slPosY1, -10.0f, 10.0f);
			ImGui::SliderFloat("pos_z1", &slPosZ1, -10.0f, 10.0f);
			ImGui::Text("Kierunek swiatla reflektora_2");
			ImGui::SliderFloat("dirX1", &spotLightDirection1.x, -10.0f, 10.0f);
			ImGui::SliderFloat("dirY1", &spotLightDirection1.y, -10.0f, 10.0f);
			ImGui::SliderFloat("dirZ1", &spotLightDirection1.z, -10.0f, 10.0f);
			ImGui::Checkbox("glPolygonMode", &isWireframeModeActive);
			
			if (ImGui::Button("ActivatePlygonMode"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			{
				isWireframeModeActive = !isWireframeModeActive;
				if (isWireframeModeActive) {
					cout << "Zmiana trybu wyswietlania " << endl;
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					cout << "Zmiana trybu wyswietlania " << endl;
				}
			}
				
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			ImGui::End();

			ImGui::Begin("PBR");
			ImGui::Text("Parametry swiat³a PBR");
			ImGui::SliderFloat("metalliness", &metallines, 0.0f, 1.0f);
			ImGui::SliderFloat("roughness", &roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ambient oclusion", &ao, 0.0f, 1.0f);
			ImGui::End();
		}

		pointLightPivot->Rotate(1, glm::vec3(0.0f, 1.0f, 0.0f));
		lightB->setPosition(x_axis, y_axis, 0);
		spotLight->setPosition(slPosX, slPosY, slPosZ);
		spotLight2->setPosition(slPosX1, slPosY1, slPosZ1);
		ourShader->use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		glm::vec3 lightPosition = lightB->getPosition();
		glm::vec3 spotLightPosition = spotLight->getPosition();
		glm::vec3 spotLightPosition1 = spotLight2->getPosition();

		ourShader->setMat4("view", view);
		ourShader->setMat4("projection", projection);

		if (PBR) {
			ourShader->setVec3("camPos", camera.Position);

			ourShader->setFloat("ao", ao);
			ourShader->setFloat("metallic", metallines);
			ourShader->setFloat("roughness", roughness);

			ourShader->setVec3("pointLight.color", lightDiffuse);
			ourShader->setVec3("pointLight.position", lightPosition);
			
			ourShader->setVec3("dirLight.direction", lightDirection);
			ourShader->setVec3("dirLight.color", lightAmbient);
			ourShader->setFloat("dirLight.lightStrength", 0.05f);

			ourShader->setVec3("spotLight[0].position", spotLightPosition);
			ourShader->setVec3("spotLight[0].direction", spotLightDirection);
			ourShader->setFloat("spotLight[0].cutOff", glm::cos(glm::radians(8.0f)));
			ourShader->setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(10.0f)));
			ourShader->setVec3("spotLight[0].color", 1.0f, 0.0f, 0.0f);

			ourShader->setVec3("spotLight[1].position", spotLightPosition1);
			ourShader->setVec3("spotLight[1].direction", spotLightDirection1);
			ourShader->setFloat("spotLight[1].cutOff", glm::cos(glm::radians(12.0f)));
			ourShader->setFloat("spotLight[1].outerCutOff", glm::cos(glm::radians(16.0f)));
			ourShader->setVec3("spotLight[1].color", 0.0f, 0.0f, 1.0f);

		}
		else {
		ourShader->setVec3("dirLight.ambient", lightAmbient);
		ourShader->setVec3("dirLight.diffuse", lightDiffuse); // przyciemnij nieco œwiat³o, aby pasowa³o do sceny
		ourShader->setVec3("dirLight.specular", lightSpecular);
		ourShader->setVec3("dirLight.direction", -lightDirection);

		ourShader->setVec3("pointLight.position", lightPosition);
		ourShader->setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
		ourShader->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
		ourShader->setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
		ourShader->setFloat("pointLight.constant", 1.0f);
		ourShader->setFloat("pointLight.linear", 0.09f);
		ourShader->setFloat("pointLight.quadratic", 0.032f);

		ourShader->setVec3("spotLight[0].position", spotLightPosition);
		ourShader->setVec3("spotLight[0].direction", spotLightDirection);
		ourShader->setFloat("spotLight[0].cutOff", glm::cos(glm::radians(12.0f)));
		ourShader->setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(16.0f)));
		ourShader->setVec3("spotLight[0].ambient", 0.05f, 0.05f, 0.05f);
		ourShader->setVec3("spotLight[0].diffuse", 0.8f, 0.0f, 0.0f);
		ourShader->setVec3("spotLight[0].specular", 1.0f, 1.0f, 1.0f);
		ourShader->setFloat("spotLight[0].constant", 1.0f);
		ourShader->setFloat("spotLight[0].linear", 0.09f);
		ourShader->setFloat("spotLight[0].quadratic", 0.032f);

		ourShader->setVec3("spotLight[1].position", spotLightPosition1);
		ourShader->setVec3("spotLight[1].direction", spotLightDirection1);
		ourShader->setFloat("spotLight[1].cutOff", glm::cos(glm::radians(12.0f)));
		ourShader->setFloat("spotLight[1].outerCutOff", glm::cos(glm::radians(16.0f)));
		ourShader->setVec3("spotLight[1].ambient", 0.05f, 0.05f, 0.05f);
		ourShader->setVec3("spotLight[1].diffuse", 0.0f, 0.8f, 0.0f);
		ourShader->setVec3("spotLight[1].specular", 1.0f, 1.0f, 1.0f);
		ourShader->setFloat("spotLight[1].constant", 1.0f);
		ourShader->setFloat("spotLight[1].linear", 0.09f);
		ourShader->setFloat("spotLight[1].quadratic", 0.032f);
		}

		ourShader2->use();
		ourShader2->setMat4("view", view);
		ourShader2->setMat4("projection", projection);
		ourShader2->setVec3("lightColor", lightDiffuse);
		

		/*cout << camera.Position.x << " " << camera.Position.y<< " "<< camera.Position.z <<endl;
		cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << endl;*/
		root.Update(deltaTime * 5);
		root.Draw();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete ourShader;
	delete ourShader2;
	delete ourModel;
	delete ourModel2;
	//delete mesh;
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	glfwTerminate();

	
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	  
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetCursorPosCallback(window, NULL);
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		glfwSetCursorPosCallback(window, mouse_callback);
	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLfloat xpos1 = (float)xpos;
	GLfloat ypos1 = (float)ypos;
	if (firstMouse)
	{
		lastX = xpos1;
		lastY = ypos1;
		firstMouse = false;
	}

	GLfloat xoffset = xpos1 - lastX;
	GLfloat yoffset = lastY - ypos1;
	lastX = xpos1;
	lastY = ypos1;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}