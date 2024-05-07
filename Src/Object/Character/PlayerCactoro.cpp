#include "../../Manager/SceneManager.h"
#include "PlayerCactoro.h"

void PlayerCactoro::SetParam(void)
{
    //  大きさの設定
    scl_ = { 0.3f,0.3f,0.3f };

    //  移動スピード(1未満に設定しても加速する)
    speed_ = 1.2f;          //  birb1

    stunHpMax_ = 80;       //  birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 4;      //  birb5

    attackDamage_ = 400;    //  birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 0.0f;   //  birb3.0

    //  最大速度
    MAX_MOVE_SPEED = 14.0f;    //  birb10

    //  エアダッシュできる回数
    MAX_AIRDASH_CNT = 0;    //  birb3
    MAX_HOVER_CNT = 0;

    //  ジャンプキー入力を受け付けるフレーム数
    INPUT_JUMP_FRAME = 0;  //  birb12

    //	最大ジャンプ力
    MAX_JUMP_POW = 0.0f;    //  birb8

    playerAnim_.IdleAnim = 3;
    playerAnim_.WalkAnim = 10;
    playerAnim_.RunAnim = 9;
    playerAnim_.JumpAnim = 5;
    playerAnim_.StunAnim = 7;

    //  アニメーションをアタッチする
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    //  アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
