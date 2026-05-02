#include "Player.h"


void C_Player::Init()
{
	m_Tex.Load("Texture/player.png");

	Moveflg = true;
	playerAlpha = 1.0f;
	Hp = MHp;
	m_pos = { -300,0 };
	
	m_transMat		= Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat		= Math::Matrix::CreateScale(1, 1, 0);
	m_rotationMat	= Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	m_mat			= m_scaleMat * m_rotationMat * m_transMat;
}

void C_Player::Update()
{
	if (!Moveflg)return;
	float x = 0.0f;
	float y = 0.0f;

	// 入力取得
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)  x -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x += 1.0f;
	if (GetAsyncKeyState(VK_UP) & 0x8000)    y += 1.0f;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)  y -= 1.0f;

	// 長さを計算
	float length = sqrtf(x * x + y * y);

	// 正規化（斜めのときだけ効く）
	if (length > 0.0f)
	{
		x /= length;
		y /= length;
	}

	// 移動
	m_pos.x += x * m_moveSpeed;
	m_pos.y += y * m_moveSpeed;
	
	if (m_pos.x < ScreenLeft + PlayerSize)  m_pos.x = ScreenLeft + PlayerSize;
	if (m_pos.x > ScreenRight - PlayerSize) m_pos.x = ScreenRight - PlayerSize;
	if (m_pos.y > ScreenTop - PlayerSize)   m_pos.y = ScreenTop - PlayerSize;
	if (m_pos.y < ScreenBottom + PlayerSize)m_pos.y = ScreenBottom + PlayerSize;

	if (DamegeIframes)
	{
		DamegeIframesCnt++;

		// 点滅（10フレームごとに切り替え）
		if ((DamegeIframesCnt / 10) % 2 == 0)
		{
			playerAlpha = 0.3f; // 薄い
		}
		else
		{
			playerAlpha = 1.0f; // 通常
		}

		if (DamegeIframesCnt >= 120)
		{
			playerAlpha = 1.0f;
			DamegeIframesCnt = 0;
			DamegeIframes = false;
		}
	}
	

	m_transMat		= Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat		= Math::Matrix::CreateScale(1, 1, 0);
	m_rotationMat	= Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));
	m_mat			= m_scaleMat * m_rotationMat * m_transMat;
}

void C_Player::Draw2D(int i)
{
	if (!Moveflg)return;

	switch (i)
	{
	case 1:
		rect = { 0, 0, 64, 64 };
		break;
	case 2:
		rect = { 64,0,64,64 };
		break;
	case 3:
		rect = { 128,0,64,64 };
		break;
	default:
		rect = { 0,0,64,64 };
		break;
	}
	

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_Tex, rect, playerAlpha);//画像の描画

}

void C_Player::ImGuiUpdate()
{
	/*ImGui::Text("x = %f", m_pos.x);
	ImGui::Text("y = %f", m_pos.y);
	ImGui::Text("Hp = %d", Hp);*/

}

bool C_Player::EnemyHit(Math::Vector2 p_pos)
{
	const float x = m_pos.x - p_pos.x;
	const float y = m_pos.y - p_pos.y;
	const float z = sqrt(x * x + y * y);

	if (Moveflg)
	{
		if (z < 64 && !DamegeIframes)
		{
			Hp -= 1;
			DamegeIframes = true;
			if (Hp == 0)Moveflg = false;
			return true;
		}
		else
		{
			return false;
		}

	}
}
