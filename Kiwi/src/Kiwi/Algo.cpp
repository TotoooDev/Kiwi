#include <Kiwi/Algo.h>
#include <glm/fwd.hpp>
#include <iostream>

namespace Kiwi
{
    namespace Algo
    {
        namespace FindCollisionPoints
        {
            CollisionPoints CircleCircle(const CircleCollider* a, const Transform* transformA, const CircleCollider* b, const Transform* transformB)
            {
                CollisionPoints points;
                float distance = glm::sqrt((transformB->Position.x - transformA->Position.x) * (transformB->Position.x - transformA->Position.x) +
                                           (transformB->Position.y - transformA->Position.y) * (transformB->Position.y - transformA->Position.y));
                
                if (distance > a->Radius + b->Radius)
                {
                    points.HasCollision = false;
                    return points;
                }

                points.HasCollision = true;
                points.A = transformB->Position - transformA->Position;
                points.B = points.A * -1.0f;
                points.Normal = glm::normalize(points.B - points.A);
                points.Depth = points.Normal.length();
                return points;
            }


            CollisionPoints CircleLine(const CircleCollider* a, const Transform* transformA, const LineCollider* b, const Transform* transformB)
            {
                CollisionPoints points;
                points.HasCollision = false;

                glm::vec2 beginLine = transformB->Position;
                glm::vec2 endLine = transformB->Position + b->Vec * b->Length;
                glm::vec2 centerToRayBegin = beginLine - transformA->Position + a->Center;
                glm::vec2 centerToRayEnd = endLine - transformA->Position + a->Center;

                float A = glm::dot(b->Vec, b->Vec);
                float B = 2 * glm::dot(centerToRayBegin, b->Vec);
                float C = glm::dot(centerToRayBegin, centerToRayBegin) - a->Radius * a->Radius;

                float discriminant = B * B - 4 * A * C;
                if (discriminant < 0)
                {
                    points.HasCollision = false;
                    return points;
                }

                discriminant = glm::sqrt(discriminant);

                float t1 = (-B - discriminant) / (2 * A);
                float t2 = (-B + discriminant) / (2 * A);

                if ((t1 > 0 && t1 < b->Length) || (t2 > 0 && t1 < b->Length))
                {
                    glm::vec2 directionFurthestA = centerToRayBegin - centerToRayEnd;
                    points.A = glm::normalize(directionFurthestA) * a->Radius + (transformA->Position + a->Center);
                    points.B = directionFurthestA + transformB->Position;
                    points.Normal = glm::normalize(points.B - points.A);
                    points.Depth = (points.B - points.A).length();
                    points.HasCollision = true;
                }

                return points;
            }
        }
    }
}
