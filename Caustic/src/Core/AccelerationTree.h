#pragma once

#include "BoundingBox.h"
#include "LeafNode.h"

#include <vector>

namespace Caustic
{
	class AccelerationTree
	{
	public:
		AccelerationTree() = default;

		void AddNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1);
		void AddNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles);
		void AddNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1);
		void AddNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles);
		void BuildAccelerationTree(uint32_t parentIdx, uint32_t depth, std::vector<Triangle>& triangles);

		const std::vector<LeafNode>& GetLeafNodes() const { return m_LeafNodes; }
	private:
		std::vector<LeafNode> m_LeafNodes;
		const uint32_t m_MaxBoxTriangleCount = 20;
	};
}