#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <Triangle.h>
#include <VertexManager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include <string>
#include <iostream>
#include "Shader.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
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

    // Create window with graphics context
	GLfloat screenWidth = 1280;
	GLfloat screenHeight = 720;
	GLFWwindow* window = glfwCreateWindow(GLuint(screenWidth), GLuint(screenHeight), "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();


    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
	Shader ourShader("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.vs", "C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\src\\shader.fs");
	std::vector<Tetrahedron> tetrahedrons;
	
	//tworzenie pierwszego tetrahedronu
	{
		GLfloat vertices1[] = {//front
				-0.5f, -0.5f, 0.5f,
				 0.5f, -0.5f, 0.5f,
				 0.0f,  0.5f, 0.0f
		};
		GLfloat vertices2[] = {//lewa strona
				-0.5f, -0.5f, 0.5f,
				 0.0f,  -0.5f, -0.5f,
				 0.0f,  0.5f, 0.0f
		};
		GLfloat vertices3[] = {//prawa strona
				0.5f, -0.5f, 0.5f,
				0.0f,  -0.5f, -0.5f,
				0.0f,  0.5f, 0.0f
		};
		GLfloat vertices4[] = {//spodek
				-0.5f, -0.5f, 0.5f,
				 0.5f, -0.5f, 0.5f,
				 0.0f,  -0.5f, -0.5f
		};



		auto triangle1 = Triangle(vertices1);
		auto triangle2 = Triangle(vertices2);
		auto triangle3 = Triangle(vertices3);
		auto triangle4 = Triangle(vertices4);

		std::vector<Triangle> triangles;
		triangles.push_back(triangle1);
		triangles.push_back(triangle2);
		triangles.push_back(triangle3);
		triangles.push_back(triangle4);
		Tetrahedron tetrahedron(triangles);


		tetrahedrons.push_back(tetrahedron);
	}

	VertexManager vertex_manager = VertexManager();
	auto *allVertices = new std::vector<Vertex>();
	//vertex_manager.createTrianglesFromVertexAndMids(1, allVertices, triangle1);
	std::vector<Triangle> triangles2;
	vertex_manager.CreateTetrahedrons(1, tetrahedrons, triangles2);
	vertex_manager.SummariseVertices(allVertices, triangles2);
	vertex_manager.createDataAndIndexArrays(allVertices);
	
	std::vector<float> *floats2 = vertex_manager.getFloats();
	std::vector<unsigned int> *indexArray = vertex_manager.getIndexArray();
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("C:\\Semestr5\\PAG\\openGL\\MyOpenGl\\Build\\Debug\\gold.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArray->size() * sizeof(unsigned int), indexArray->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, floats2->size() * sizeof(float), floats2->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, texture);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glm::mat4 model(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
	
	GLint modelLoc = glGetUniformLocation(ourShader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint viewLoc = glGetUniformLocation(ourShader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLint projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
	ourShader.use();
	
	int recursion_level = 1;
	float radians = 0.0f;
	/*float x_axis = 1.0f;
	float y_axis = 0.0f;*/
	bool is_x_axis = false;
	bool is_y_axis = true;
	glEnable(GL_DEPTH_TEST);
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
			//ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform4f(vertexColorLocation, clear_color.x, clear_color.y, clear_color.z, 1.0f);
		if(is_x_axis)
		{
			 model = glm::rotate(model, glm::radians(radians), glm::vec3(1.0f, 0.0f, 0.0f)); 
		}
		if(is_y_axis)
		{
			model = glm::rotate(model, glm::radians(radians), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		{
			{
			    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			    //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			    //ImGui::Checkbox("Another Window", &show_another_window);

			    ImGui::SliderInt("recursion level", &recursion_level, 1, 10);  
				ImGui::SliderFloat("rotation speed", &radians, -4.0f, 4.0f);
				/*ImGui::SliderFloat("x-axis", &x_axis, 0.0f, 1.0f);
				ImGui::SliderFloat("y-axis", &y_axis, 0.0f, 1.0f);*/
			    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
				ImGui::Checkbox("x_axis", &is_x_axis); ImGui::SameLine(150);
				ImGui::Checkbox("y_axis", &is_y_axis);

				if (ImGui::Button("Generate"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				{
					allVertices->clear();
					triangles2.clear();
					vertex_manager.CreateTetrahedrons(recursion_level, tetrahedrons, triangles2);
					//vertex_manager.createTetrahedron(recursion_level, allVertices, triangles);
					//vertex_manager.createTrianglesFromVertexAndMids(recursion_level, allVertices, triangle1);
					vertex_manager.SummariseVertices(allVertices, triangles2);
					vertex_manager.createDataAndIndexArrays(allVertices);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArray->size() * sizeof(unsigned int), indexArray->data(), GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, floats2->size() * sizeof(float), floats2->data(), GL_STATIC_DRAW);
				}
				ImGui::Text("Vertices count: %d", indexArray->size());
				ImGui::Text("Floats count: %d", floats2->size() * 3/5);
				
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			    ImGui::End();
			}
		}
		
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexArray->size(), GL_UNSIGNED_INT, 0);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
	
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	delete allVertices;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}