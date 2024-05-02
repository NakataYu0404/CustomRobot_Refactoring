#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "PodFreeze.h"

void PodFreeze::SetParam(void)
{
	// �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	// ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	// �e�̑傫����ݒ�
	scl_ = { 0.8f,0.8f,0.8f };

	// �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	// �e�̑��x
	speed_ = 8.0f;

	hpDamage_ = 60;
	stunDamage_ = 480;

	ShotBlastCnt_ = 0;

	moveDistance = 0.0f;

	ShotBlastMax_ = 600;
	blastCnt_ = 0;
}

void PodFreeze::UpdateWeapon(void)
{
	// �n�ʂƕ��s�ɂ����ړ����Ȃ�����Y������0��
	if (pos_.y < 160.0f)
	{
		dir_.y = 1.0f;
	}
	else
	{
		dir_.y = 0.0f;
	}
	// �ړ��ʂ̌v�Z(����*�X�s�[�h)
	VECTOR movePow = VScale(dir_, speed_);

	moveDistance += sqrtf((movePow.x * movePow.x) + (movePow.z * movePow.z));
	if (moveDistance >= plEnDistance_)
	{
		ChangeState(STATE::BLAST);
	}


	// �ړ�����(���W+�ړ���) �������l���Ă��Ȃ�
	pos_ = VAdd(pos_, movePow);

	// �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	// �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	// �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);
}

void PodFreeze::UpdateBlast(void)
{

	scl_ = { 4.0f,4.0f,4.0f };

	// ���o�ׂ̈ɉ�]������
	rot_.y += 0.05f;

	// �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	// �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	// �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

		// ����̑傫�����傫���Ȃ�����A�����J�E���^����
		blastCnt_++;
	if (blastCnt_ >= 120)
	{
		// �����J�E���^�������ς��ɂȂ��������
		ChangeState(STATE::END);
	}
}

void PodFreeze::DrawBlast(void)
{
	COLOR_F tmpCol = weaponColor_[plNum_ - 1];

	switch (plNum_)
	{
	case 1:
		tmpCol = GetColorF(0.8f, 0.3f, 0.2f, 1.0f);
		break;
	case 2:
		tmpCol = GetColorF(0.2f, 0.3f, 0.8f, 1.0f);
		break;
	}

	MV1SetDifColorScale(modelId_, tmpCol);
	MV1SetSpcColorScale(modelId_, tmpCol);
	MV1DrawModel(modelId_);

}

bool PodFreeze::IsShot(void)
{
	if (state_ == STATE::SHOT || state_ == STATE::BLAST)
	{
		return true;
	}

	return false;

}
