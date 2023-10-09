#include "Utility.h"


namespace PFG
{
	float DistanceToPlane(const glm::vec3& n, const glm::vec3& p, const glm::vec3& q)
	{
		float d = glm::dot((p - q), n);
		return d;
	}

	bool MovingSphereToPlaneCollision(const glm::vec3& n, const glm::vec3& c0, const glm::vec3& c1, GameObject* object, float r, glm::vec3& ci)
	{
		float t = 0.0f;
		float i = 2.5f;

		glm::vec3 q = object->GetPosition();
		glm::vec3 s = object->GetScale();

		float minX = q.x - i * s.x;
		float maxX = q.x + i * s.x;
		float minY = q.y - 4 * s.y;
		float maxY = q.y + 4 * s.y;
		float minZ = q.z - i * s.z;
		float maxZ = q.z + i * s.z;

		glm::vec3 temp = glm::vec3(0.0f, 0.0f, 0.0f);

		temp.x = std::max(minX, std::min(c0.x, maxX));
		temp.y = std::max(minY, std::min(c0.y, maxY));
		temp.z = std::max(minZ, std::min(c0.z, maxZ));

		glm::vec3 temp2 = glm::vec3(0.0f, 0.0f, 0.0f);

		temp2.x = std::max(minX, std::min(c1.x, maxX));
		temp2.y = std::max(minY, std::min(c1.y, maxY));
		temp2.z = std::max(minZ, std::min(c1.z, maxZ));

		float d0 = std::sqrt((temp.x - c0.x) * (temp.x - c0.x) + (temp.y - c0.y) * (temp.y - c0.y) + (temp.z - c0.z) * (temp.z - c0.z));
		float d1 = std::sqrt((temp2.x - c1.x) * (temp2.x - c1.x) + (temp2.y - c1.y) * (temp2.y - c1.y) + (temp2.z - c1.z) * (temp2.z - c1.z));

		//float d0 = DistanceToPlane(n, c0, temp);
		//float d1 = DistanceToPlane(n, c1, temp);

		if (glm::abs(d0) <= r)
		{
			ci = c0;
			t = 0.0f;
			return true;
		}
		if (d0 > r && d1 < r)
		{
			t = (d0 - r) / (d0 - d1);
			ci = (1 - t) * c0 + t * q;
			return true;
		}
		return false;
	}


	bool SphereToSphereCollision(const glm::vec3& c0, const glm::vec3 c1, float r1, float r2, glm::vec3& cp)
	{
		float d = glm::length(c0 - c1);
		glm::vec3 n = glm::vec3(0.0f, 0.0f, 0.0f);

		if (d <= (r1 + r2))
		{
			n = glm::normalize(c0 - c1);
			cp = r1 * n;
			return true;
		}
		return false;
	}

}