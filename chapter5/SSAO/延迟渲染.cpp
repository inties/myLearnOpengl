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
//GLuint quadVAO = 0;
//GLuint quadVBO;
//void RenderQuad();
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
//  
//    glfwMakeContextCurrent(window);
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//  
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    stbi_set_flip_vertically_on_load(true);
//    Shader ourShader("E:/myLearnOpengl/chapter5/deffered/gbuffer.vs", "E:/myLearnOpengl/chapter5/deffered/gbuffer.frag");
//    Shader shadingShader("E:/myLearnOpengl/chapter5/deffered/blinn_phong_deffered.vs", "E:/myLearnOpengl/chapter5/deffered/blinn_phong_deffered.frag");
//    Model ourModel("E:/myLearnOpengl/models/backpack/backpack.obj");
//
//// 光源立方体的顶点数据
//float cubeVertices[] = {
//    // 前面
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    // 后面
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    // 左面
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//    // 右面
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f, -0.5f,
//    // 上面
//    -0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    // 下面
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f
//};
//
//unsigned int cubeIndices[] = {
//    // 前面
//    0, 1, 2,
//    2, 3, 0,
//    // 后面
//    4, 5, 6,
//    6, 7, 4,
//    // 左面
//    8, 9, 10,
//    10, 11, 8,
//    // 右面
//    12, 13, 14,
//    14, 15, 12,
//    // 上面
//    16, 17, 18,
//    18, 19, 16,
//    // 下面
//    20, 21, 22,
//    22, 23, 20
//};
//
//// 光源立方体的VAO/VBO
//unsigned int lightCubeVAO, lightCubeVBO, lightCubeEBO;
//glGenVertexArrays(1, &lightCubeVAO);
//glGenBuffers(1, &lightCubeVBO);
//glGenBuffers(1, &lightCubeEBO);
//
//glBindVertexArray(lightCubeVAO);
//glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightCubeEBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
//
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//
//glBindVertexArray(0);
//
//// 光源立方体的着色器
//Shader lightCubeShader("E:/myLearnOpengl/chapter5/hdrANDbloom/cube.vs", "E:/myLearnOpengl/chapter5/hdrANDbloom/cube.frag");
//
//    //����֡���岢�󶨼�����ͬ����ɫ��������
//	unsigned int gBuffer;
//	glGenFramebuffers(1, &gBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//	unsigned int gPosition, gNormal, gAlbedoSpec;
//	// - λ����ɫ����
//	glGenTextures(1, &gPosition);
//    glBindTexture(GL_TEXTURE_2D, gPosition);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	//�󶨵�֡����
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//	// - ������ɫ����
//	glGenTextures(1, &gNormal);
//    glBindTexture(GL_TEXTURE_2D, gNormal);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	//�󶨵�֡����
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//	//-������͸߹�ϵ�����壬ʹ��RGBA��ʽ����Ϊ������Ҫ�洢��������ɫ�͸߹���ɫ
//	glGenTextures(1, &gAlbedoSpec);
//    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
//	//����ʹ���ĸ���ɫ����
//    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//    glDrawBuffers(3, attachments);
//    unsigned int depthRenderbuffer;
//    glGenRenderbuffers(1, &depthRenderbuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
//
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        std::cout << "Framebuffer is not complete!" << std::endl;
//        return -1;
//    }
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	shadingShader.use();
//	shadingShader.setInt("gPosition", 0);
//	shadingShader.setInt("gNormal", 1);
//	shadingShader.setInt("gAlbedoSpec", 2);
//
//    const int NR_LIGHTS = 4;
//    // ���������Դ��λ�ú���ɫ
//    glm::vec3 lightPositions[NR_LIGHTS] = {
//        glm::vec3(0.0f, 0.0f, 5.0f),
//        glm::vec3(5.0f, 5.0f, 10.0f),
//        glm::vec3(-5.0f, -5.0f, 10.0f),
//        glm::vec3(0.0f, 5.0f, -5.0f)
//    };
//    glm::vec3 lightColors[NR_LIGHTS] = {
//        glm::vec3(1.0f, 0.0f, 0.0f),
//        glm::vec3(0.0f, 1.0f, 0.0f),
//        glm::vec3(0.0f, 0.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f)
//    };
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
//        
//        
//        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//        glEnable(GL_DEPTH_TEST);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        // don't forget to enable shader before setting uniforms
//        ourShader.use();
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//
//        // render the loaded model
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//        ourShader.setMat4("model", model);
//        ourModel.Draw(ourShader);
//
//        // 渲染光源立方体
//        lightCubeShader.use();
//        lightCubeShader.setMat4("projection", projection);
//        lightCubeShader.setMat4("view", view);
//        
//        for (unsigned int i = 0; i < NR_LIGHTS; i++) {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, lightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.5f)); // 缩小立方体尺寸
//            lightCubeShader.setMat4("model", model);
//            lightCubeShader.setVec3("lightColor", lightColors[i]);
//            
//            glBindVertexArray(lightCubeVAO);
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//            glBindVertexArray(0);
//        }
//
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);   
//       
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glDisable(GL_DEPTH_TEST); // �ӳ���Ⱦ�ڶ��׶�ͨ������Ҫ��Ȳ���
//        shadingShader.use();
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gPosition);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, gNormal);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//        for (unsigned int i = 0; i < NR_LIGHTS; i++)
//        {
//            glUniform3fv(glGetUniformLocation(shadingShader.ID, ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPositions[i][0]);
//            glUniform3fv(glGetUniformLocation(shadingShader.ID, ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColors[i][0]);
//            // Update attenuation parameters and calculate radius
//            const GLfloat constant = 1.0; // Note that we don't send this to the shader, we assume it is always 1.0 (in our case)
//            const GLfloat linear = 0.7;
//            const GLfloat quadratic = 1.8;
//            glUniform1f(glGetUniformLocation(shadingShader.ID, ("lights[" + std::to_string(i) + "].Linear").c_str()), linear);
//            glUniform1f(glGetUniformLocation(shadingShader.ID, ("lights[" + std::to_string(i) + "].Quadratic").c_str()), quadratic);
//        }
//		shadingShader.setVec3("viewPos", camera.Position);
//        RenderQuad();
//        
//        // 前向渲染光源立方体
//        glEnable(GL_DEPTH_TEST);
//        lightCubeShader.use();
//        lightCubeShader.setMat4("projection", projection);
//        lightCubeShader.setMat4("view", view);
//        
//        for (unsigned int i = 0; i < NR_LIGHTS; i++) {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, lightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.5f));
//            lightCubeShader.setMat4("model", model);
//            lightCubeShader.setVec3("lightColor", lightColors[i]);
//            
//            glBindVertexArray(lightCubeVAO);
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//            glBindVertexArray(0);
//        }
//        
//        // 复制深度信息到默认帧缓冲
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
//        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//        glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
// 
//    // ������Դ
//  
//    glDeleteFramebuffers(1, &gBuffer);
//    glDeleteTextures(1, &gPosition);
//    glDeleteTextures(1, &gNormal);
//    glDeleteTextures(1, &gAlbedoSpec);
//    glDeleteRenderbuffers(1, &depthRenderbuffer);
//    glDeleteVertexArrays(1, &quadVAO);
//    glDeleteBuffers(1, &quadVBO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &lightCubeVBO);
//    glDeleteBuffers(1, &lightCubeEBO);
//    glfwTerminate();//����opengl������
//    return 0;
//
//}
//
//void RenderQuad()
//{
//    if (quadVAO == 0)
//    {
//        GLfloat quadVertices[] = {
//            // Positions        // Texture Coords
//            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//        };
//        // Setup plane VAO
//        glGenVertexArrays(1, &quadVAO);
//        glGenBuffers(1, &quadVBO);
//        glBindVertexArray(quadVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    }
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glBindVertexArray(0);
//  
//}
