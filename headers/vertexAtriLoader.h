#pragma once
#ifndef VERTEX_ATRI_LOADER_H
#define VERTEX_ATRI_LOADER_H
#include <vector>
 // 需要包含 OpenGL 头文件，因为使用了 unsigned int VAO, VBO

class Atriloader {
public:
    unsigned int VAO, VBO;

    Atriloader(const std::vector<float>& vertices, int stride, const std::vector<int>& attribSizes);
    ~Atriloader();

    void bind() const;

private:
    int vertexCount;
};
#endif // VERTEX_ATRI_LOADER_H