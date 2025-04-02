//#define GLEW_STATIC
//#include <glew/glew.h>
//#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <Shader.h>
//#include <camera.h>
//#include<Utils.h>
//
//#include <iostream>
//#include<Model.h>
//#include<Mesh.h>
//#include<textureloader.h>
////#include<vertexAtriLoader.h>
//#include<GeometryData.h>
////-----------------------------------------------------------------------------------------//
////这个程序无法正确加载纹理//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//unsigned int loadTexture(const char* path);
//
//unsigned int loadCubemap(vector<std::string> faces);
//// settings
//const unsigned int SCR_WIDTH = 2000;
//const unsigned int SCR_HEIGHT = 1400;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    vector<float>vertexs = Geometry::Cube.vertices;
//
//    //Atriloader cubeVertexAttri(cube.vertices,cube.stride,cube.attribSizes);
//    unsigned int VAO, VBO;
//    glCreateVertexArrays(1, &VAO);
//    glCreateBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexs.size(), vertexs.data(), GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
//
//
//    Shader ourShader("chapter4/cubemap/cube.vs", "chapter4/cubemap/cube.frag");
//	//create texture
//	unsigned int textureID;
//	textureID = loadTexture("container.jpg");
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	//bind texture to shader
//	ourShader.setInt("tex", 1);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//
//
//    vector<glm::vec3>cubesPos = {
//        glm::vec3(1.0,2.0,3.0),glm::vec3(3.0,4.5,8.5)
//
//
//    };
//
//    std::map<float, int>distanceMap;
//
//    unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	// create a color attachment texture
//	unsigned int textureColorbuffer;
//	glGenTextures(1, &textureColorbuffer);
//	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
//	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
//	// attach the texture to the framebuffer
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//    Shader screenShader("chapter4/framebuffer/screen.vs", "chapter4/framebuffer/screen.frag");
//	//screen vertex and texturecoord
//    vector<float>screen = {
//        -1.0f, -1.0f, 0.0f,0.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,1.0f, 0.0f,
//        1.0f, 1.0f, 0.0f,1.0f, 1.0f,
//        -1.0f, 1.0f, 0.0f,0.0f, 1.0f,
//    };
// 
//	//create vao vbo
//	unsigned int screenVAO, screenVBO;
//    glCreateVertexArrays(1, &screenVAO);
//	glCreateBuffers(1, &screenVBO);
//	glBindVertexArray(screenVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * screen.size(), screen.data(), GL_STATIC_DRAW);
//	//set vertex attribute
//	glEnableVertexAttribArray(0);
//	//set vertex attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	//set texture attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    //unbind
//	glBindVertexArray(0);
//	//bind framebuffer color attachment to texture0
//	screenShader.use();
//	screenShader.setInt("screenTexture", 0);
//	//activate color attachment texture
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//	
//	
//    
//	screenShader.setInt("screenTexture", 0);
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//        processInput(window);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        ourShader.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//        ourShader.setMat4("model", model);
//        // render the loaded model
//
//        //cubeVertexAttri.bind();
//        glBindVertexArray(VAO);
//
//        for (int i = 0; i < cubesPos.size(); i++) {
//            float distance = glm::length(camera.Position - cubesPos[i]);
//            distanceMap[distance] = i;
//        }
//        for (std::map<float, int>::reverse_iterator it = distanceMap.rbegin(); it != distanceMap.rend(); ++it) {
//            model = glm::mat4(1.0f);
//
//            model = glm::translate(model, cubesPos[it->second]);
//            ourShader.setMat4("model", model);
//            if (it->second == 0)ourShader.setVec3("color", glm::vec3(0.8, 0.2, 0.2));
//            else ourShader.setVec3("color", glm::vec3(0.2, 0.8, 0.2));
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//		glClear(GL_COLOR_BUFFER_BIT);
//		screenShader.use();
//		glBindVertexArray(screenVAO);
//		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//		glEnable(GL_DEPTH_TEST);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//
//}
