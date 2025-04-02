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
//
// /*   Atriloader cubeVertex(Geometry::Cube.vertices, Geometry::Cube.stride, Geometry::Cube.attribSizes);
//    Atriloader skyboxVertex(Geometry::Skybox.vertices, Geometry::Skybox.stride, Geometry::Skybox.attribSizes);*/
//    float cubeVertices[] = {
//        // positions          // texture Coords
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    float vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };
//    float skyboxVertices[] = {
//        // positions          
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        -1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f
//    };
//
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    // skybox VAO
//    unsigned int skyboxVAO, skyboxVBO;
//    glGenVertexArrays(1, &skyboxVAO);
//    glGenBuffers(1, &skyboxVBO);
//    glBindVertexArray(skyboxVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    unsigned int cubeReflectVAO, cubeReflectVBO;
//    glGenVertexArrays(1, &cubeReflectVAO);
//    glGenBuffers(1, &cubeReflectVBO);
//    glBindVertexArray(cubeReflectVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeReflectVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    int width, height, nrChannels;
//    unsigned char* data;
//    string base_path = "texture/skybox/";
//    vector<string> face_names = {
//        "right.jpg",  // +X
//        "left.jpg",   // -X
//        "top.jpg",    // +Y
//        "bottom.jpg", // -Y
//        "front.jpg",  // +Z
//        "back.jpg"    // -Z
//    };
//
//    vector<string> textures_faces;
//    for (const auto& face : face_names) {
//        textures_faces.push_back(base_path + face);
//    }
//    unsigned int skyboxID;
//    skyboxID =loadCubemap(textures_faces);
//    unsigned int cubetextureID;
//    cubetextureID = loadTexture("texture/container.jpg");
//    Shader skyboxShader("chapter4/cubemap/cubemap.vs","chapter4/cubemap/cubemap.frag");
//    Shader shader("chapter4/cubemap/cube.vs", "chapter4/cubemap/cube.frag");
//    Shader reflectshader("chapter4/cubemap/cubereflective.vs", "chapter4/cubemap/cubereflective.frag");
//
//    skyboxShader.setInt("skybox", 1);
//    shader.setInt("texture1", 0);
//    reflectshader.setInt("skybox", 1);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, cubetextureID);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, cubetextureID);
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
//        processInput(window);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        // draw scene as normal
//        shader.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        shader.setMat4("model", model);
//        shader.setMat4("view", view);
//        shader.setMat4("projection", projection);
//        // cubes
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//        reflectshader.use();
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(1.0, 2.0, 3.0));
//        reflectshader.setMat4("model", model);
//        reflectshader.setMat4("view", view);
//        reflectshader.setMat4("projection", projection);
//        reflectshader.setVec3("cameraPos", camera.Position);
//        
//        // cubes
//        glBindVertexArray(cubeReflectVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//    
//        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//        skyboxShader.use();
//        
//        
//        
//        skyboxShader.setMat4("view", view);
//        skyboxShader.setMat4("projection", projection);
//        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
//        skyboxShader.setMat4("view", view);
//        skyboxShader.setMat4("projection", projection);
//        // skybox cube
//        glBindVertexArray(skyboxVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//        glDepthFunc(GL_LESS); // set depth function back to default
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//
//}
