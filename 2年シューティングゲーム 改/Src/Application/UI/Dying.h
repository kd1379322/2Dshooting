#pragma once
class C_Dying
{
public:
	C_Dying() {}
	~C_Dying() { Release(); }

	void InitDying();
	void UpdateDying();
	void DrawDying();

private:

	void Release();		// ‰ğ•úˆ—

	float Alpha;
	bool tenmetuflg;

	Math::Vector2 m_pos;
	Math::Vector2 m_scale;
	Math::Matrix m_scaleMat;	//Šg‘ås—ñ
	Math::Matrix m_transMat;	//ˆÚ“®s—ñ
	Math::Matrix m_mat;
	KdTexture m_tex;			//‰æ‘œ—p	


};
