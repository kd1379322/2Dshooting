#include "circle.h"

void C_Circle::Init()
{
	m_tex.Load("Texture/Circle.png");

	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	Moveflg = false;
	alpha = 1.0f;
	color = { 1,0,0,alpha };
	rect = { 0,0,64,64 };
}
