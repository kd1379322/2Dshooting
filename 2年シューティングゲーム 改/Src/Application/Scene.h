#pragma once


class C_Title;

class C_GamePlay;

class C_Mosaic;

enum SceneType
{
	Title,
	GamePlay,
	Result
};

class Scene
{
private:

	//シーン管理用変数
	SceneType nowScene;

	std::shared_ptr<C_Title>		m_Title;
	std::shared_ptr <C_GamePlay>	m_GamePlay;

	std::shared_ptr<C_Mosaic>		m_mosaic;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:

	bool Spacekeyflg;


	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
