#include "Bullet.h"

void C_Bullet::Init(Math::Vector2 p_pos)
{
	Moveflg = true;

	m_pos = p_pos;
	rect = { 0,0,64,64 };

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
	SHADER.m_spriteShader.DrawTex(m_tex, rect, 1.0f);//画像の描画
}

void C_Bullet::ImGuiUpdate()
{
}
