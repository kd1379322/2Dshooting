#include "Sound.h"

void C_Sound::Init()
{
	//音量初期値
	Bgmvol = 0.08f;	// MAXは 1.0f
	Sevol  = 0.08f;	// MAXは 1.0f

	//タイトルBGMの読み込み
    //①容量確保
	Title_bgm = std::make_shared<KdSoundEffect>();

	//②音データ読み込み
	Title_bgm->Load("Sound/TitleBGM.wav");

	//③実体化(インスタンス化)(専用スピーカーの作成)
	Title_bgmInst = Title_bgm->CreateInstance(false);

	//④音量設定(0から1の範囲で)
	Title_bgmInst->SetVolume(Bgmvol);

	//⑤音再生(Play関数の引数はループ再生するならtrue・1度だけ鳴らすならfalse)
    //bgmInst->Play(true);


	//ゲームBGMの読み込み
	Game_bgm = std::make_shared<KdSoundEffect>();

	Game_bgm->Load("Sound/GameBGM.wav");

	Game_bgmInst = Game_bgm->CreateInstance(false);

	Game_bgmInst->SetVolume(Bgmvol);

	//⑤音再生(Play関数の引数はループ再生するならtrue・1度だけ鳴らすならfalse)
	//bgmInst->Play(true);


	//リザルトBGMの読み込み 
	Result_bgm = std::make_shared<KdSoundEffect>();

	Result_bgm->Load("Sound/ResultBGM.wav");

	Result_bgmInst = Result_bgm->CreateInstance(false);

	Result_bgmInst->SetVolume(Bgmvol);

	//⑤音再生(Play関数の引数はループ再生するならtrue・1度だけ鳴らすならfalse)
	//bgmInst->Play(true);


	

	// プレイヤーがくらった時のダメージ音SEの読み込み
	PlayerDamage_se = std::make_shared<KdSoundEffect>();

	PlayerDamage_se->Load("Sound/PlayerDamage.wav");

	PlayerDamage_seInst = PlayerDamage_se->CreateInstance(false);

	PlayerDamage_seInst->SetVolume(Sevol);


	

	// 敵がくらった時のダメージ音SEの読み込み
	EnemyDamage_se = std::make_shared<KdSoundEffect>();

	EnemyDamage_se->Load("Sound/EnemyDamage.wav");

	EnemyDamage_seInst = EnemyDamage_se->CreateInstance(false);

	EnemyDamage_seInst->SetVolume(Sevol);


	// 瀕死SEの読み込み
	Hinsi_se = std::make_shared<KdSoundEffect>();

	Hinsi_se->Load("Sound/Hinsi.wav");

	Hinsi_seInst = Hinsi_se->CreateInstance(false);

	Hinsi_seInst->SetVolume(Sevol);
	

	// 決定時の音SEの読み込み
	DecisionSound_se = std::make_shared<KdSoundEffect>();

	DecisionSound_se->Load("Sound/DecisionSound.wav");

	DecisionSound_seInst = DecisionSound_se->CreateInstance(false);

	DecisionSound_seInst->SetVolume(Sevol);


	


	// リザルトのゲーム結果の数字が増えていく音SEの読み込み
	Drum_se = std::make_shared<KdSoundEffect>();

	Drum_se->Load("Sound/Drum.wav");

	Drum_seInst = Drum_se->CreateInstance(false);

	Drum_seInst->SetVolume(Sevol);


	// リザルトのゲーム結果の数字がでた音SEの読み込み
	Levelup_se = std::make_shared<KdSoundEffect>();

	Levelup_se->Load("Sound/LevelUp.wav");

	Levelup_seInst = Levelup_se->CreateInstance(false);

	Levelup_seInst->SetVolume(Sevol);


	// ゲーム開始時のカウントダウンSEの読み込み
	Countdown1_se = std::make_shared<KdSoundEffect>();

	Countdown1_se->Load("Sound/CountDown01.wav");

	Countdown1_seInst = Countdown1_se->CreateInstance(false);

	Countdown1_seInst->SetVolume(Sevol);


	// カウントダウンが1の後になるときの音SEの読み込み
	Countdown2_se = std::make_shared<KdSoundEffect>();

	Countdown2_se->Load("Sound/CountDown02.wav");

	Countdown2_seInst = Countdown2_se->CreateInstance(false);

	Countdown2_seInst->SetVolume(Sevol);


	//開始時
	Start_se = std::make_shared<KdSoundEffect>();

	Start_se->Load("Sound/Start.wav");

	Start_seInst = Start_se->CreateInstance(false);

	Start_seInst->SetVolume(Sevol);


	//終了時
	finish_se = std::make_shared<KdSoundEffect>();

	finish_se->Load("Sound/finish.wav");

	finish_seInst = finish_se->CreateInstance(false);

	finish_seInst->SetVolume(Sevol);


	//機体の色チェンジ
	Chenge_se = std::make_shared<KdSoundEffect>();

	Chenge_se->Load("Sound/Chenge.wav");
	
	Chenge_seInst = Chenge_se->CreateInstance(false);
	
	Chenge_seInst->SetVolume(Sevol);

}

//ゲームBGM
void C_Sound::Game_BGM()
{
	if (Game_bgmInst->IsPlay() == false)
	{
		Title_bgmInst->Stop();
		Result_bgmInst->Stop();
		Game_bgmInst->Play(true);
	}
}

//タイトルBGM
void C_Sound::Title_BGM()
{
	if (Title_bgmInst->IsPlay() == false)
	{
		Game_bgmInst->Stop();
		Result_bgmInst->Stop();
		Title_bgmInst->Play(true);
	}
}

//リザルトBGM  
void C_Sound::Result_BGM()
{
	if (Result_bgmInst->IsPlay() == false)
	{
		Title_bgmInst->Stop();
		Game_bgmInst->Stop();
		Result_bgmInst->Play(true);
	}
}



//プレイヤーがくらった時のダメージ音
void C_Sound::PlayerDamage_SE()
{
	PlayerDamage_seInst->Play();
}


//敵がくらった時のダメージ音
void C_Sound::EnemyDamage_SE()
{
	//if (EnemyDamage_seInst->IsPlay() == false)
	//{
		EnemyDamage_seInst->Play();
	//}
}



//瀕死になった時の音
void C_Sound::Hinsi_SE()
{
	if (Hinsi_seInst->IsPlay() == false)
	{
		Hinsi_seInst->Play();
	}
}



//リザルトのゲーム結果の数字が増えていく音
void C_Sound::drum_SE()
{
	if (Drum_seInst->IsPlay() == false)
	{
		Drum_seInst->Play();
	}
}

//リザルトのゲーム結果の数字がでた音
void C_Sound::LevelUp_SE()
{
	if (Levelup_seInst->IsPlay() == false)
	{
		Drum_seInst->Stop();
		Levelup_seInst->Play();
	}
}

//ゲーム開始時のカウントダウン時の音
void C_Sound::CountDown1_SE()
{
	//if (Countdown1_seInst->IsPlay() == false)
	//{
		Countdown1_seInst->Play();
	//}
}

//カウントダウンが1の後になるときの音
void C_Sound::CountDown2_SE()
{
	if (Countdown2_seInst->IsPlay() == false)
	{
		Countdown2_seInst->Play();
	}
}


//決定時の音
void C_Sound::DecisionSound_SE()
{
	//if(DecisionSound_seInst->IsPlay() == false)
	{
		DecisionSound_seInst->Play();
	}
}

void C_Sound::Start_SE()
{
	Start_seInst->Play();
}

void C_Sound::Finish_SE()
{
	finish_seInst->Play();
}

void C_Sound::Chenge_SE()
{
	Chenge_seInst->Play();
}


//音を一斉に止める
void C_Sound::AllSoundStop()
{
	//PlayerDamage_seInst->Stop();     //プレイヤーがくらった時のダメージ音

	EnemyDamage_seInst->Stop();      //敵がくらった時のダメージ音
	
	Hinsi_seInst->Stop();            //瀕死

	Drum_seInst->Stop();             //リザルトのゲーム結果の数字が増えていく音
	Levelup_seInst->Stop();          //リザルトのゲーム結果の数字がでた音
	Countdown1_seInst->Stop();       //ゲーム開始時のカウントダウン
	Countdown2_seInst->Stop();       //カウントダウンが1の後になるときの音

	DecisionSound_seInst->Stop();    //決定時の音

	Title_bgmInst->Stop();			 //タイトルBGM
	Game_bgmInst->Stop();			 //ゲームBGM
	Result_bgmInst->Stop();			 //リザルトBGM
	Start_seInst->Stop();
	finish_seInst->Stop();
}
