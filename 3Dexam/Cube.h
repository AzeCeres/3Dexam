#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "glm/mat4x3.hpp"
class Cube
{
    float length{1}, width{1}, height{1};
    Mesh mesh;
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    Shader* shader;
    bool constructed{false};
    void ConstructMesh()
    {
        if(constructed)
            return;
        constructed = true;
        mesh.vertices.clear();
        mesh.strideLength = 5;
        mesh.vertices = {
            {{-length/2, -width/2, height/2, 0.0f, 0.0f}},
            {{length/2, -width/2, height/2, 1.0f, 0.0f}},
            {{length/2, width/2, height/2, 1.0f, 1.0f}},
            {{-length/2, width/2, height/2, 0.0f, 1.0f}},
            {{-length/2, -width/2, -height/2, 0.0f, 0.0f}},
            {{length/2, -width/2, -height/2, 1.0f, 0.0f}},
            {{length/2, width/2, -height/2, 1.0f, 1.0f}},
            {{-length/2, width/2, -height/2, 0.0f, 1.0f}}
        };
        mesh.indices = {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
        };
    }
    unsigned int VBO, VAO;
    void SetupForDrawing()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices), mesh.vertices.data(), GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    
public:
    Cube(float lengthIn, float widthIn, float heightIn) : length(lengthIn), width(widthIn), height(heightIn)
    {
        ConstructMesh();
        SetupForDrawing();
    }
    void SetPosition(glm::vec3 positionIn)
    {
        position = positionIn;
    }
    void SetShader(Shader* shaderIn)
    {
        shader = shaderIn;
    }
    glm::vec3 GetPosition()
    {
        return position;
    }
    void Draw()
    {
        glBindVertexArray(VAO);
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        shader->setMat4("model", model);
        
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, mesh.indices.data());
    }
};
