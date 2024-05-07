#include "../../Manager/SceneManager.h"
#include "PlayerGhost.h"

void PlayerGhost::SetParam(void)
{
    //  大きさの設定
    scl_ = { 0.3f,0.3f,0.3f };

    //  移動スピード(1未満に設定しても加速する)
    speed_ = 0.3f;          //  birb1

    stunHpMax_ = 80;       //  birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 4;      //  birb5

    attackDamage_ = 200;    //  birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 2.4f;   //  birb3.0

    //  最大速度
    MAX_MOVE_SPEED = 6.0f;    //  birb10

    //  エアダッシュできる回数
    MAX_AIRDASH_CNT = 4;    //  birb3
    MAX_HOVER_CNT = 160;

    //  ジャンプキー入力を受け付けるフレーム数
    INPUT_JUMP_FRAME = 16;  //  birb12

    //	最大ジャンプ力
    MAX_JUMP_POW = 12.0f;    //  birb8

    playerAnim_.IdleAnim = 7;
    playerAnim_.WalkAnim = 2;
    playerAnim_.RunAnim = 1;
    playerAnim_.JumpAnim = 2;
    playerAnim_.StunAnim = 5;

    //  アニメーションをアタッチする
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    //  アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
