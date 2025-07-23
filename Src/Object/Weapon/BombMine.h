#pragma once
#include "WeaponBase.h"

class BombMine : public WeaponBase
{
public:
    // BombMine固有パラメータ定数
    static constexpr float SCALE = 0.8f;                // モデルスケール
    static constexpr float SPEED = 8.0f;                // 移動速度
    static constexpr int HP_DAMAGE = 75;                // HPダメージ
    static constexpr int SHOT_BLAST_MAX = 600;          // ショット持続最大
    static constexpr float BLAST_SCL_UP = 0.05f;        // 爆発時スケール増加量
    static constexpr float BLAST_ROT_Y = 0.05f;         // 爆発時Y軸回転増加量
    static constexpr float BLAST_MAX_SCL = 15.0f;       // 爆発最大スケール
    static constexpr int BLAST_MAX_CNT = 80;            // 爆発最大カウント
    static constexpr int BLAST_WAIT_CNT = 120;          // 爆発待機カウント


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
	float moveDistance;    // 移動距離

	int blastCnt_;         // 爆発カウント

	int waitCnt_;          // 爆発待機カウント
};

