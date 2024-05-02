#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "PodSticky.h"

void PodSticky::SetParam(void)
{
	// �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
// ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	// �e�̑傫����ݒ�
	scl_ = { 0.4f,0.4f,0.4f };

	// �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	// �e�̑��x
	speed_ = 8.0f;

	hpDamage_ = 50;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 0;
	ShotBlastCnt_ = 0;


	playerHit_ = false;
	stickFlag_ = false;
}

void PodSticky::UpdateWeapon(void)
{
	if (!stickFlag_)
	{

		// �n�ʂƕ��s�ɂ����ړ����Ȃ�����Y������0��
		if (pos_.y > 25.0f)
		{
			dir_.y = -1.0f;
		}
		else
		{
			dir_.y = 0.0f;
		}

		rot_.x += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.z));
		rot_.z += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.x));


		// �ړ��ʂ̌v�Z(����*�X�s�[�h)
		VECTOR movePow = VScale(dir_, speed_);

		// �ړ�����(���W+�ړ���) �������l���Ă��Ȃ�
		pos_ = VAdd(pos_, movePow);
	}
	// �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	// �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	// �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);
}

void PodSticky::UpdateBlast(void)
{

	// �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	// �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	// �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);

	stickFlag_ = true;
	state_ = STATE::SHOT;
}

void PodSticky::DrawBlast(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_ - 1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_ - 1]);

	MV1DrawModel(modelId_);
}

float PodSticky::GetRadius(void)
{
	VECTOR scale = { 0.0f,0.0f,0.0f };
	float radius = 0.0f;
	scale.x = scl_.x * 100.0f;
	scale.y = scl_.y * 100.0f;
	scale.z = scl_.z * 100.0f;
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

