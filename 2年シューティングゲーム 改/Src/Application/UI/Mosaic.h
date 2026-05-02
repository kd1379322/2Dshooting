#pragma once
class C_Mosaic
{
public:
	C_Mosaic() {}
	~C_Mosaic() { Release(); }

	void Init();
	void Update();
	void Draw();

	void Up();
	void Down();

	float GetAlpha() { return Alpha; }

	bool GetMax_A() { return MaxAlpha; }

	bool GetMin_A() { return MinAlpha; }

private:

	void Release();		// ‰ğ•úˆ—

	bool flg;

	bool MaxAlpha = false;

	bool MinAlpha = false;

	float Alpha = 1.0f;

	Math::Vector2 m_pos;
	Math::Vector2 m_scale;
	Math::Matrix m_scaleMat;	//Šg‘ås—ñ
	Math::Matrix m_transMat;	//ˆÚ“®s—ñ
	Math::Matrix m_mat;
	KdTexture m_tex;			//‰æ‘œ—p	


};
