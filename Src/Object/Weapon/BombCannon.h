#pragma once
#include "WeaponBase.h"

class BombCannon : public WeaponBase
{
public:
	// BombCannon固有パラメータ定数
	static constexpr float SCALE = 0.8f;                // モデルスケール
	static constexpr float SPEED = 8.0f;                // 移動速度
	static constexpr int HP_DAMAGE = 30;                // HPダメージ
	static constexpr int SHOT_BLAST_MAX = 600;          // ショット持続最大
	static constexpr float CROSSHAIR_SCALE = 0.8f;      // クロスヘアスケール
	static constexpr float CROSSHAIR_MOVE_SCALE = 12.0f;// クロスヘア移動倍率
	static constexpr float BLAST_SCL_UP = 0.1f;         // 爆発時スケール増加量
	static constexpr float BLAST_ROT_Y = 0.05f;         // 爆発時Y軸回転増加量
	static constexpr float BLAST_MAX_SCL = 10.0f;       // 爆発最大スケール
	static constexpr int BLAST_MAX_CNT = 60;            // 爆発最大カウント


	//  特にない
	//  パラメータ
	void SetParam(void) override;

	void UpdateWeapon(void) override;

	void UpdateBlast(void) override;
	void DrawShot(void) override;
	void DrawBlast(void) override;

	void Release(void) override;

protected:
	bool IsShot(void) override;

private:
	//  このブキ固有の処理が発生する場合はここ
	bool dirFlag;           // 進行方向反転フラグ
	float moveDistance;     // 移動距離

	int blastCnt_;          // 爆発カウント

	bool crosshairFlag_;    // クロスヘア表示フラグ

	int crossHairId_;       // クロスヘアモデルID
	VECTOR crosshairPos_;   // クロスヘア位置
	VECTOR crosshairScl_;   // クロスヘアスケール
	VECTOR crosshairRot_;   // クロスヘア回転

};

