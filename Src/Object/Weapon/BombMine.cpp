#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "BombMine.h"


void BombMine::SetParam(void)
{
	//  �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	//  ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  �e�̑傫����ݒ�
	scl_ = { 0.8f,0.8f,0.8f };

	//  �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	//  �e�̑��x
	speed_ = 8.0f;

	hpDamage_ = 75;
	stunDamage_ = hpDamage_;

	ShotBlastCnt_ = 0;

	moveDistance = 0.0f;

	ShotBlastMax_ = 600;
	blastCnt_ = 0;
	waitCnt_ = 0;

}

void BombMine::UpdateWeapon(void)
{
	//  ���e���ړ�������
	//  �ړ��ʂ̌v�Z(����*�X�s�[�h)
	VECTOR movePow = VScale(dir_, speed_);
	//  �ړ������𑪂�
	moveDistance += sqrt((movePow.x * movePow.x) + (movePow.z * movePow.z));
	if ((moveDistance >= (plEnDistance_ / 3.0f) + (fmodf(plEnDistance_, 3.0f))))
	{
		//  �����x�I�ɏd�͂�������
		gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
		pos_ = VAdd(pos_, VScale({ 0.0f,-1.0f,0.0f }, gravityPow_));

	}

	//  �ړ�����(���W+�ړ���) �������l���Ă��Ȃ�
	pos_ = VAdd(pos_, movePow);

	if (pos_.y <= 0)
	{
		ChangeState(STATE::BLAST);
	}

	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

}

void BombMine::UpdateBlast(void)
{
	waitCnt_++;
	if (waitCnt_ < 120)
	{
		return;
	}

	float sclUp = 0.05f;
	if (blastCnt_ == 0)
	{
		//  ����̑傫��(10)�܂Œi�X�ł�������
		scl_.x += sclUp;
		scl_.y += sclUp;
		scl_.z += sclUp;
	}
	//  ���o�ׂ̈ɉ�]������
	rot_.y += 0.05f;

	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

	if (scl_.x > 15.0)
	{
		//  ����̑傫�����傫���Ȃ�����A�����J�E���^����
		blastCnt_++;
	}
	if (blastCnt_ >= 80)
	{
		//  �����J�E���^�������ς��ɂȂ��������
		ChangeState(STATE::END);
	}
}

void BombMine::DrawShot(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_ - 1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_ - 1]);

	MV1DrawModel(modelId_);

}

void BombMine::DrawBlast(void)
{
	if (waitCnt_ < 120)
	{
		MV1DrawModel(modelId_);
		return;
	}

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

void BombMine::Release(void)
{
	MV1DeleteModel(modelId_);
}

bool BombMine::IsShot(void)
{
	if (state_ == STATE::SHOT || state_ == STATE::BLAST)
	{
		return true;
	}

	return false;

}

