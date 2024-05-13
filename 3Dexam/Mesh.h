#pragma once
#include <vector>
struct Vertex
{
    std::vector<float> vertexInfo;
};
struct Mesh
{
    int strideLength;
    std::vector<Vertex> vertices;
    std::vector<int> indices;
};

