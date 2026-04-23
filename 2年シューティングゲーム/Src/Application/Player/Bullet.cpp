#include "Bullet.h"

void C_Bullet::Init(Math::Vector2 p_pos, int p_bcn)
{
	Moveflg = true;

	m_pos.x = p_pos.x + 16;
	m_pos.y = p_pos.y;
	rect = { 0,0,64,64 };

	switch (p_bcn)
	{
	case 1:
		color = { 1,0,0,1 };
		break;
	case 2:
		color = { 0,0,1,1 };
		break;
	case 3:
		color = { 1,1,0,1 };
		break;
	default:
		color = { 1,0,0,1 };
		break;
	}


	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	m_mat = m_scaleMat * m_rotationMat * m_transMat;
}

void C_Bullet::Update()
{
	if (!Moveflg)return;

	m_pos.x += m_moveSpeed;

	if (m_pos.x > ScreenRight + Size)
	{
		Moveflg = false;
	}

	

	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	m_mat = m_scaleMat * m_rotationMat * m_transMat;
}

void C_Bullet::Draw2D()
{
	if (!Moveflg)return;

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(m_tex, Math::Rectangle(0, 0, 64, 64), color);//画像の描画
}

void C_Bullet::ImGuiUpdate()
{
}
