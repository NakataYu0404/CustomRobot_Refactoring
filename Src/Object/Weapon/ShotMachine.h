#pragma once
#include "WeaponBase.h"

class ShotMachine : public WeaponBase
{
public:
	// ShotMachine固有パラメータ定数
	static constexpr float SCALE = 0.8f;                // モデルスケール
	static constexpr float SPEED = 20.0f;               // 移動速度
	static constexpr int HP_DAMAGE = 65;                // HPダメージ
	static constexpr int SHOT_BLAST_MAX = 600;          // ショット持続最大



	void SetParam(void) override;
protected:
private:
};

