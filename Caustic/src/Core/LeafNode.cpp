#include "LeafNode.h"

namespace Caustic
{
	LeafNode::LeafNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1) 
		:m_BoundingBox(AABB), m_ChildIdx0(childIdx0), m_ChildIdx1(childIdx1)
	{
		m_NodeIdx = -1;
	}

	LeafNode::LeafNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1)
		: m_NodeIdx(nodeIdx), m_BoundingBox(AABB), m_ChildIdx0(childIdx0), m_ChildIdx1(childIdx1)
	{

	}

	LeafNode::LeafNode(BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles)
		:m_BoundingBox(AABB), m_ChildIdx0(childIdx0), m_ChildIdx1(childIdx1), m_Triangles(triangles)
	{
		m_NodeIdx = -1;
	}

	LeafNode::LeafNode(uint32_t nodeIdx, BoundingBox& AABB, uint32_t childIdx0, uint32_t childIdx1, std::vector<Triangle>& triangles)
		:m_NodeIdx(nodeIdx), m_BoundingBox(AABB), m_ChildIdx0(childIdx0), m_ChildIdx1(childIdx1), m_Triangles(triangles)
	{

	}

	void LeafNode::SetBoundingBox(const BoundingBox& box)
	{
		m_BoundingBox = box;
	}

	void LeafNode::SetTriangles(const std::vector<Triangle>& triangles)
	{
		m_Triangles = triangles;
	}

	void LeafNode::AddTriangle(const Triangle& triangle)
	{
		m_Triangles.push_back(triangle);
	}

	void LeafNode::SetChildAIdx(uint32_t idx)
	{
		m_ChildIdx0 = idx;
	}

	void LeafNode::SetChildBIdx(uint32_t idx)
	{
		m_ChildIdx1 = idx;
	}
}