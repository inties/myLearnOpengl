#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <vector>               // 用于 std::vector
#include <string>               // 用于 std::string

// 前置声明 STB_IMAGE 函数（避免直接包含 stb_image.h）
extern "C" {
    unsigned char* stbi_load(const char* filename, int* width, int* height, int* nrChannels, int desired_channels);
    void stbi_image_free(void* data);
}

// 函数声明
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(std::vector<std::string> faces);

#endif // TEXTURE_LOADER_H#pragma once
