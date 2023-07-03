#include "AccelerationTree.h"

static const uint32_t AxisCount = 3;

namespace Caustic
{
	void AccelerationTree::AddNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1)
	{
		LeafNode node(AABB, childIdx0, childIdx1);
		m_LeafNodes.push_back(node);
	}

	void AccelerationTree::AddNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles)
	{
		LeafNode node(AABB, childIdx0, childIdx1, triangles);
		m_LeafNodes.push_back(node);
	}

	void AccelerationTree::AddNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1)
	{
		LeafNode node(nodeIdx, AABB, childIdx0, childIdx1);
		m_LeafNodes.push_back(node);
	}

	void AccelerationTree::AddNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles)
	{
		LeafNode node(nodeIdx, AABB, childIdx0, childIdx1, triangles);
		m_LeafNodes.push_back(node);
	}

	void AccelerationTree::BuildAccelerationTree(uint32_t parentIdx, uint32_t depth, std::vector<Triangle>& triangles)
	{
		if(depth > 100 || triangles.size() <= m_MaxBoxTriangleCount)
		{
			m_LeafNodes[parentIdx].SetTriangles(triangles);
			return;
		}

		BoundingBox BoxA;
		BoundingBox BoxB;

		std::vector<Triangle> childATriangles;
		std::vector<Triangle> childBTriangles;

		m_LeafNodes[parentIdx].GetBoundingBox().Split(depth % AxisCount, BoxA, BoxB);

		for(Triangle& triangle : triangles)
		{
			if(BoundingBox::BoxesIntersection(triangle.GetBoundingBox(), BoxA))
			{
				childATriangles.push_back(triangle);
			}

			if (BoundingBox::BoxesIntersection(triangle.GetBoundingBox(), BoxB))
			{
				childBTriangles.push_back(triangle);
			}
		}

		if(childATriangles.size() > 0)
		{
			this->AddNode(m_LeafNodes.size() - 1, BoxA, -1, -1);
			m_LeafNodes[parentIdx].SetChildAIdx(m_LeafNodes.size() - 1);
			BuildAccelerationTree(m_LeafNodes.size() - 1, depth + 1, childATriangles);
		}
		
		if (childBTriangles.size() > 0)
		{
			this->AddNode(m_LeafNodes.size() - 1, BoxB, -1, -1);
			m_LeafNodes[parentIdx].SetChildBIdx(m_LeafNodes.size() - 1);
			BuildAccelerationTree(m_LeafNodes.size() - 1, depth + 1, childBTriangles);
		}

	}
}