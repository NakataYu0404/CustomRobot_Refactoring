#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotMachine.h"

void ShotMachine::SetParam(void)
{
	//  使用メモリ容量と読み込み時間削減のため
	//  モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  弾の大きさを設定
	scl_ = { 0.8f,0.8f,0.8f };

	//  弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	//  弾の速度
	speed_ = 20.0f;

	hpDamage_ = 65;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 600;
	ShotBlastCnt_ = 0;
}

