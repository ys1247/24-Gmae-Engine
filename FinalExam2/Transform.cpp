#include "Transform.h"
#include <cmath>

namespace Transform {

    Vertex MoveVertex(Vertex point, Vector meter) {
        point.x += meter.x_meter;
        point.y += meter.y_meter;
        return point;
    }

    Vertex RotateVertex(Vertex point, float angle_degree) {
        float angle_rad = angle_degree * (3.14 / 180.0f); 
        float cos_theta = std::cos(angle_rad);
        float sin_theta = std::sin(angle_rad);

        float x = point.x * cos_theta - point.y * sin_theta;
        float y = point.x * sin_theta + point.y * cos_theta;

        point.x = x;
        point.y = y;

        return point;
    }

    Vertex ScaleVertex(Vertex point, Vector meter) {
        point.x *= meter.x_meter;
        point.y *= meter.y_meter;
        return point;
    }

} 