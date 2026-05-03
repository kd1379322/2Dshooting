#include "Red.h"

void C_Red::Update()
{
	if (!Moveflg)return;

	m_pos.x += m_moveSpeed;

	if (m_pos.x < ScreenLeft - Size)
	{
		Moveflg = false;
	}

	anm++;
	if (anm == 30) {
		rect = { 64,0,64,64 };
	}
	else if (anm == 60)
	{
		anm = 0;
		rect = { 0,0,64,64 };
	}

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

bool C_Red::CheckColor(int i)
{
	if (i == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

