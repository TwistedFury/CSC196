#pragma once
#include "Model.h"
#include "Renderer.h"


void swaws::Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
{
	renderer.SetColor(color.r, color.g, color.b);

	for (int i = 0; i < m_verts.size() - 1; i++)
	{
		vec2 p1 = (m_verts[i].Rotate(math::DegToRad(rotation)) * scale) + position;
		vec2 p2 = (m_verts[i + 1].Rotate(math::DegToRad(rotation))  * scale) + position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void swaws::Model::Draw(Renderer& renderer, Transform& transform)
{
	Draw(renderer, transform.position, transform.rotation, transform.scale);
}
