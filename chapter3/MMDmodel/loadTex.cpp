#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <string>
#include "stb_image.h"

using namespace std;

// 直接加载纹理函数（不需要OpenGL上下文）
bool LoadTextureDirectly(const char* filepath)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    
    if (data)
    {
        std::cout << "纹理加载成功！" << std::endl;
        std::cout << "宽度: " << width << std::endl;
        std::cout << "高度: " << height << std::endl;
        std::cout << "通道数: " << nrChannels << std::endl;
        
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cout << "纹理加载失败，路径: " << filepath << std::endl;
        std::cout << "错误: " << stbi_failure_reason() << std::endl;
        return false;
    }
}

int main()
{
    // 设置绝对路径
    const char* texturePath = "E:/myLearnOpengl/chapter3/MMDmodel/textures/texture.jpg";
    
    // 直接使用stbi_load加载纹理
    stbi_set_flip_vertically_on_load(true); // 翻转Y轴
    bool success = LoadTextureDirectly(texturePath);
    
    if (success) {
        std::cout << "纹理加载测试完成" << std::endl;
    } else {
        std::cout << "纹理加载测试失败" << std::endl;
    }
    
    return 0;
}