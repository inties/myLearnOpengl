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
//#include<vertexAtriLoader.h>
//#include<GeometryData.h>
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//unsigned int loadTexture(const char* path);
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
//    glEnable(GL_STENCIL_TEST);
//    Shader ourShader("chapter3/easyShader.vs", "chapter3/easyShader.frag");
//    stbi_set_flip_vertically_on_load(true);
//    Model ourModel("models/backpack/backpack.obj");
//    
//    
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
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
//        
//        processInput(window);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
//        glStencilFunc(GL_ALWAYS, 1, 0xFF);
//        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//        glStencilMask(0xFF);
//        
//        ourShader.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(1.0, 1.0, 1.0));
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        ourShader.setMat4("model", model);
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//        ourShader.setInt("useTexture", 1);
//        ourModel.Draw(ourShader);
//        ourShader.use();
//        glDisable(GL_DEPTH_TEST);
//        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//        glStencilMask(0x00);
//        
//        model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));
//        ourShader.setMat4("model", model);
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//        ourShader.setInt("useTexture", 0);
//        ourModel.Draw(ourShader);
//        glEnable(GL_DEPTH_TEST);
//        glBindVertexArray(0);
//        glStencilMask(0xFF);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//
//}
