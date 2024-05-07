#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotSniper.h"


void ShotSniper::SetParam(void)
{
	//  �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	//  ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  �e�̑傫����ݒ�
	scl_ = { 0.8f,0.8f,0.8f };

	//  �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	//  �e�̑��x
	speed_ = 28.0f;

	hpDamage_ = 499;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 600;
	ShotBlastCnt_ = 0;
}

void ShotSniper::UpdateWeapon(void)
{
	//  ���e���ړ�������
	//  �ړ��ʂ̌v�Z(����*�X�s�[�h)
	movePow_ = VScale(dir_, speed_);
	speed_++;



	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);


}
