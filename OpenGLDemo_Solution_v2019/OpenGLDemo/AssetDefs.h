#pragma once
#include"glm.h"

struct SVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;

	SVertex(glm::vec3 _position, glm::vec3 _color, glm::vec2 _uv)
	{
		position = _position;
		color = _color;
		uv = _uv;
	}
};