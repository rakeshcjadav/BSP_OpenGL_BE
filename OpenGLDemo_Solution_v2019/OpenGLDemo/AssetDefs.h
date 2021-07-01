#pragma once
#include"glm.h"

struct SVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
	glm::vec3 normal;

	SVertex(glm::vec3 _position, glm::vec3 _color, glm::vec2 _uv, glm::vec3 _normal)
	{
		position = _position;
		color = _color;
		uv = _uv;
		normal = _normal;
	}
};