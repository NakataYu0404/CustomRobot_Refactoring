#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotMachine.h"

void ShotMachine::SetParam(void)
{
	//  �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	//  ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  �e�̑傫����ݒ�
	scl_ = { 0.8f,0.8f,0.8f };

	//  �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	//  �e�̑��x
	speed_ = 20.0f;

	hpDamage_ = 65;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 600;
	ShotBlastCnt_ = 0;
}

