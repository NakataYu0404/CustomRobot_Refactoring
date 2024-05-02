#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "PodFreeze.h"

void PodFreeze::SetParam(void)
{
	// 使用メモリ容量と読み込み時間削減のため
	// モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	// 弾の大きさを設定
	scl_ = { 0.8f,0.8f,0.8f };

	// 弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	// 弾の速度
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
	// 地面と平行にしか移動しないためY方向を0に
	if (pos_.y < 160.0f)
	{
		dir_.y = 1.0f;
	}
	else
	{
		dir_.y = 0.0f;
	}
	// 移動量の計算(方向*スピード)
	VECTOR movePow = VScale(dir_, speed_);

	moveDistance += sqrtf((movePow.x * movePow.x) + (movePow.z * movePow.z));
	if (moveDistance >= plEnDistance_)
	{
		ChangeState(STATE::BLAST);
	}


	// 移動処理(座標+移動量) 落下を考えていない
	pos_ = VAdd(pos_, movePow);

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);
}

void PodFreeze::UpdateBlast(void)
{

	scl_ = { 4.0f,4.0f,4.0f };

	// 演出の為に回転させる
	rot_.y += 0.05f;

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);

		// 特定の大きさより大きくなったら、持続カウンタを回す
		blastCnt_++;
	if (blastCnt_ >= 120)
	{
		// 持続カウンタがいっぱいになったら消す
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
