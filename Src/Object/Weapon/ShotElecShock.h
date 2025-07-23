#pragma once
#include "WeaponBase.h"

class ShotElecShock : public WeaponBase
{
public:
    // ShotElecShock固有パラメータ定数
    static constexpr float SCALE = 4.0f;                // モデルスケール
    static constexpr float SPEED = 10.0f;               // 移動速度
    static constexpr int HP_DAMAGE = 70;                // HPダメージ
    static constexpr int STUN_DAMAGE = 250;             // スタンダメージ
    static constexpr int SHOT_BLAST_MAX = 30;           // ショット持続最大


    void SetParam(void) override;
protected:
private:
};

