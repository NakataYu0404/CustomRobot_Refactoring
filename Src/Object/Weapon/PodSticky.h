#pragma once
#include "WeaponBase.h"
class PodSticky : public WeaponBase
{
public:
	// PodSticky固有パラメータ定数
	static constexpr float SCALE = 0.4f;                // モデルスケール
	static constexpr float SPEED = 8.0f;                // 移動速度
	static constexpr int HP_DAMAGE = 50;                // HPダメージ
	static constexpr int SHOT_BLAST_MAX = 0;            // ショット持続最大
	static constexpr float BOUNCE_Y_BORDER = 25.0f;     // バウンドY境界
	static constexpr float RADIUS_SCALE = 100.0f;       // 半径計算用スケール

	//  パラメータ
	void SetParam(void) override;

	//  処理
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

	float GetRadius(void) override;

protected:
private:
	//  このブキ固有の処理が発生する場合はここ
	bool stickFlag_;        // スティックフラグ
};

