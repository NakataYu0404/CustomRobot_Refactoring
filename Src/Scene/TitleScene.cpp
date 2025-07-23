#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

// 定数（マジックナンバー）
namespace {
    constexpr float SKYDOME_SCALE = 2.0f;      // スカイドームのスケール
    constexpr float SKYDOME_ROT_SPEED = 0.005f; // スカイドームの回転速度
    constexpr float SKYDOME_POS_X = 0.0f;      // スカイドームX座標
    constexpr float SKYDOME_POS_Y = 0.0f;      // スカイドームY座標
    constexpr float SKYDOME_POS_Z = 0.0f;      // スカイドームZ座標
    constexpr int TITLE_GRAPH_X = 0;           // タイトル画像描画X座標
    constexpr int TITLE_GRAPH_Y = 0;           // タイトル画像描画Y座標
}

TitleScene::TitleScene(void) :resMng_(ResourceManager::GetInstance())
{
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = resMng_.Load(ResourceManager::SRC::IMG_TITLE).handleId_;

	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::TITLE);
	modelSkyId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_SKYDOME);
	rotY_ = 0.0f;
}

void TitleScene::Update(void)
{

	// スカイドームのスケール・位置・回転設定
	MV1SetScale(modelSkyId_, { SKYDOME_SCALE, SKYDOME_SCALE, SKYDOME_SCALE });
	MV1SetPosition(modelSkyId_, { SKYDOME_POS_X, SKYDOME_POS_Y, SKYDOME_POS_Z });
	MV1SetRotationXYZ(modelSkyId_, { 0.0f, rotY_, 0.0f });
	rotY_ += SKYDOME_ROT_SPEED;

	// シーン遷移判定
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CUSTOM);
	}
}

void TitleScene::Draw(void)
{
	VECTOR pos = { SKYDOME_POS_X, SKYDOME_POS_Y, SKYDOME_POS_Z };


	MV1DrawModel(modelSkyId_);

	// タイトルUI描画
	DrawGraph(TITLE_GRAPH_X, TITLE_GRAPH_Y, imgTitle_, true);


}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(modelSkyId_);

}
