#include "../../Manager/SceneManager.h"
#include "PlayerCactoro.h"

void PlayerCactoro::SetParam(void)
{
    // キャラクターの大きさ設定
    scl_ = { SCALE, SCALE, SCALE };

    // 移動速度設定
    speed_ = MOVE_SPEED;

    // スタン耐久値最大・初期化
    stunHpMax_ = STUN_HP_MAX;
    stunHp_ = stunHpMax_;

    // 防御力設定
    defensePower_ = DEFENSE_POWER;

    // 攻撃力設定
    attackDamage_ = ATTACK_DAMAGE;

    // 重力加速度設定
    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    // エアダッシュ速度設定
    airDashSpeed_ = AIR_DASH_SPEED;

    // 最大移動速度設定
    MAX_MOVE_SPEED = MAX_MOVE_SPEED_VAL;

    // エアダッシュ・ホバー回数設定
    MAX_AIRDASH_CNT = MAX_AIRDASH_CNT_VAL;
    MAX_HOVER_CNT = MAX_HOVER_CNT_VAL;

    // ジャンプ受付フレーム数設定
    INPUT_JUMP_FRAME = INPUT_JUMP_FRAME_VAL;

    // 最大ジャンプ力設定
    MAX_JUMP_POW = MAX_JUMP_POW_VAL;

    // アニメーション番号設定
    playerAnim_.IdleAnim = 3;   // 待機
    playerAnim_.WalkAnim = 10;  // 歩き
    playerAnim_.RunAnim = 9;    // 走り
    playerAnim_.JumpAnim = 5;   // ジャンプ
    playerAnim_.StunAnim = 7;   // スタン

    // アニメーションをアタッチ
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    // アタッチしているアニメーションの総再生時間取得
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);
}
