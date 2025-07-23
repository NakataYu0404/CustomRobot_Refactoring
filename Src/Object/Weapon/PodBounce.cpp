#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "PodBounce.h"

void PodBounce::SetParam(void)
{
	// モデル複製
	modelId_ = MV1DuplicateModel(baseModelId_);

	// モデルスケール設定
	scl_ = { SCALE, SCALE, SCALE };

	// 回転初期化
	rot_ = { 0.0f,0.0f,0.0f };

	// 移動速度設定
	speed_ = SPEED;

	// ダメージ設定
	hpDamage_ = HP_DAMAGE;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = SHOT_BLAST_MAX;
	ShotBlastCnt_ = 0;
	bounceCnt_ = BOUNCE_MAX_CNT;
	playerHit_ = false;
}

void PodBounce::UpdateWeapon(void)
{
	// Y座標が境界より大きい場合は下向き、そうでなければ水平
	if (pos_.y > BOUNCE_Y_BORDER)
	{
		dir_.y = -1.0f;
	}
	else
	{
		dir_.y = 0.0f;
	}
	rot_.x += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.z));
	rot_.z += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.x));
	VECTOR movePow = VScale(dir_, speed_);
	pos_ = VAdd(pos_, movePow);
	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);
}

void PodBounce::UpdateBlast(void)
{
	if (bounceCnt_ > 0 && playerHit_ == false)
	{
		Bounce();
		ChangeState(STATE::SHOT);
	}
	else
	{
		bounceCnt_ = 0;
		blastIdxAnim_++;
		if (blastIdxAnim_ + 1 >= blastAnimNum_)
		{
			blastIdxAnim_ = 0;
			ChangeState(STATE::END);
		}
	}
}

void PodBounce::DrawBlast(void)
{
	if (bounceCnt_ <= 0)
	{
		DrawBillboard3D(pos_, BLAST_DRAW_SCALE, BLAST_DRAW_SCALE, BLAST_DRAW_SIZE, BLAST_DRAW_ROT, blastImgs_[blastIdxAnim_], true);
	}
	else
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
		MV1DrawModel(modelId_);
	}
}

float PodBounce::GetRadius(void)
{
	VECTOR scale = { 0.0f,0.0f,0.0f };
	float radius = 0.0f;
	scale.x = scl_.x * 100.0f;
	scale.y = scl_.y * 100.0f;
	scale.z = scl_.z * 100.0f;
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

void PodBounce::Bounce(void)
{
	if (fabsf(hitNormal_.x) > fabsf(hitNormal_.z))
	{
		if ((hitNormal_.x > 0.0f && dir_.x > 0.0f)||(hitNormal_.x < 0.0f && dir_.x < 0.0f))
		{
			dir_.x = hitNormal_.x;
		}
		else
		{
			dir_.x *= -1.0f;
			rot_.x *= AsoUtility::Deg2RadF(-1.0f);
		}
	}
	else if (fabsf(hitNormal_.x) < fabsf(hitNormal_.z))
	{
		if ((hitNormal_.z > 0.0f && dir_.z > 0.0f) || (hitNormal_.z < 0.0f && dir_.z < 0.0f))
		{
			dir_.z = hitNormal_.z;
		}
		else
		{
			dir_.z *= -1.0f;
			rot_.z *= AsoUtility::Deg2RadF(-1.0f);
		}
	}
	else
	{
		dir_.x *= -1;
		dir_.z *= -1;
	}
	bounceCnt_--;
}

