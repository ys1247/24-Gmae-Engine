#pragma once
namespace Transform
{
	struct Vertex
	{
		float x;
		float y;
	};

	struct Vector
	{
		float x_meter;
		float y_meter;
	};

	Vertex MoveVertex(Vertex point, Vector meter);
	Vertex RotateVertex(Vertex point, float angle_degree);
	Vertex ScaleVertex(Vertex point, Vector meter);

};