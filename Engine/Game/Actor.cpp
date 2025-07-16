#include "Actor.h"
#include "../Renderer/Model.h"

void swaws::Actor::Update(float dt)
{
}

void swaws::Actor::Draw(Renderer& renderer)
{
	m_model->Draw(renderer, m_transform);
}
