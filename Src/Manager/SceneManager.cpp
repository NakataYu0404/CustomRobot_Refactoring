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

	//  �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	//  3D�p�̏�����
	Init3D();

	//  �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Init3D(void)
{
	//  �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);
	//  ���s���l����悤��
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	//  �J�����ɉf��Ȃ�������`�悵�Ȃ��悤��
	SetUseBackCulling(true);

	//  ���C�g��L����
	SetUseLighting(true);
	//  �f�B���N�V���i�����C�g�����̐ݒ�
	//  �ォ�牺�Ɍ��������C�g
	ChangeLightTypeDir({ 0.00f,-1.00f,0.0f });

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	//  �f���^�^�C��
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
	
	//  �`���O���t�B�b�N�̈�̎w��
	//  (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	//  ��ʂ�������
	ClearDrawScreen();

	//  �J�����ݒ�
	camera_->SetBeforeDraw();

	//  �`��
	scene_->Draw();

	//  �J�����f�o�b�O�p
	camera_->Draw();



	//  �Ó]�E���]
	fader_->Draw();


}

void SceneManager::Release(void)
{
	camera_->Release();

	scene_->Release();



}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	//  �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	//  �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	//  �t�F�[�h�A�E�g(�Ó])���J�n����
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

	//  �f���^�^�C��
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

	//  �V�[��ID�ύX�O�ɃJ�X�^���V�[����������(�����Q�[��)
	if (sceneId_ == SCENE_ID::CUSTOM)
	{
		//  �v���C���[�̃|�C���^��ۊǂ��āA�Q�[���V�[���ɉ�����������
		for (int i = 0; i < 2; i++)
		{
			player_[i] = custom_->GetPlayer(i);
		}
	}

	//  �V�[����ύX����
	sceneId_ = sceneId;

	//  ���݂̃V�[�������
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
		//  �ۊǂ����|�C���^���Q�[���V�[���ɑ���

		game_->SetPlayer(player_);
		break;
	}

	//  �ύX��̃V�[�����Q�[����������
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
		//  ���]��
		if (fader_->IsEnd())
		{
			//  ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		//  �Ó]��
		if (fader_->IsEnd())
		{
			camera_->Release();
			//  ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			camera_->Init();
			//  �Ó]���疾�]��
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


