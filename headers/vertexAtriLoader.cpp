#include "vertexAtriLoader.h"
#define GLEW_STATIC
#include <glew/glew.h>
#include <vertexAtriLoader.h>

Atriloader::Atriloader(const std::vector<float>& vertices, int stride, const std::vector<int>& attribSizes) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    int offset = 0;
    for (size_t i = 0; i < attribSizes.size(); ++i) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribSizes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        offset += attribSizes[i];
    }
    vertexCount = vertices.size() / stride;
    glBindVertexArray(0);
}

Atriloader::~Atriloader() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Atriloader::bind() const {
    glBindVertexArray(VAO);
}



