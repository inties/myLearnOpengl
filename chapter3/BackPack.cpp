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
//
//#include <iostream>
//#include<Model.h>
//#include<Mesh.h>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(char const* path);
//
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
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    stbi_set_flip_vertically_on_load(true);
//    Shader easyShader("easyShader.vs", "easyShader.frag");
//    Model model("E:/myLearnOpengl/models/backpack");
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
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//        // be sure to activate shader when setting uniforms/drawing objects
//        easyShader.use();
//
//
//        easyShader.setVec3("caremaPos", camera.Position);
//        // light properties
//        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//        /*     lightColor.x = static_cast<float>(sin(0.3*glfwGetTime() * 2.0));
//             lightColor.y = static_cast<float>(sin(0.3 * glfwGetTime() * 0.7));
//             lightColor.z = static_cast<float>(sin(0.3 * glfwGetTime() * 1.3));*/
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
//     
//
//        easyShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        easyShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        easyShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        easyShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//     
//
//        model.Draw(easyShader);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//}