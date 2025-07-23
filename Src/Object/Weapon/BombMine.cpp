#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "BombMine.h"


void BombMine::SetParam(void)
{
	//  モデル複製
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  モデルスケール設定
	scl_ = { SCALE, SCALE, SCALE };

	//  回転初期化
	rot_ = { 0.0f,0.0f,0.0f };

	//  移動速度設定
	speed_ = SPEED;

	//  ダメージ設定
	hpDamage_ = HP_DAMAGE;
	stunDamage_ = hpDamage_;

	ShotBlastCnt_ = 0;
	moveDistance = 0.0f;
	ShotBlastMax_ = SHOT_BLAST_MAX;
	blastCnt_ = 0;
	waitCnt_ = 0;
}

void BombMine::UpdateWeapon(void)
{
	//  移動量計算
	VECTOR movePow = VScale(dir_, speed_);
	//  移動距離を測る
	moveDistance += sqrt((movePow.x * movePow.x) + (movePow.z * movePow.z));
	if ((moveDistance >= (plEnDistance_ / 3.0f) + (fmodf(plEnDistance_, 3.0f))))
	{
		//  加速度的に重力を加える
		gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
		pos_ = VAdd(pos_, VScale({ 0.0f,-1.0f,0.0f }, gravityPow_));

	}
	//  移動処理(座標+移動量) 落下を考えていない
	pos_ = VAdd(pos_, movePow);

	if (pos_.y <= 0)
	{
		ChangeState(STATE::BLAST);
	}

	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);

}

void BombMine::UpdateBlast(void)
{
	waitCnt_++;
	if (waitCnt_ < BLAST_WAIT_CNT)
	{
		return;
	}

	if (blastCnt_ == 0)
	{
		//  特定の大きさ(10)まで段々でかくする
		scl_.x += BLAST_SCL_UP;
		scl_.y += BLAST_SCL_UP;
		scl_.z += BLAST_SCL_UP;
	}
	//  演出の為に回転させる
	rot_.y += BLAST_ROT_Y;

	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);

	if (scl_.x > BLAST_MAX_SCL)
	{
		//  特定の大きさより大きくなったら、持続カウンタを回す
		blastCnt_++;
	}
	if (blastCnt_ >= BLAST_MAX_CNT)
	{
		//  持続カウンタがいっぱいになったら消す
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
	if (waitCnt_ < BLAST_WAIT_CNT)
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

