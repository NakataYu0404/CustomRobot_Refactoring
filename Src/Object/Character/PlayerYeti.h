#pragma once
#include "../PlayerBase.h"

class PlayerYeti : public PlayerBase
{
public:
    // Yeti固有パラメータ定数
    static constexpr float SCALE = 0.3f;                // キャラクターの大きさ
    static constexpr float MOVE_SPEED = 0.7f;           // 移動速度
    static constexpr int STUN_HP_MAX = 120;             // スタン耐久値最大
    static constexpr float DEFENSE_POWER = 5.0f;        // 防御力
    static constexpr int ATTACK_DAMAGE = 600;           // 攻撃力
    static constexpr float AIR_DASH_SPEED = 2.4f;       // エアダッシュ速度
    static constexpr float MAX_MOVE_SPEED_VAL = 12.0f;  // 最大移動速度
    static constexpr int MAX_AIRDASH_CNT_VAL = 3;       // エアダッシュ回数
    static constexpr int MAX_HOVER_CNT_VAL = 120;       // ホバー回数
    static constexpr int INPUT_JUMP_FRAME_VAL = 16;     // ジャンプ受付フレーム
    static constexpr float MAX_JUMP_POW_VAL = 7.0f;     // 最大ジャンプ力

    void SetParam(void) override;

protected:

private:
};

