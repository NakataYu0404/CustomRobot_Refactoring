#pragma once
#include "../PlayerBase.h"

class PlayerBirb : public PlayerBase
{
public:
    // Birb固有パラメータ定数
    static constexpr float SCALE = 0.3f;                // キャラクターの大きさ
    static constexpr float MOVE_SPEED = 1.0f;           // 移動速度
    static constexpr int STUN_HP_MAX = 100;             // スタン耐久値最大
    static constexpr float DEFENSE_POWER = 5.0f;        // 防御力
    static constexpr int ATTACK_DAMAGE = 500;           // 攻撃力
    static constexpr float AIR_DASH_SPEED = 3.0f;       // エアダッシュ速度
    static constexpr float MAX_MOVE_SPEED_VAL = 10.0f;  // 最大移動速度
    static constexpr int MAX_AIRDASH_CNT_VAL = 3;       // エアダッシュ回数
    static constexpr int MAX_HOVER_CNT_VAL = 120;       // ホバー回数
    static constexpr int INPUT_JUMP_FRAME_VAL = 12;     // ジャンプ受付フレーム
    static constexpr float MAX_JUMP_POW_VAL = 8.0f;     // 最大ジャンプ力

    void SetParam(void) override;

protected:

private:
};

