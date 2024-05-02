#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());

	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::TITLE);
	modelSkyId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Sky.mv1").c_str());
	rotY_ = 0.0f;
}

void TitleScene::Update(void)
{

	MV1SetScale(modelSkyId_, { 2.0f,2.0f,2.0f });
	MV1SetPosition(modelSkyId_, { 0.0f,0.0f,0.0f });
	MV1SetRotationXYZ(modelSkyId_, { 0.0f,rotY_,0.0f });
	rotY_ += 0.005f;

	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)|| ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN)|| ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)||ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CUSTOM);
	}

}

void TitleScene::Draw(void)
{
	VECTOR pos = { 0.0f, 0.0f, 0.0f };


	MV1DrawModel(modelSkyId_);


	// UI
	DrawGraph(0,0,imgTitle_, true);


}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(modelSkyId_);

}
