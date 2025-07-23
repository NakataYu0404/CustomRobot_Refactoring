#pragma once
#include "WeaponBase.h"

class ShotSniper :public WeaponBase
{
public:
	// ShotSniper固有パラメータ定数
	static constexpr float SCALE = 0.8f;                // モデルスケール
	static constexpr float SPEED = 28.0f;               // 移動速度
	static constexpr int HP_DAMAGE = 499;               // HPダメージ
	static constexpr int SHOT_BLAST_MAX = 600;          // ショット持続最大
	static constexpr float SPEED_UP = 1.0f;             // 毎フレーム速度増加量


	void SetParam(void) override;

	void UpdateWeapon(void) override;



protected:
private:
};

