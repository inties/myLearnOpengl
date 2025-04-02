#define GLEW_STATIC
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <camera.h>
#include<Utils.h>

#include <iostream>
#include<Model.h>
#include<Mesh.h>
#include<textureloader.h>
#include<vertexAtriLoader.h>
#include<GeometryData.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);
// settings
const unsigned int SCR_WIDTH = 2000;
const unsigned int SCR_HEIGHT = 1400;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLuint quadVAO = 0;
GLuint quadVBO;
void RenderQuad();

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
  
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    stbi_set_flip_vertically_on_load(true);
    
    // 使用绝对路径加载着色器
    std::string shaderPath = "E:/myLearnOpengl/chapter5/Bloom/shaders/";
    std::string vs_path = shaderPath + "gbuffer.vs";
    std::string fs_path = shaderPath + "gbuffer.frag";
    Shader ourShader(vs_path.c_str(), fs_path.c_str());
    
    vs_path = shaderPath + "blinn_phong_deffered.vs";
    fs_path = shaderPath + "blinn_phong_deffered.frag";
    Shader shadingShader(vs_path.c_str(), fs_path.c_str());
    
    vs_path = shaderPath + "screen.vs";
    fs_path = shaderPath + "screen.frag";
    Shader screenShader(vs_path.c_str(), fs_path.c_str());
    
    vs_path = shaderPath + "cube.vs";
    fs_path = shaderPath + "cube.frag";
    Shader lightCubeShader(vs_path.c_str(), fs_path.c_str());
    
    Model ourModel("E:/myLearnOpengl/models/backpack/backpack.obj");

// 光源立方体的顶点数据
float cubeVertices[] = {
    // 前面
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // 后面
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    // 左面
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    // 右面
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    // 上面
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    // 下面
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f
};

unsigned int cubeIndices[] = {
    // 前面
    0, 1, 2,
    2, 3, 0,
    // 后面
    4, 5, 6,
    6, 7, 4,
    // 左面
    8, 9, 10,
    10, 11, 8,
    // 右面
    12, 13, 14,
    14, 15, 12,
    // 上面
    16, 17, 18,
    18, 19, 16,
    // 下面
    20, 21, 22,
    22, 23, 20
};

// 光源立方体的VAO/VBO
unsigned int lightCubeVAO, lightCubeVBO, lightCubeEBO;
glGenVertexArrays(1, &lightCubeVAO);
glGenBuffers(1, &lightCubeVBO);
glGenBuffers(1, &lightCubeEBO);

glBindVertexArray(lightCubeVAO);
glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightCubeEBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindVertexArray(0);

    //创建G-Buffer帧缓冲
    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gAlbedoSpec;
    // - 位置颜色缓冲
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // - 法线颜色缓冲
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // - 漫反射和高光系数缓冲
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    // 设置要使用的颜色缓冲
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
    // 创建并添加深度缓冲
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "G-Buffer Framebuffer is not complete!" << std::endl;
        return -1;
    }

    // 创建HDR帧缓冲
    unsigned int hdrFBO;
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    // 创建HDR颜色缓冲
    unsigned int hdrColorBuffer;
    glGenTextures(1, &hdrColorBuffer);
    glBindTexture(GL_TEXTURE_2D, hdrColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hdrColorBuffer, 0);
    
    // 创建Bloom颜色缓冲
    unsigned int bloomColorBuffer;
    glGenTextures(1, &bloomColorBuffer);
    glBindTexture(GL_TEXTURE_2D, bloomColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloomColorBuffer, 0);
    
    // 设置要使用的颜色缓冲
    GLuint hdrAttachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, hdrAttachments);
    
    // 创建HDR深度缓冲
    unsigned int hdrRBO;
    glGenRenderbuffers(1, &hdrRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, hdrRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, hdrRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "HDR Framebuffer is not complete!" << std::endl;
        return -1;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 创建两个用于高斯模糊的帧缓冲
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "PingPong Framebuffer " << i << " is not complete!" << std::endl;
    }

    // 创建高斯模糊着色器
    vs_path = shaderPath + "blur.vs";
    fs_path = shaderPath + "blur.frag";
    Shader blurShader(vs_path.c_str(), fs_path.c_str());
    blurShader.use();
    blurShader.setInt("image", 0);

    shadingShader.use();
    shadingShader.setInt("gPosition", 0);
    shadingShader.setInt("gNormal", 1);
    shadingShader.setInt("gAlbedoSpec", 2);

    screenShader.use();
    screenShader.setInt("hdrBuffer", 0);
    screenShader.setInt("bloomBuffer", 1);
    float exposure = 1.0f;

    const int NR_LIGHTS = 4;
    // 设置光源的位置和颜色
    glm::vec3 lightPositions[NR_LIGHTS] = {
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(3.0f, 3.0f, 4.0f),
        glm::vec3(-3.0f, -3.0f, 5.0f),
        glm::vec3(0.0f, 5.0f, -5.0f)
    };
    glm::vec3 lightColors[NR_LIGHTS] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    };
    float emissiveIntensities[NR_LIGHTS] = {
        3.0f,  // 红色光源
        3.0f,  // 绿色光源
        3.0f,  // 蓝色光源
        1.0f   // 白色光源
    };

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        
        // 1. 几何处理阶段：渲染到G-Buffer
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // 2. 光照处理阶段：使用G-Buffer计算光照并渲染到HDR帧缓冲
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shadingShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        
        for (unsigned int i = 0; i < NR_LIGHTS; i++) {
            shadingShader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            shadingShader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
            shadingShader.setFloat("lights[" + std::to_string(i) + "].Linear", 0.7f);
            shadingShader.setFloat("lights[" + std::to_string(i) + "].Quadratic", 1.8f);
            shadingShader.setFloat("lights[" + std::to_string(i) + "].emissiveIntensity", emissiveIntensities[i]);
        }
        shadingShader.setVec3("viewPos", camera.Position);
        RenderQuad();

        // 3. 复制深度信息并渲染光源
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, hdrFBO);
        glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        
        for (unsigned int i = 0; i < NR_LIGHTS; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPositions[i]);
            model = glm::scale(model, glm::vec3(0.1f));
            lightCubeShader.setMat4("model", model);
            lightCubeShader.setVec3("lightColor", lightColors[i]);
            lightCubeShader.setFloat("emissiveIntensity", emissiveIntensities[i]);
            
            glBindVertexArray(lightCubeVAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // 4. 高斯模糊
        bool horizontal = true, first_iteration = true;
        blurShader.use();
        for (unsigned int i = 0; i < 10; i++)  // 修改为10次迭代（5次水平+5次垂直）
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            blurShader.setBool("horizontal", horizontal);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? bloomColorBuffer : pingpongColorbuffers[!horizontal]);
            RenderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }

        // 5. HDR色调映射和gamma校正
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        screenShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, hdrColorBuffer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        screenShader.setFloat("exposure", exposure);
        RenderQuad();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // 调整曝光度
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            exposure += 0.1f;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            exposure -= 0.1f;
    }

    glDeleteFramebuffers(1, &gBuffer);
    glDeleteFramebuffers(1, &hdrFBO);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gAlbedoSpec);
    glDeleteTextures(1, &hdrColorBuffer);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteRenderbuffers(1, &hdrRBO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &lightCubeVBO);
    glDeleteBuffers(1, &lightCubeEBO);
    glDeleteFramebuffers(2, pingpongFBO);
    glDeleteTextures(2, pingpongColorbuffers);
    glDeleteTextures(1, &bloomColorBuffer);

    glfwTerminate();
    return 0;
}

void RenderQuad()
{
    if (quadVAO == 0)
    {
        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}