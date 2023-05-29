#pragma once

#include "Core/Vertex.h"
#include "Core/Triangle.h"

#include <vector>
#include <glm/glm.hpp>

namespace Caustic
{
    class Mesh 
    {
    public:
        // Constructors
        Mesh() = default;
        Mesh(uint32_t materialIdx, uint32_t meshIdx)
            :m_MaterialIdx(materialIdx), m_MeshIdx(meshIdx){}

        //Getters
        const uint32_t GetMaterialIdx() const { return m_MaterialIdx; }
        const uint32_t GetMeshIdx() const { return m_MeshIdx; }
        const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
        const std::vector<Triangle>& GetTriangles() const { return m_Triangles; }

        void PushVertex(const Vertex& vertex);
        void PushTriangle(const Triangle& triangle);
        void PushTriangleIndexToVertex(const uint32_t& vertexIdx, const uint32_t& triangleIdx);
        void UpdateVertexNormals();
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<Triangle> m_Triangles;

        uint32_t m_MeshIdx;
        uint32_t m_MaterialIdx = 0;
    };
}