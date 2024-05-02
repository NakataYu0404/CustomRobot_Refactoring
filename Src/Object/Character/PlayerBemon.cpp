#include "../../Manager/SceneManager.h"
#include "PlayerBemon.h"

void PlayerBemon::SetParam(void)
{
    // 大きさの設定
    scl_ = { 0.5f,0.5f,0.5f };

    // 移動スピード(1未満に設定しても加速する)
    speed_ = 0.6f;          // birb1

    stunHpMax_ = 160;       // birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 6.0f;      // birb5

    attackDamage_ = 1000;    // birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 3.0f;   // birb3.0

    // 最大速度
    MAX_MOVE_SPEED = 8.0f;    // birb10

    // エアダッシュできる回数
    MAX_AIRDASH_CNT = 2;    // birb3
    MAX_HOVER_CNT = 80;

    // ジャンプキー入力を受け付けるフレーム数
    INPUT_JUMP_FRAME = 10;  // birb12

    //	最大ジャンプ力
    MAX_JUMP_POW = 8.0f;    // birb8

    playerAnim_.IdleAnim = 3;
    playerAnim_.WalkAnim = 11;
    playerAnim_.RunAnim = 9;
    playerAnim_.JumpAnim = 5;
    playerAnim_.StunAnim = 7;

    // アニメーションをアタッチする
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    // アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
