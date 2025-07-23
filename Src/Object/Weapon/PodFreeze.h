#pragma once
#include "WeaponBase.h"

class PodFreeze : public WeaponBase
{
public:
	// PodFreeze固有パラメータ定数
	static constexpr float SCALE = 0.8f;                // モデルスケール
	static constexpr float SPEED = 8.0f;                // 移動速度
	static constexpr int HP_DAMAGE = 60;                // HPダメージ
	static constexpr int STUN_DAMAGE = 480;             // スタンダメージ
	static constexpr int SHOT_BLAST_MAX = 600;          // ショット持続最大
	static constexpr float Y_BORDER = 160.0f;           // Y座標境界
	static constexpr float BLAST_SCL = 4.0f;            // 爆発時スケール
	static constexpr float BLAST_ROT_Y = 0.05f;         // 爆発時Y軸回転増加量
	static constexpr int BLAST_MAX_CNT = 120;           // 爆発最大カウント


	//  特にない
	//  パラメータ
	void SetParam(void) override;

	//  処理
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

protected:
	bool IsShot(void) override;

private:
	//  このブキ固有の処理が発生する場合はここ
	int blastCnt_;
	float moveDistance;

};
