#pragma once

#include "BoundingBox.h"
#include "Triangle.h"

#include <vector>

namespace Caustic
{
	class LeafNode
	{
	public:
		LeafNode() = default;
		LeafNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1);
		LeafNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1);
		LeafNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles);
		LeafNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles);

		const int& GetNodeIdx() { return m_NodeIdx; }
		const std::vector<Triangle>& GetTriangles() { return m_Triangles; }
		const BoundingBox& GetBoundingBox() { return m_BoundingBox; }
		const int& GetChildAIdx() const { return m_ChildIdx0; }
		const int& GetChildBIdx() const { return m_ChildIdx1; }

		void SetBoundingBox(const BoundingBox& box);
		void SetTriangles(const std::vector<Triangle>& triangles);
		void AddTriangle(const Triangle& triangle);
		void SetChildAIdx(uint32_t idx);
		void SetChildBIdx(uint32_t idx);
	private:
		int m_NodeIdx = -1;
		BoundingBox m_BoundingBox;
		std::vector<Triangle> m_Triangles;
		int m_ChildIdx0 = -1;
		int m_ChildIdx1 = -1;
	};
}