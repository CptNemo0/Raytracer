#pragma once
#include "vec.h"
#include "ray.h"
#include "plane.h"
#include "geometry.h"
#include "raytracer_math.h"

namespace primitives
{
	class Triangle : public Geometry
	{
	public:
		Triangle(const math::vec3& a, const math::vec3& b, const math::vec3& c)
		{
			vertices[0] = a;
			vertices[1] = b;
			vertices[2] = c;
			normals[0] = math::cross(b - a, c - a);
			normals[1] = normals[0];
			normals[2] = normals[0];
		};

		Triangle(const math::vec3& a, const math::vec3& b, const math::vec3& c, const math::vec3& na, const math::vec3& nb, const math::vec3& nc)
		{
			vertices[0] = a;
			vertices[1] = b;
			vertices[2] = c;
			normals[0] = na;
			normals[1] = nb;
			normals[2] = nc;
		};

		bool IntersectTriangle(const intersections::Ray& ray, const math::vec3& A, const math::vec3& B, const math::vec3& C, math::vec3& intersectionP)
		{
			math::vec3 AB = B - A;
			math::vec3 AC = C - A;
			math::vec3 BC = C - B;
			math::vec3 CA = A - C;
			math::vec3 N = math::cross(AB, AC);
			float dot = N.dot(ray.getDirection());
			if (fabsf(dot) < 0.00001f)
			{
				return false;
			}
			float f = 1.0f / dot;
			math::vec3 s = A - ray.getOrigin();
			float t = f * N.dot(s);
			if (t < 0.0f)
			{
				return false;
			}
			
			intersectionP = ray.solveParametricEquation(t);

			math::vec3 AP = intersectionP - A;
			math::vec3 BP = intersectionP - B;
			math::vec3 CP = intersectionP - C;
			math::vec3 v1 = math::cross(AB, AP);
			math::vec3 v2 = math::cross(BC, BP);
			math::vec3 v3 = math::cross(CA, CP);

			if (v1.dot(N) >= 0.0f && v2.dot(N) >= 0.0f && v3.dot(N) >= 0.0f)
			{
				return true;
			}

			return false;
		}

		intersections::IntersectionResult Intersects(const intersections::Ray& ray, float range)
		{
			intersections::IntersectionResult result;
			result.type = intersections::IntersectionResult::MISS;

			Plane p(normals[0], vertices[0]);
			intersections::IntersectionResult planeResult = p.Intersects(ray, range);
			if (planeResult.type == intersections::IntersectionResult::MISS)
			{
				return planeResult;
			}

			float D = -normals[0].dot(vertices[0]);
			float t = -(normals[0].dot(ray.getOrigin()) + D) / normals[0].dot(ray.getDirection());

			math::vec3 fa = vertices[0] - planeResult.LPOINT;
			math::vec3 fb = vertices[1] - planeResult.LPOINT;
			math::vec3 fc = vertices[2] - planeResult.LPOINT;

			if (t < 0 || (range > 0 && t > range))
			{
				return result;
			}
			math::vec3 intersectionP = ray.solveParametricEquation(t);

			math::vec3 v1 = math::cross(fb - fa, intersectionP - fa);
			math::vec3 v2 = math::cross(fc - fb, intersectionP - fb);
			math::vec3 v3 = math::cross(fa - fc, intersectionP - fc);

			if (v1.dot(normals[0]) >= 0.0f && v2.dot(normals[1]) >= 0.0f && v3.dot(normals[2]) >= 0.0f)
			{
				result.type = intersections::IntersectionResult::HIT;
				result.LPOINT = intersectionP;
				result.intersectionNormal = normals[0];
				result.distance = t;
			}

			return result;
		}

		friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle)
		{
			os <<"Triangle: \n(" << "vertices: ["
			   << triangle.vertices[0] << ", "
			   << triangle.vertices[1] << ", "
			   << triangle.vertices[2] << "]\n"
			   << "normals: ["
			   << triangle.normals[0] << ", "
			   << triangle.normals[1] << ", "
			   << triangle.normals[2] << "]\n";
			return os;
		}

		math::vec3 vertices[3];
		math::vec3 normals[3];
	};

}
