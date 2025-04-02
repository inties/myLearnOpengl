//#define GLEW_STATIC
//#include <glew/glew.h>
//#include <GLFW/glfw3.h>
//
//
//glFrontFace(GL_CW);
//gl_FragDepth//用来设置片段的深度值，NDC 是 [-1, 1]，而片段深度是 [0, 1]，光栅化阶段会将 NDC 的 z 值映射到 [0, 1] 范围内，所以我们需要将深度值映射到 [0, 1] 范围内。gl_FragDepth 是一个内建的输出变量，它可以让我们设置片段的深度值。我们可以在片段着色器中设置 gl_FragDepth 的值，这样就可以在片段着色器中手动设置片段的深度值了。
//// render loop
//out float gl_FragDepth;
////interface block是着色器间的结构体
//
//out VS_OUT
//{
//    vec2 TexCoords;
//} vs_out;
//in VS_OUT
//{
//    vec2 TexCoords;
//} fs_in;
//fs_in.TexCoords
//
////uniform block数据存放在是缓冲对象中，类型是GL_UNIFORM_BUFFER
////绑定到多个着色器程序中，这样就可以在多个着色器程序中共享数据了。这样的话，我们就可以在一个着色器程序中更新一个缓冲对象，然后在另一个着色器程序中使用这个缓冲对象了。
//layout(std140) uniform Matrices//std140是一个布局修饰符，它告诉 OpenGL 缓冲对象的布局是标准化的
//{
//    mat4 projection;
//    mat4 view;
//};
//unsigned int uboExampleBlock;
//glGenBuffers(1, &uboExampleBlock);
//glBindBuffer(GL_UNIFORM_BUFFER, uboExampleBlock);
//glBufferData(GL_UNIFORM_BUFFER, 152, NULL, GL_STATIC_DRAW); // 分配152字节的内存
//glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//unsigned int lights_index = glGetUniformBlockIndex(shaderA.ID, "Lights");//获取uniform block的索引
//glUniformBlockBinding(shaderA.ID, lights_index, 2);//将uniform block绑定到绑定点2,多个着色器程序可以共享一个uniform block
//
//glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboExampleBlock);
//glBindBufferRange(GL_UNIFORM_BUFFER, 2, uboExampleBlock, 0, 152);//绑定到2号绑定点，偏移0，大小152字节
//
//glBindBuffer(GL_UNIFORM_BUFFER, uboExampleBlock);
//int b = true; // GLSL中的bool是4字节的，所以我们将它存为一个integer
//glBufferSubData(GL_UNIFORM_BUFFER, 144, 4, &b);//更新缓冲对象的数据，144是偏移量，4是数据大小
//glBindBuffer(GL_UNIFORM_BUFFER, 0);
