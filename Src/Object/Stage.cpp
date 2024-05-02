#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "Stage.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{
	
	// �O���t�@�C����3D���f�������[�h
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Stage.mv1").c_str());
	coverModelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Cover.mv1").c_str());
	charId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Moji.mv1").c_str());

	modelSkyId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Sky.mv1").c_str());

	// 3D���f���̑傫����ݒ�(������XYZ�̔{��)
	MV1SetScale(modelId_, { 1.0f,1.0f,1.0f });
	MV1SetScale(coverModelId_, { 1.0f,1.0f,1.0f });

	MV1SetScale(charId_, { 1.0f,1.0f,1.0f });
	
	MV1SetScale(modelSkyId_, {2.0f,2.0f,2.0f });

	// 3D���f���̈ʒu(������3D���W)
	MV1SetPosition(modelId_, { 0.0f,0.0f,0.0f });
	MV1SetPosition(coverModelId_, { 0.0f,0.0f,0.0f });

	MV1SetPosition(charId_, { 0.0f,0.0f,0.0f });
	MV1SetPosition(modelSkyId_, { 0.0f,0.0f,0.0f });

	// 3D���f���̌���(�����́AXYZ�̉�]�� �P�ʂ̓��W�A��)
	MV1SetRotationXYZ(modelId_, { 0.0f,0.0f,0.0f });
	MV1SetRotationXYZ(coverModelId_, { 0.0f,0.0f,0.0f });

	MV1SetRotationXYZ(charId_, { 0.0f,0.0f,0.0f });
	MV1SetRotationXYZ(modelSkyId_, { 0.0f,0.0f,0.0f });

	// �Փ˔�����(�R���C�_)�̍쐬
	MV1SetupCollInfo(modelId_);
	MV1SetupCollInfo(coverModelId_);

}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, shadowH);
	// ���f���̕`��
	MV1DrawModel(modelId_);
	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

	MV1DrawModel(charId_);
	MV1DrawModel(modelSkyId_);

}

void Stage::Release(void)
{
	// ���[�h���ꂽ3D���f����������������
	MV1DeleteModel(modelId_);
	MV1DeleteModel(coverModelId_);
	MV1DeleteModel(charId_);
	MV1DeleteModel(charId_);
	MV1DrawModel(modelSkyId_);


}

int Stage::GetModelId(void)
{
	return modelId_;
}

int Stage::GetCoverModelId(void)
{
	return coverModelId_;
}

void Stage::SetShadowH(int Hand)
{
	shadowH = Hand;
}

