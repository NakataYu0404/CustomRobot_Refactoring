#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotElecShock.h"

void ShotElecShock::SetParam(void)
{
	// �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	// ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	// �e�̑傫����ݒ�
	scl_ = { 4.0f,4.0f,4.0f };

	// �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	// �e�̑��x
	speed_ = 10.0f;

	hpDamage_ = 70;
	stunDamage_ = 250;

	ShotBlastMax_ = 30;
	ShotBlastCnt_ = 0;
}

