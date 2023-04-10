#include "Triangle.h"

namespace Caustic 
{
    const float EPSILON = 1e-6f;

	bool Triangle::Intersect(const Ray& ray, HitRecord& hitRecord) const
	{
        //Calculate the vectors for two of the edges of the triangle
        Vec3 edge1 = m_V2 - m_V1;
        Vec3 edge2 = m_V3 - m_V1;

        //Calculate the normal of the triangle
        Vec3 normal = Vec3::Cross(edge1, edge2);

        // Calculate the determinant of the matrix formed by the ray direction and the edges
        Vec3 pvec = Vec3::Cross(ray.GetDirection(), edge2);
        float determinant = Vec3::Dot(edge1, pvec);
        
        //Check if ray is parallel to the triangle plane
        if (determinant > -EPSILON && determinant < EPSILON)
        {
            return false;
        }

        // Calculate the inverse of the determinant and use it to calculate the u parameter
        float inv_det = 1.0f / determinant;
        Vec3 tvec = ray.GetOrigin() - m_V1;
        float u = Vec3::Dot(tvec, pvec) * inv_det;

        // Check if the u parameter is outside the range [0, 1]
        if (u < 0.0f || u > 1.0f)
        {
            return false;
        }

        // Calculate the v parameter using the dot product of the ray direction and another edge
        Vec3 qvec = Vec3::Cross(tvec, edge1);
        float v = Vec3::Dot(ray.GetDirection(), qvec) * inv_det;

        // Check if the v parameter is outside the range [0, 1] or if the sum of u and v is greater than 1
        if (v < 0.0f || u + v > 1.0f)
        {
            return false;
        }

        // Calculate the distance along the ray to the intersection point
        float distance = Vec3::Dot(edge2, qvec) * inv_det;

        // Check if the intersection point is within the distance range
        if (distance < ray.GetTMin() || distance > ray.GetTMax())
        {
            return false;
        }

        // Store the intersection point and other relevant data in the HitRecord
        hitRecord.m_Distance = distance;
        hitRecord.m_IntersectionPoint = ray.PointAt(distance);
        hitRecord.m_Normal = normal;
        hitRecord.m_Normal.Normalize();

        return true;
	}

}