#pragma once
#include "../PlayerBase.h"

class PlayerCactoro : public PlayerBase
{
public:
    // Cactoro固有パラメータ定数
    static constexpr float SCALE = 0.3f;                // キャラクターの大きさ
    static constexpr float MOVE_SPEED = 1.2f;           // 移動速度
    static constexpr int STUN_HP_MAX = 80;              // スタン耐久値最大
    static constexpr float DEFENSE_POWER = 4.0f;        // 防御力
    static constexpr int ATTACK_DAMAGE = 400;           // ???
    static constexpr float AIR_DASH_SPEED = 0.0f;       // エアダッシュ速度
    static constexpr float MAX_MOVE_SPEED_VAL = 14.0f;  // 最大移動速度
    static constexpr int MAX_AIRDASH_CNT_VAL = 0;       // エアダッシュ回数
    static constexpr int MAX_HOVER_CNT_VAL = 0;         // ホバー回数
    static constexpr int INPUT_JUMP_FRAME_VAL = 0;      // ジャンプ受付フレーム
    static constexpr float MAX_JUMP_POW_VAL = 0.0f;     // 最大ジャンプ力

    void SetParam(void) override;

protected:

private:
};
