#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ResourceManager.h"
#include "BombCannon.h"


void BombCannon::SetParam(void)
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

	hpDamage_ = 30;
	stunDamage_ = hpDamage_;

	ShotBlastCnt_ = 0;

	moveDistance = 0.0f;

	dirFlag = false;

	ShotBlastMax_ = 600;
	blastCnt_ = 0;

	crossHairId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_CROSSHAIR);
	crosshairPos_ = enemyPos_;
	crosshairScl_ = { 0.8f,0.8f,0.8f };
	crosshairRot_ = { 0.0f,0.0f,0.0f };
	
	crosshairFlag_ = false;
}

void BombCannon::UpdateWeapon(void)
{
	//  ���e���ړ�������
	//  �ړ��ʂ̌v�Z(����*�X�s�[�h)
	VECTOR movePow = VScale(dir_, speed_);
	//  ���������ɃW�����v���Ă������ǂ����ŏ����𕪂���
	if (!isJump_ && posFire_.y <= enemyPos_.y+0.5f)
	{
		//  �ړ������𑪂�
		moveDistance += sqrt((movePow.x * movePow.x) + (movePow.z * movePow.z));
		if ((moveDistance >= (plEnDistance_ / 2.0f) + (fmodf(plEnDistance_, 2.0f))) && dirFlag == false)
		{
			//  �e�̈ړ��������G�Ǝ��������̔����ȏ�ɂȂ����珈��
			moveDistance = 0.0f;
			dir_.y *= -1.0f;
			dirFlag = true;
		}
	}
	//  �ړ�����(���W+�ړ���) �������l���Ă��Ȃ�
	pos_ = VAdd(pos_, movePow);
	if (crosshairFlag_ == false)
	{
		crosshairFlag_ = true;
		crosshairPos_.x += movePow.x*12.0f;
		crosshairPos_.y = 0.0f;
		crosshairPos_.z += movePow.z*12.0f;
	}
	////  �����x�I�ɏd�͂�������
	//gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
	//pos_ = VAdd(pos_, VScale({ 0.0f,-1.0f,0.0f }, gravityPow_));

	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

	MV1SetScale(crossHairId_, scl_);
	MV1SetRotationXYZ(crossHairId_, rot_);
	MV1SetPosition(crossHairId_, crosshairPos_);
}

void BombCannon::UpdateBlast(void)
{
	float sclUp = 0.1f;
	if (blastCnt_ == 0)
	{
		//  ����̑傫��(10)�܂Œi�X�ł�������
		scl_.x += sclUp;
		scl_.y += sclUp;
		scl_.z += sclUp;
	}
	//  ���o�ׂ̈ɉ�]������
	rot_.y+=0.05f;

	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

	if (scl_.x > 10.0)
	{
		//  ����̑傫�����傫���Ȃ�����A�����J�E���^����
		blastCnt_++;
	}
	if (blastCnt_ >= 60)
	{
		//  �����J�E���^�������ς��ɂȂ��������
		ChangeState(STATE::END);
	}
}

void BombCannon::DrawShot(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_ - 1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_ - 1]);

	MV1DrawModel(crossHairId_);
	MV1DrawModel(modelId_);

}

void BombCannon::DrawBlast(void)
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

void BombCannon::Release(void)
{
	MV1DeleteModel(modelId_);
	MV1DeleteModel(crossHairId_);
}

bool BombCannon::IsShot(void)
{
	if (state_ == STATE::SHOT || state_ == STATE::BLAST)
	{
		return true;
	}

	return false;
	
}

