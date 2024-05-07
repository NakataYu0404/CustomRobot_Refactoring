#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotSniper.h"


void ShotSniper::SetParam(void)
{
	//  使用メモリ容量と読み込み時間削減のため
	//  モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  弾の大きさを設定
	scl_ = { 0.8f,0.8f,0.8f };

	//  弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	//  弾の速度
	speed_ = 28.0f;

	hpDamage_ = 499;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 600;
	ShotBlastCnt_ = 0;
}

void ShotSniper::UpdateWeapon(void)
{
	//  ↓弾を移動させる
	//  移動量の計算(方向*スピード)
	movePow_ = VScale(dir_, speed_);
	speed_++;



	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);


}
