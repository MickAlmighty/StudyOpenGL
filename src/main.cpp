//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//#include <cstdio>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <stb_image.h>
//#include <filesystem>
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//#include <GL/gl3w.h>    // Initialize with gl3wInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//#include <GL/glew.h>    // Initialize with glewInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//#include <glad/glad.h>  // Initialize with gladLoadGL()
//#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#endif
//
//#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
//#include <string>
//#include <iostream>
//#include <Shader.h>
//#include <Model.h>
//
//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}
//
//int main(int, char**)
//{
//    // Setup window
//    glfwSetErrorCallback(glfw_error_callback);
//    if (!glfwInit())
//        return 1;
//
//    // Decide GL+GLSL versions
//#if __APPLE__
//    // GL 3.2 + GLSL 150
//    const char* glsl_version = "#version 150";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
//#else
//    // GL 4.3 + GLSL 430
//    const char* glsl_version = "#version 430";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//#endif
//
//    // Create window with graphics context
//	GLfloat screenWidth = 1280;
//	GLfloat screenHeight = 720;
//	GLFWwindow* window = glfwCreateWindow(GLuint(screenWidth), GLuint(screenHeight), "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
//    if (window == NULL)
//        return 1;
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1); // Enable vsync
//
//    // Initialize OpenGL loader
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//    bool err = gl3wInit() != 0;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//    bool err = glewInit() != GLEW_OK;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//    bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//#endif
//    if (err)
//    {
//        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//        return 1;
//    }
//
//    // Setup Dear ImGui binding
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
//
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    // Setup style
//    ImGui::StyleColorsDark();
//
//
//    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
//	Shader ourShader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.fs");
//	Model ourModel("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\nanosuit\\nanosuit.obj");
//	int recursion_level = 1;
//	float radians = 0.0f;
//	/*float x_axis = 1.0f;
//	float y_axis = 0.0f;*/
//	bool is_x_axis = false;
//	bool is_y_axis = true;
//	//******CAMERA***************
//	/*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//
//	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);*/
//	//CAMERA
//	glm::mat4 projection(1.0f);
//	glm::mat4 view(1.0f);
//	glm::mat4 model(1.0f);
//	int display_w, display_h;
//	glViewport(0, 0, display_w, display_h);
//	glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
//	glEnable(GL_DEPTH_TEST);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	// Main loop
//	while (!glfwWindowShouldClose(window))
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		// Poll and handle events (inputs, window resize, etc.)
//		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//		
//		
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//		//if (show_demo_window)
//			//ImGui::ShowDemoWindow(&show_demo_window);
//
//		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//		
//		
//		//{
//		//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//		//	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//		//	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//		//	//ImGui::Checkbox("Another Window", &show_another_window);
//
//		//	ImGui::SliderInt("recursion level", &recursion_level, 1, 10);  
//		//	ImGui::SliderFloat("rotation speed", &radians, -40.0f, 40.0f);
//		//	/*ImGui::SliderFloat("x-axis", &x_axis, 0.0f, 1.0f);
//		//	ImGui::SliderFloat("y-axis", &y_axis, 0.0f, 1.0f);*/
//		//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//		//	ImGui::Checkbox("x_axis", &is_x_axis); ImGui::SameLine(150);
//		//	ImGui::Checkbox("y_axis", &is_y_axis);
//
//		//	if (ImGui::Button("Generate"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//		//	{
//		//			
//		//	}
//		//		
//		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//		//	ImGui::End();
//		//}
//		ourShader.use();
//		GLfloat radius = 10.0f;
//		GLfloat camX = sin(glfwGetTime()) * radius;
//		GLfloat camZ = cos(glfwGetTime()) * radius;
//		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//		projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
//		
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		ourModel.Draw(ourShader);
//		
//        // Rendering
//        //ImGui::Render();
//
//
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//
//		
//        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//		glfwPollEvents();
//        glfwSwapBuffers(window);
//    }
//	
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}

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

#include <iostream>
#include <cstdlib>
#include <ctime>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.05f; // dopasuj do swoich potrzeb
GLfloat deltaTime = 0.0f; // Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹  
GLfloat lastFrame = 0.0f; // Czas ostatniej ramki
GLfloat yaw = 0;
GLfloat pitch = 0;
bool firstMouse = true;
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
	srand(static_cast <unsigned> (time(0)));
	// build and compile our shader zprogram
	// ------------------------------------
	Shader* ourShader = new Shader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.fs");
	//Shader* ourShader2 = new Shader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.fs");
	Model* ourModel = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\nanosuit\\nanosuit.obj");
	Model* ourModel2 = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\chair\\Armchair Quinti Amelie.3ds");
	Model* nanosuit = new Model("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\nanosuit\\nanosuit.obj");
	
	Mesh *mesh = new Mesh();
	Mesh *torus = new Mesh();
	Mesh *torus2 = new Mesh();
	mesh->generateTorus(3, 50, 0.02f, 10.0f);
	torus->generateTorus(3, 50, 0.02f, 3.0f);
	torus2->generateTorus(8, 50, 2.0f, 3.0f);
	Model* model3 = new Model(mesh);
	Model* model4 = new Model(torus);
	Model* model5 = new Model(torus2);
	
	ourModel->SetShader(ourShader);
	ourModel2->SetShader(ourShader);
	model3->SetShader(ourShader);
	model4->SetShader(ourShader);
	model5->SetShader(ourShader);
	nanosuit->SetShader(ourShader);
	ourShader->use();

	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------
	glm::mat4 projection(1);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);

	glm::mat4* model = new glm::mat4(1);
	*model = glm::translate(*model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	*model = glm::scale(*model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down

	glm::mat4* model2 = new glm::mat4(1);
	*model2 = glm::rotate(*model2, glm::radians(90.0f), glm::vec3(1, 0, 0));
	
	
	glm::mat4* transform = new glm::mat4(1);
	*transform = glm::translate(*transform, glm::vec3(10.0f, -0.5f, 0.0f)); // translate it down so it's at the center of the scene
	*transform = glm::scale(*transform, glm::vec3(0.1f, 0.1f, 0.1f));
	GraphNode root(true);
	GraphNode* sun = new GraphNode(false, ourModel);
	GraphNode* sun2 = new GraphNode(true, nanosuit);
	GraphNode* chair = new GraphNode(true, ourModel2);
	GraphNode* sunOrbit = new GraphNode(true, model3);
	GraphNode* chairOrbit = new GraphNode(true, model4);
	GraphNode* chairMoon = new GraphNode(true, model5);
	
	root.AddChild(sun);
	root.AddChild(sun2);
	sun->SetTransform(model);
	sunOrbit->SetTransform(model2);
	sun->AddChild(sunOrbit);
	chair->SetTransform(transform);
	sun->AddChild(chair);
	chair->AddChild(chairOrbit);
	chairOrbit->Scale(glm::vec3(10, 10, 10));
	chairOrbit->Rotate(45, glm::vec3(1, 0, 0));
	
	chairOrbit->AddChild(chairMoon);
	chairMoon->Translate(glm::vec3(3, 0, 0));
	chairMoon->Scale(glm::vec3(0.1f, 0.1f, 0.1));


	sun2->Scale(glm::vec3(0.15, 0.15, 0.15));
	sun2->Translate(glm::vec3(-12, -15, -3));
	sun2->Rotate(30, glm::vec3(0, 1, 0));

	glm::mat4 view(1);
	int numberOfRings = 30;
	int oldNumberOfRings;
	bool isWireframeModeActive = false;
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
		oldNumberOfRings = numberOfRings;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
			
			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);
			
			ImGui::SliderInt("NumberOfRings", &numberOfRings, 3, 50);
			//ImGui::SliderFloat("rotation speed", &radians, -40.0f, 40.0f);
			/*ImGui::SliderFloat("x-axis", &x_axis, 0.0f, 1.0f);
			ImGui::SliderFloat("y-axis", &y_axis, 0.0f, 1.0f);*/
			//mGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
			//ImGui::Checkbox("x_axis", &is_x_axis); ImGui::SameLine(150);
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
		}
		if(oldNumberOfRings != numberOfRings)
			mesh->generateTorus(3, numberOfRings, 0.02f, 10.0f);
		sun->Rotate(1, glm::vec3(0, 1, 0));
		sunOrbit->Rotate(0, glm::vec3(0, 1, 0));
		chair->Rotate(1, glm::vec3(1, 0, 0.2));
		chairOrbit->Rotate(2, glm::vec3(0, 0, 1));
		chairMoon->Rotate(2, glm::vec3(0, 1, 0.2));

		cameraSpeed = 3.5f * deltaTime;
		// activate shader
		ourShader->use();

		// camera/view transformation
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader->setMat4("view", view);
		
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
	//delete ourShader2;
	delete ourModel;
	delete ourModel2;
	delete mesh;
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
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

	GLfloat sensitivity = 0.15f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}