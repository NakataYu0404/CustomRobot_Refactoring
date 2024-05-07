#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "../Manager/Camera.h"
#include "../Scene/TitleScene.h"
#include "../Scene/CustomScene.h"
#include "../Scene/GameScene.h"
#include "../Object/PlayerBase.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	camera_ = std::make_shared<Camera>();
	camera_->Init();

	fader_ = std::make_unique<Fader>();
	fader_->Init();


	isSceneChanging_ = false;

	//  デルタタイム
	preTime_ = std::chrono::system_clock::now();

	//  3D用の初期化
	Init3D();

	//  初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Init3D(void)
{
	//  背景色設定
	SetBackgroundColor(0, 139, 139);
	//  奥行を考えるように
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	//  カメラに映らない部分を描画しないように
	SetUseBackCulling(true);

	//  ライトを有効に
	SetUseLighting(true);
	//  ディレクショナルライト方向の設定
	//  上から下に向かうライト
	ChangeLightTypeDir({ 0.00f,-1.00f,0.0f });

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	//  デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;


	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		scene_->Update();
		
	}

	camera_->Update();



}

void SceneManager::Draw(void)
{
	
	//  描画先グラフィック領域の指定
	//  (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	//  画面を初期化
	ClearDrawScreen();

	//  カメラ設定
	camera_->SetBeforeDraw();

	//  描画
	scene_->Draw();

	//  カメラデバッグ用
	camera_->Draw();



	//  暗転・明転
	fader_->Draw();


}

void SceneManager::Release(void)
{
	camera_->Release();

	scene_->Release();



}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	//  フェード処理が終わってからシーンを変える場合もあるため、
	//  遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	//  フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

std::weak_ptr<Camera> SceneManager::GetCamera(void)
{
	return camera_;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;

	//  デルタタイム
	deltaTime_ = 1.0f / 60.0f;

}

SceneManager::~SceneManager(void)
{
	delete instance_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	//  シーンID変更前にカスタムシーンだったら(次がゲーム)
	if (sceneId_ == SCENE_ID::CUSTOM)
	{
		//  プレイヤーのポインタを保管して、ゲームシーンに横流ししたい
		for (int i = 0; i < 2; i++)
		{
			player_[i] = custom_->GetPlayer(i);
		}
	}

	//  シーンを変更する
	sceneId_ = sceneId;

	//  現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = std::make_shared<TitleScene>();
		break;
	case SCENE_ID::CUSTOM:
		scene_ = std::make_shared<CustomScene>();
		custom_ = std::dynamic_pointer_cast<CustomScene>(scene_);
		break;
	case SCENE_ID::GAME:
		scene_ = std::make_shared<GameScene>();
		game_ = std::dynamic_pointer_cast<GameScene>(scene_);
		//  保管したポインタをゲームシーンに送る

		game_->SetPlayer(player_);
		break;
	}

	//  変更後のシーンがゲームだったら
	if (sceneId_ == SCENE_ID::GAME)
	{
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		//  明転中
		if (fader_->IsEnd())
		{
			//  明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		//  暗転中
		if (fader_->IsEnd())
		{
			camera_->Release();
			//  完全に暗転してからシーン遷移
			DoChangeScene(waitSceneId_);
			camera_->Init();
			//  暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


