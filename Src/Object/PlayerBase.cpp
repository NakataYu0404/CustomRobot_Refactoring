#include <math.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"

//  ブキ
#include "Weapon/WeaponBase.h"
#include "Weapon/ShotMachine.h"
#include "Weapon/ShotElecShock.h"
#include "Weapon/ShotSniper.h"
#include "Weapon/BombCannon.h"
#include "Weapon/BombMine.h"
#include "Weapon/PodBounce.h"
#include "Weapon/PodFreeze.h"
#include "Weapon/PodSticky.h"
#include "../Manager/Camera.h"
#include "PlayerBase.h"

//   //タブ
//  //スペース
PlayerBase::PlayerBase(void)
{
}

PlayerBase::~PlayerBase(void)
{
}

void PlayerBase::Init(TYPE type, KEY_CONFIG keyConfig)
{

    playerNumber_ = type;
    keyConfig_ = keyConfig;

        
    shotFlameCnt_ = 0;
    podFlameCnt_ = 0;


    //  爆発エフェクト読み込み  
    LoadDivGraph((Application::PATH_IMAGE + "Blast.png").c_str(), BLAST_ANIM_NUM, 4, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImgs_, true);
    for (int i = 0; i < 4; i++)
    {
        stunImgs_[i] = LoadGraph((Application::PATH_IMAGE + "Stun/" + std::to_string(i + 1) + ".png").c_str());
    }


    SetCommon();
    SetParam();

    Update();
}

void PlayerBase::ChangeBody(int modelId)
{
    if (modelIdOld_ == modelId)
    {
        return;
    }

    modelIdOld_ = modelId;

    MV1DeleteModel(modelId_);
    baseModelId_ = modelId;
    modelId_ = MV1DuplicateModel(baseModelId_);

    MV1SetScale(modelId_, scl_);
    MV1SetRotationXYZ(modelId_, rot_);
    MV1SetPosition(modelId_, pos_);

    //  アニメーションをアタッチする
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);
    //  アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);


}

void PlayerBase::ChangeShot(SHOT_TYPE shotType)
{
    shotType_ = shotType;
    //  弾の種類に応じた弾数の設定(一回の射撃動作で何発出るか)
    PlayerBase::BULLETS bullets;
    PlayerBase::WeaponDelay weaponDelay;
    switch (shotType)
    {
    case PlayerBase::SHOT_TYPE::MACHINE:
        modelShotId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        shotBullet_ = bullets.S_MACHINE;
        delayShot_ = weaponDelay.S_MACHINE;
        break;
    case PlayerBase::SHOT_TYPE::ELECSHOCK:
        modelShotId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Fist.mv1").c_str());
        shotBullet_ = bullets.S_ELECSHOCK;
        delayShot_ = weaponDelay.S_ELECSHOCK;
        break;
    case PlayerBase::SHOT_TYPE::SNIPER:
        modelShotId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        shotBullet_ = bullets.S_SNIPER;
        delayShot_ = weaponDelay.S_SNIPER;
        break;
    case PlayerBase::SHOT_TYPE::MAX:
        modelShotId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        shotBullet_ = bullets.S_MACHINE;
        delayShot_ = weaponDelay.S_MACHINE;
        break;
    default:
        break;
    }
}

void PlayerBase::ChangeBomb(BOMB_TYPE bombType)
{
    bombType_ = bombType;
    //  弾の種類に応じた弾数の設定(一回の射撃動作で何発出るか)
    PlayerBase::BULLETS bullets;
    PlayerBase::WeaponDelay weaponDelay;
    switch (bombType)
    {
    case PlayerBase::BOMB_TYPE::CANNON:
        modelBombId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        bombBullet_ = bullets.B_CANNON;
        delayBomb_ = weaponDelay.B_CANNON;

        break;
    case PlayerBase::BOMB_TYPE::MINE:
        modelBombId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        bombBullet_ = bullets.B_MINE;
        delayBomb_ = weaponDelay.B_MINE;

        break;
    case PlayerBase::BOMB_TYPE::MAX:
        modelBombId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        bombBullet_ = bullets.B_CANNON;
        delayBomb_ = weaponDelay.B_CANNON;
        break;
    default:
        break;
    }

}

void PlayerBase::ChangePod(POD_TYPE podType)
{
    podType_ = podType;
    //  弾の種類に応じた弾数の設定(一回の射撃動作で何発出るか)
    PlayerBase::BULLETS bullets;
    PlayerBase::WeaponDelay weaponDelay;
    switch (podType)
    {
    case PlayerBase::POD_TYPE::BOUNCE:
        modelPodId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/SpikeShot.mv1").c_str());
        podBullet_ = bullets.P_BOUNCE;
        delayPod_ = weaponDelay.P_BOUNCE;
        break;
    case PlayerBase::POD_TYPE::FREEZE:
        modelPodId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Bird.mv1").c_str());
        podBullet_ = bullets.P_FREEZE;
        delayPod_ = weaponDelay.P_FREEZE;
        break;
    case PlayerBase::POD_TYPE::STICKY:
        modelPodId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/SpikeShot.mv1").c_str());
        podBullet_ = bullets.P_STICKY;
        delayPod_ = weaponDelay.P_STICKY;
        break;
    case PlayerBase::POD_TYPE::MAX:
        modelPodId_ = MV1LoadModel((Application::PATH_MODEL + "Shot/Shot.mv1").c_str());
        podBullet_ = bullets.P_BOUNCE;
        delayPod_ = weaponDelay.P_BOUNCE;
        break;
    default:
        break;
    }

}

void PlayerBase::ChangeReg(REG_TYPE regType)
{
    regType_ = regType;
}

void PlayerBase::SetCommon(void)
{
    //  使用メモリ容量と読み込み時間削減のため
    //  モデルデータをいくつもメモリ上に表示させない

    LoadDivGraph((Application::PATH_IMAGE + "smoke.png").c_str(), 12, 12, 1, 2112 / 12, 61, smokeImage_, 0, 0);
    isSpriteEnd_ = false;



    //  角度の設定
    rot_ = { 0.0f,0.0f * DX_PI_F / 180.0f,0.0f };

    //  位置の設定
    switch (playerNumber_)
    {
    case PlayerBase::TYPE::NONE:
        break;
    case PlayerBase::TYPE::PLAYER_1:
        pos_ = { -500.0f,0.0f,75.0f };
        break;
    case PlayerBase::TYPE::PLAYER_2:
        pos_ = { 500.0f,0.0f,75.0f };
        break;
    case PlayerBase::TYPE::MAX:
        break;
    default:
        break;
    }

    //  右方向に移動する
    dir_ = { 0.0f,0.0f,0.0f };

    airDashDir_ = { 0.0f,0.0f,0.0f };

    weaponDir_ = { 0.0f,0.0f,0.0f };
    bombDirX_ = 0.0f;

    //  初期は生存状態
    isAlive_ = true;


    //  再生中のアニメーション時間
    stepAnim_ = 0.0f;

    //  アニメーション速度
    speedAnim_ = 30.0f;

    //  衝突判定用の球体中心の調整座標
    collisionLocalPos_ = { 0.0f, 50.0f, 0.0f };

    hp_ = hpMax_;

    attackFlag = false;
    alreadyAttackHit_ = false;

    //  ジャンプ力
    jumpPow_ = 0.0;
    //  ジャンプ判定
    isJump_ = false;
    //  ジャンプキー押下判定
    isPutJumpKey_ = false;

    jumpPos_ = pos_;

    //ジャンプキー入力カウンタ
    //スタート直後は、一回着地しないとジャンプできない
    cntJumpInput_ = INPUT_JUMP_FRAME;

    isAirDash_ = false;
    alreadyAirDash_ = false;

    airDashCnt_ = 0;
    airDashVec_ = { 0.0f,0.0f,0.0f };

    isHover_ = false;
    alreadyHover_ = false;
    hoverCnt_ = 0;

    shotLocalPos_ = { 0.0f,25.0f,0.0f };

    shotFireCnt_ = shotBullet_;
    bombFireCnt_ = bombBullet_;
    podFireCnt_ = podBullet_;
    delayShotCnt_ = 0;
    delayBombCnt_ = 0;
    delayPodCnt_ = 0;
    delayAttackCnt_ = 0;
    delayAttack_ = 180;

    isShot_ = false;
    
    PythagorasDisXZ_ = 0.0f;

    invincibleCnt_ = InvincibleCntMax;
    invincible_ = false;

    recovery_ = true;
    recoveryCnt_ = 0;

    soundDamageH_ = LoadSoundMem((Application::PATH_SE + "Damage.mp3").c_str());
    soundShotH_ = LoadSoundMem((Application::PATH_SE + "Shot.mp3").c_str());
    soundBombH_ = LoadSoundMem((Application::PATH_SE + "Bomb.mp3").c_str());
    soundPodH_ = LoadSoundMem((Application::PATH_SE + "Pod.mp3").c_str());
    soundTackleH_ = LoadSoundMem((Application::PATH_SE + "Tackle.mp3").c_str());


}

void PlayerBase::SetParam(void)
{
    //  大きさの設定
    scl_ = { 0.3f,0.3f,0.3f };

    //  移動スピードz
    speed_ = 1.0f;

    stunHpMax_ = 100;
    stunHp_ = stunHpMax_;
    defensePower_ = 5;

    attackDamage_ = 500;

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 3.0f;

    //  エアダッシュできる回数
    MAX_AIRDASH_CNT = 3;
    //  ホバーできる時間
    MAX_HOVER_CNT = 120;

    //  ジャンプキー入力を受け付けるフレーム数
    INPUT_JUMP_FRAME = 12;

    //	最大ジャンプ力
    MAX_JUMP_POW = 8.0f;

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

void PlayerBase::Update(void)
{

    //  生存していなければ処理しない
    if (isAlive_ == false)
    {
        return;
    }

    //   重力を常にかける
    AddGravity();

    //   同じif文を3つも使っていて気持ち悪いけど、Process◯◯と◯◯、jumpとAirDashの処理順を入れ替えるわけにはいかないので仕方がない

    if (status_ != STATUS::STUN && status_ != STATUS::RECOVERY)
    {
        ProcessMove();
    }

    Move();

    if (status_ != STATUS::STUN && status_ != STATUS::RECOVERY)
    {
        Turn();

        //  ジャンプ操作
        ProcessJump();
    }

    //  ジャンプ動作
    Jump();

    if (status_ != STATUS::STUN && status_ != STATUS::RECOVERY)
    {
        switch (regType_)
        {
            //  cntJumpInput_が最大値だったら、ホバー、スラスターをさせたい
        case PlayerBase::REG_TYPE::AIRDASH:
            AirDash();
            break;
        case PlayerBase::REG_TYPE::HOVER:
            Hover();
            break;
        }

        Attack();

        //  発射
        Fire(shotType_, bombType_, podType_);
    }
    else
    {
        Stun();
    }

    if (status_ == STATUS::RECOVERY)
    {
        Recovery();
    }
    else if (recoveryCnt_ > 180)
    {
        recovery_ = false;
    }
    recoveryCnt_++;

    //  弾処理
    ShotUpdate();

    int hp = hp_;
    hpHundredPlace_ = hp / 100;
    hp = hp % 100;
    hpTensPlace_ = hp_ / 10;
    hp = hp % 10;
    hpOnesPlace_ = hp;

    ChangeAnim();
    Animation();


    invincibleCnt_++;
}

void PlayerBase::Draw(void)
{
    //  状況にあわせた色
    if (invincible_)
    {
        MV1SetDifColorScale(modelId_, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
        MV1SetSpcColorScale(modelId_, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
        MV1SetEmiColorScale(modelId_, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
        MV1SetAmbColorScale(modelId_, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    }
    else if (status_ == STATUS::STUN)
    {
        MV1SetDifColorScale(modelId_, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
        MV1SetSpcColorScale(modelId_, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
        MV1SetEmiColorScale(modelId_, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
        MV1SetAmbColorScale(modelId_, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));

        VECTOR head = pos_;
        head.y += 50.0f;
    }
    else if (status_ == STATUS::RECOVERY)
    {
        MV1SetDifColorScale(modelId_, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
        MV1SetSpcColorScale(modelId_, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
        MV1SetEmiColorScale(modelId_, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));
        MV1SetAmbColorScale(modelId_, GetColorF(0.0f, 1.0f, 0.0f, 1.0f));

    }
    else
    {
        MV1SetDifColorScale(modelId_, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        MV1SetSpcColorScale(modelId_, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        MV1SetEmiColorScale(modelId_, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        MV1SetAmbColorScale(modelId_, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    }
    if (recoveryCnt_ <= 180)
    {
        //  リカバリーから無敵中の点滅
        if (recoveryCnt_ % 20 <= 9)
        {
            MV1DrawModel(modelId_);
        }
    }
    else
    {
        MV1DrawModel(modelId_);
    }
    if (status_ == STATUS::STUN)
    {
        VECTOR head = pos_;
        head.y += 40;
        DrawBillboard3D(head, 0.5f, 0.0f, 100.0f, 0.0f, stunImgs_[stunCnt_ /3 % 4], true);
    }


    //DrawFormatString(0, 100, 0x000000, "pow=%d", cntJumpInput_);
    //DrawFormatString(0, 120, 0x000000, "DIR=%.0f,%.0f,%.0f", dir_.x, dir_.y, dir_.z);
    //DrawFormatString(0, 250, 0xffffff, "ROT=%.0f,%.0f,%.0f", rot_.x, rot_.y, rot_.z);

    //DrawFormatString(0, 200 + 100 * static_cast<int>(playerNumber_), 0x000000, "hp_:%d", hp_);

    //  当たり判定の諸々描画
    VECTOR capsuleSPos = VAdd(pos_, { 0.0f,70.0f,0.0f });
    VECTOR capsuleEPos = VAdd(pos_, { 0.0f,25.0f,0.0f });
    int capsuleRadius = 25;
    //DrawCapsule3D(capsuleSPos, capsuleEPos, capsuleRadius, 10, 0xff8866, 0xff8866, false);

    VECTOR spherePos = VAdd(pos_, { 0.0f,22.8f,0.0f });
    int sphereRadius = 23;
    //DrawSphere3D(spherePos, sphereRadius, 10, 0xffffff, 0xffffff, false);

    size_t size = shots_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (shots_[i]->IsAlive())
        {
            shots_[i]->Draw();
        }
    } 

    size = bombs_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (bombs_[i]->IsAlive())
        {
            bombs_[i]->Draw();
        }
    } 

    size = pods_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (pods_[i]->IsAlive())
        {
            pods_[i]->Draw();
        }
    }

    if (isPutJumpKey_ && !isSpriteEnd_)
    {
        DrawBillboard3D(jumpPos_, 0.5f, 0.0f, 250.0f, 0.0f, smokeImage_[smokesprite], true);
        smokesprite++;
        if (smokesprite >= 12)
        {
            isSpriteEnd_ = true;
        }
    }
    else
    {
        smokesprite = 0;
    }

}

void PlayerBase::Release(void)
{
    MV1DeleteModel(modelId_);
    MV1DeleteModel(modelShotId_);
    MV1DeleteModel(modelBombId_);
    MV1DeleteModel(modelPodId_);

    for (auto shot : shots_)
    {
        shot->Release();
    }
    for (auto bomb : bombs_)
    {
        bomb->Release();
    }
    for (auto pod : pods_)
    {
        pod->Release();
    }

    //  爆発画像の解放
    for (int i = 0; i < BLAST_ANIM_NUM; i++)
    {
        DeleteGraph(blastImgs_[i]);
    }

    DeleteSoundMem(soundDamageH_);
    DeleteSoundMem(soundShotH_);
    DeleteSoundMem(soundBombH_);
    DeleteSoundMem(soundPodH_);
    DeleteSoundMem(soundTackleH_);
}

void PlayerBase::Animation(void)
{
    //  アニメーション再生

    //  経過時間の取得
    float deltaTime = 1.0f / SceneManager::DEFAULT_FPS;

    //  アニメーション時間の進行
    stepAnim_ += (speedAnim_ * deltaTime);
    if (stepAnim_ > animTotalTime_)
    {
        //  ループ再生
        stepAnim_ = 0.0f;
    }

    //  再生するアニメーション時間の設定
    MV1SetAttachAnimTime(modelId_, animAttachNo_, stepAnim_);

}

void PlayerBase::ChangeAnim(void)
{
    //  アニメーションをアタッチする
    MV1DetachAnim(modelId_, animAttachNo_);

    switch (status_)
    {
    case PlayerBase::STATUS::IDLE:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);
        break;
    case PlayerBase::STATUS::WALK:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.WalkAnim);
        break;
    case PlayerBase::STATUS::RUN:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.RunAnim);
        break;
    case PlayerBase::STATUS::JUMP:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.JumpAnim);
        break;
    case PlayerBase::STATUS::STUN:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.StunAnim);
        break;
    case PlayerBase::STATUS::TACKLE:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.RunAnim);
        break;
    case PlayerBase::STATUS::RECOVERY:
        animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);
        break;
    default:
        break;
    }
    //  アタッチしているアニメーションの総再生時間を取得する
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);


}

VECTOR PlayerBase::GetPos(void)
{
    return pos_;
}

VECTOR PlayerBase::GetColPos(void)
{
    return VAdd(pos_, collisionLocalPos_);
}

VECTOR PlayerBase::GetScl(void)
{
    return scl_;
}

void PlayerBase::SetPos(VECTOR pos)
{
    pos_ = pos;
    MV1SetPosition(modelId_, pos_);

}

bool PlayerBase::IsAlive(void)
{
    return isAlive_;
}

void PlayerBase::SetAlive(bool alive)
{
    isAlive_ = alive;
}

void PlayerBase::Damage(int hpDamage, int stunDamage, VECTOR weaponDir, ATTACK_TYPE type)
{
    if (status_ == STATUS::STUN)
    {
        //  スタン中のダメージ加算(スタン中のダメージがある程度溜まったら起き上がる)
        stunDmg_ += hpDamage / defensePower_;

    }

    hp_ -= hpDamage / defensePower_;
    stunHp_ -= stunDamage / defensePower_;
    if (hp_ <= 0)
    {
        hp_ = 0;
    }
    if (stunHp_ <= 0)
    {
        stunHp_ = 0;
    }
    //  強制ふっとびなので、jumpPowをむりやり与える
    //  weapondirが下方向であっても上方方向に動くようにする(weapondirのyは使わず、jumppowだけで調整するのがいいか)
    //  強制横移動はdir,speedを設定する
    //  ダメージをある程度もらったら、しばらく無敵になって起き上がる
    //  攻撃の種類によってふっとびを変える
    //  地面についていると自分から以外浮かない仕様になっていたので、すこし高さを上げる
    weaponDir.y = 0.0f;

    switch (type)
    {
    case PlayerBase::ATTACK_TYPE::SHOT:
        if (status_ == STATUS::STUN)
        {
            dir_ = weaponDir;
            VECTOR wdir = AsoUtility::NormalizeV(dir_);
            pos_.x += wdir.x * 8.0f;
            pos_.z += wdir.z * 8.0f;
            jumpPow_ = 2.0f;
            pos_.y+=0.02f;

        }
        else
        {
            dir_ = weaponDir;
            VECTOR wdir = AsoUtility::NormalizeV(dir_);
            pos_.x += wdir.x * 5.0f;
            pos_.z += wdir.z * 5.0f;
            jumpPow_ = 2.0f;
            pos_.y += 0.02f;

        }
        break;
    case PlayerBase::ATTACK_TYPE::BOMB:
        if (status_ == STATUS::STUN)
        {
            speed_ = 0.0f;
            jumpPow_ = 10.0f;
            pos_.y += 0.2f;
        }
        else
        {
            speed_ = 0.0f;
            jumpPow_ = 10.0f;
            pos_.y += 0.2f;
            //  ボムに当たると、強制スタン
            stunHp_ = 0;
        }
        break;
    case PlayerBase::ATTACK_TYPE::POD:
        if (status_ == STATUS::STUN)
        {
            dir_ = weaponDir;

            VECTOR wdir = AsoUtility::NormalizeV(dir_);
            pos_.x += wdir.x * 8.0f;
            pos_.z += wdir.z * 8.0f;

            jumpPow_ = 2.0f;
            pos_.y += 0.2f;


        }
        else
        {
            dir_ = weaponDir;

            VECTOR wdir = AsoUtility::NormalizeV(dir_);
            pos_.x += wdir.x * 5.0f;
            pos_.z += wdir.z * 5.0f;

            jumpPow_ = 2.0f;
            pos_.y += 0.2f;

        }
        break;
    }




    if (stunHp_ <= 0)
    {
        ChangeStatus(STATUS::STUN);
    }

    SoundPlayer(SE_TYPE::DAMAGE);
}

float PlayerBase::GetRadius(void)
{
    return COL_RADIUS;
}

int PlayerBase::GetHp(void)
{
    return hp_;
}

int PlayerBase::GetStunHp(void)
{
    return stunHp_;
}

void PlayerBase::SetEnemyPos(VECTOR pos)
{
    enemyPos_ = pos;
}

void PlayerBase::Fire(SHOT_TYPE shotType, BOMB_TYPE bombType, POD_TYPE podType)
{
    Shot(shotType);
    Bomb(bombType);
    Pod(podType);

    return;
}

void PlayerBase::ProcessMove(void)
{
    auto& ins = InputManager::GetInstance();

    //  プレイヤーの入力を検知する
    auto playerCtl = ins.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(playerNumber_));

    if (!isAirDash_)
    {
        dir_.x = playerCtl.AKeyLX;
        dir_.z = playerCtl.AKeyLY * -1;
    }

    //  dirは方向ベクトルのことだが、コントローラーの入力を10段階(N状態を除く)にしたので0～10になっている。最大値は1.0fの方が仕様上良いので除算する。
    dir_.x /= 10.0f;
    dir_.z /= 10.0f;


    //  動いてたら加速する
    if (dir_.x != 0 || dir_.z != 0)
    {
        if (!isJump_)
        {
            ChangeStatus(STATUS::WALK);
        }
        //  加速
        Accele(MOVE_ACC);
    }
    else
    {
        ChangeStatus(STATUS::IDLE);
    }


}

void PlayerBase::Accele(float speed)
{
    speed_ += speed;

    //  速度制限
    if (speed_ >= MAX_MOVE_SPEED)
    {
        if (!isJump_)
        {
            ChangeStatus(STATUS::RUN);
        }
        speed_ = MAX_MOVE_SPEED;
    }

}

void PlayerBase::Decelerate(void)
{
    //  スティック入力をしてない、特定のショット以外でのショット、エアダッシュをした
    if ((dir_.x == 0 && dir_.z == 0)|| (isShot_ && shotType_ != SHOT_TYPE::ELECSHOCK) || alreadyAirDash_ || status_ == STATUS::STUN)
    {
        //  スピードを最低値に落とす
        speed_ = MIN_MOVE_SPEED;
    }
}

void PlayerBase::Shot(SHOT_TYPE shotType)
{
    //  ここで弾の作成
    auto& ins = InputManager::GetInstance();

    //  弾処理
    if ((ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.SHOT) && delayShotCnt_ > delayShot_) || shotFireCnt_ < shotBullet_)
    {

        isShot_ = true;
        shotFlameCnt_++;

        //  ボタンを押したから発射されたなら、カウントを0に
        if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.SHOT))
        {
            shotFlameCnt_ = 0;
            if (!(shotFireCnt_ < shotBullet_))
            {
                shotFireCnt_ = 0;
            }
        }
        //  6フレームに1回発射
        if (shotFireCnt_ < shotBullet_ && shotFlameCnt_ % 6 != 0)
        {
            return;
        }

        //  発射処理の前に発射カウンタを上げておく
        shotFireCnt_++;

        //  空き配列が存在する場合はそこに弾情報を入れて、発射
        bool flag = false;
        size_t size = shots_.size();
        for (int i = 0; i < size; i++)
        {
            //  i番目の弾が生きていなかったら
            if (!shots_[i]->IsAlive())
            {
                //  i番目の配列に弾を作る
                shots_[i]->Init();
                shots_[i]->CreateWeapon(weaponPos_, weaponDir_,(int)playerNumber_);
                shots_[i]->SetRot(rot_);
                flag = true;
                SoundPlayer(SE_TYPE::SHOT);
                if (shotBullet_ == 1)
                {
                    delayShotCnt_ = 0;
                }
                break;
            }
        }
        //  既に撃ったので、下の発射処理を抜ける
        if (flag)
        {
            if (shotFireCnt_ >= shotBullet_)
            {
                delayShotCnt_++;
            }
            else
            {
                delayShotCnt_ = 0;
            }
            return;
        }
        //  空き配列が無かった場合の発射処理
        std::shared_ptr<WeaponBase> shot = nullptr;
        switch (shotType)
        {
        case PlayerBase::SHOT_TYPE::MACHINE:
            shot = std::make_shared<ShotMachine>();
            break;
        case PlayerBase::SHOT_TYPE::ELECSHOCK:
            shot = std::make_shared<ShotElecShock>();
            break;
        case PlayerBase::SHOT_TYPE::SNIPER:
            shot = std::make_shared<ShotSniper>();
            break;
        case PlayerBase::SHOT_TYPE::MAX:
            break;
        default:
            shot = std::make_shared<ShotMachine>();
            break;
        }
        shot->SetInitial(modelShotId_, blastImgs_, BLAST_ANIM_NUM);
        shot->Init();
        shot->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);

        shot->SetRot(rot_);
        shots_.push_back(shot);
        SoundPlayer(SE_TYPE::SHOT);
        if (shotBullet_ == 1)
        {
            delayShotCnt_ = 0;
        }
    }
    if (shotFireCnt_ >= shotBullet_)
    {
        delayShotCnt_++;
        isShot_ = false;

    }
    else
    {
        delayShotCnt_ = 0;
    }
    return;
}

void PlayerBase::Bomb(BOMB_TYPE bombType)
{
    //  ここで弾の作成
    auto& ins = InputManager::GetInstance();


    //  弾処理
    if ((ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.BOMB) && delayBombCnt_ > delayBomb_) || bombFireCnt_ < bombBullet_)
    {
        //  ボタンを押したから発射されたなら、カウントを0に
        if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.BOMB))
        {

            delayBombCnt_ = 0;

        }

        //  空き配列が存在する場合はそこに弾情報を入れて、発射
        bool flag = false;
        size_t size = bombs_.size();
        for (int i = 0; i < size; i++)
        {
            //  i番目の弾が生きていなかったら
            if (!bombs_[i]->IsAlive())
            {

                //  i番目の配列に弾を作る
                bombs_[i]->Init();
                bombs_[i]->SetEnemyPos(enemyPos_);
                bombs_[i]->SetDistance(PythagorasDisXZ_);
                if (!(pos_.y > enemyPos_.y + 0.5f) && !(bombType == PlayerBase::BOMB_TYPE::MINE))
                {
                    bombs_[i]->CreateWeapon(weaponPos_, bombDir_, (int)playerNumber_);
                }
                else
                {
                    bombs_[i]->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
                }
                flag = true;

                //  発射カウンタを上げる
                bombFireCnt_++;
                SoundPlayer(SE_TYPE::BOMB);
                break;
            }
        }
        //  既に撃ったので、下の発射処理を抜ける
        if (flag)
        {

            delayBombCnt_++;
            return;
        }

        //  空き配列が無かった場合の発射処理
        std::shared_ptr<WeaponBase> bomb = nullptr;
        switch (bombType)
        {
        case PlayerBase::BOMB_TYPE::CANNON:
            bomb = std::make_shared<BombCannon>();
            break;
        case PlayerBase::BOMB_TYPE::MINE:
            bomb = std::make_shared<BombMine>();
            break;
        case PlayerBase::BOMB_TYPE::MAX:
            break;
        default:
            bomb = std::make_shared<BombCannon>();
            break;
        }
        bomb->Init();
        bomb->SetInitial(modelBombId_, blastImgs_, BLAST_ANIM_NUM);
        bomb->SetEnemyPos(enemyPos_);
        bomb->SetDistance(PythagorasDisXZ_);

        if (bombType == BOMB_TYPE::MINE)
        {
            bomb->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
        }
        else
        {
            if (!(pos_.y > enemyPos_.y + 0.5f))
            {
                bomb->CreateWeapon(weaponPos_, bombDir_, (int)playerNumber_);
            }
            else
            {
                bomb->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
            }
        }

        bombs_.push_back(bomb);

        SoundPlayer(SE_TYPE::BOMB);

        //  発射カウンタを上げる
        bombFireCnt_++;

    }
    if (bombFireCnt_ >= bombBullet_)
    {
        delayBombCnt_++;
    }
    else
    {
        delayBombCnt_ = 0;
    }
    return;
}

void PlayerBase::Pod(POD_TYPE podType)
{
    //  ここで弾の作成
    auto& ins = InputManager::GetInstance();

    if (((ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.POD) && delayPodCnt_ > delayPod_) || podFireCnt_ < podBullet_) && podType != POD_TYPE::STICKY)
    {
        podFlameCnt_++;

        //  ボタンを押したから発射されたなら、カウントを0に
        if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.POD))
        {
            podFlameCnt_ = 0;
            if (!(podFireCnt_ < podBullet_))
            {
                podFireCnt_ = 0;
            }
        }

        //  6フレームに1回発射
        if (podFireCnt_ < podBullet_ && podFlameCnt_ % 6 != 0)
        {
            return;
        }

        //  発射カウンタを上げておく
        podFireCnt_++;

        //  空き配列が存在する場合はそこに弾情報を入れて、発射
        bool flag = false;
        size_t size = pods_.size();
        for (int i = 0; i < size; i++)
        {
            //  i番目の弾が生きていなかったら
            if (!pods_[i]->IsAlive())
            {
                //  i番目の配列に弾を作る
                pods_[i]->Init();
                pods_[i]->SetDistance(PythagorasDisXZ_);
                pods_[i]->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
                pods_[i]->SetRot(rot_);

                flag = true;
                SoundPlayer(SE_TYPE::POD);
                break;
            }
        }
        //  既に撃ったので、下の発射処理を抜ける
        if (flag)
        {
            if (podFireCnt_ >= podBullet_)
            {
                delayPodCnt_++;
            }
            else
            {
                delayPodCnt_ = 0;
            }
            return;
        }

        //  空き配列が無かった場合の発射処理
        std::shared_ptr<WeaponBase> pod = nullptr;
        switch (podType)
        {
        case PlayerBase::POD_TYPE::BOUNCE:
            pod = std::make_shared<PodBounce>();
            break;
        case PlayerBase::POD_TYPE::FREEZE:
            pod = std::make_shared<PodFreeze>();
            break;
        case PlayerBase::POD_TYPE::MAX:
            break;
        default:
            pod = std::make_shared<PodBounce>();
            break;
        }

        pod->SetInitial(modelPodId_, blastImgs_, BLAST_ANIM_NUM);
        pod->Init();
        pod->SetDistance(PythagorasDisXZ_);
        pod->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
        pod->SetRot(rot_);
        pods_.push_back(pod);
        SoundPlayer(SE_TYPE::POD);
    }
    else if ((ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.POD) && delayPodCnt_ > delayPod_) && podType == POD_TYPE::STICKY)
    {
        //   ポッドがスティッキーだった場合

        //  空き配列が存在する場合はそこに弾情報を入れて、発射
        bool flag = false;
        size_t size = pods_.size();
        for (int i = 0; i < size; i++)
        {
            //  i番目の弾が生きていなかったら
            if (!pods_[i]->IsAlive())
            {
                //  i番目の配列に弾を作る
                pods_[i]->Init();
                pods_[i]->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
                pods_[i]->SetRot(rot_);

                flag = true;
                SoundPlayer(SE_TYPE::POD);
                newPod = i;
                break;
            }
        }
        //  既に撃ったので、下の発射処理を抜ける
        if (flag)
        {
            delayPodCnt_ = 0;
            return;
        }
        //  空き配列が無かった場合の発射処理
        if (pods_.size() < 2)
        {
            std::shared_ptr<WeaponBase> pod = nullptr;
            pod = std::make_shared<PodSticky>();
            pod->SetInitial(modelPodId_, blastImgs_, BLAST_ANIM_NUM);
            pod->Init();
            pod->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
            pod->SetRot(rot_);
            pods_.push_back(pod);
            SoundPlayer(SE_TYPE::POD);
            newPod = pods_.size() - 1;
            delayPodCnt_ = 0;

        }
        else
        {
            //  i番目の配列に弾を作る
            if (newPod == 0)
            {
                pods_[newPod+1]->Init();
                pods_[newPod+1]->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
                pods_[newPod+1]->SetRot(rot_);
                flag = true;
                SoundPlayer(SE_TYPE::POD);
                newPod = newPod + 1;
                delayPodCnt_ = 0;
            }
            else
            {
                pods_[newPod - 1]->Init();
                pods_[newPod - 1]->CreateWeapon(weaponPos_, weaponDir_, (int)playerNumber_);
                pods_[newPod - 1]->SetRot(rot_);
                flag = true;
                SoundPlayer(SE_TYPE::POD);
                newPod = newPod - 1;
                delayPodCnt_ = 0;

            }


        }
    }

    if (podFireCnt_ >= podBullet_)
    {
        delayPodCnt_++;
    }
    else
    {
        delayPodCnt_ = 0;
    }

    return;

}

void PlayerBase::Move(void)
{
    Decelerate();

    //  カメラの角度に合わせて移動ベクトルを回転してから加算
    float CameraHAngle = SceneManager::GetInstance().GetCamera().lock()->GetHAngle();

    //  カメラの方向を考えない移動
    VECTOR CharMoveVector = VScale(dir_, speed_);
    //  カメラの方向を加味した移動
    VECTOR CharMoveVectorCamera;

    //  カメラの角度に合わせて移動ベクトルを回転してから加算
    float SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
    float CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);

    CharMoveVectorCamera.x = CharMoveVector.x * CosParam - CharMoveVector.z * SinParam;
    CharMoveVectorCamera.y = 0.0f;
    CharMoveVectorCamera.z = CharMoveVector.x * SinParam + CharMoveVector.z * CosParam;

    //  エアダッシュ後にその慣性で移動してくれないのは、向きをコントローラー入力のみで決めているから　なのでエアダッシュの方向を入力する
    if (!isAirDash_ && alreadyAirDash_)
    {
        pos_ = VAdd(pos_, VScale(airDashVec_, 2.0f));
    }
    else if (!isAirDash_)
    {

        //  移動処理
        pos_ = VAdd(pos_, CharMoveVectorCamera);
    }

    //  ステージモデルとの衝突判定
    VECTOR capsuleSPos = VAdd(pos_, { 0.0f,70.0f,0.0f });
    VECTOR capsuleEPos = VAdd(pos_, { 0.0f,25.0f,0.0f });
    int capsuleRadius = 25;


    auto hit = MV1CollCheck_Capsule(modelStageId_, -1, capsuleSPos, capsuleEPos, capsuleRadius);
    //  MV1Coll…で当たっているポリゴン数が0より大きかったら（当たっていたら）
    if (hit.HitNum > 0)
    {
        int HitNum = hit.HitNum;
        for (int i = 0; i < HitNum; i++)
        {

            auto hitDim = hit.Dim[i];
            VECTOR hitPoliPos0 = hitDim.Position[0];
            VECTOR hitPoliPos1 = hitDim.Position[1];
            VECTOR hitPoliPos2 = hitDim.Position[2];

            //  当たっていたら、当たらなくなるまで法線ベクトル方向に100回戻す
            for (int a = 0; a < 100; a++)
            {
                //  このループ内での当たり判定Pos
                VECTOR tmpCapsuleSPos = VAdd(pos_, { 0.0f,70.0f,0.0f });
                VECTOR tmpCapsuleEPos = VAdd(pos_, { 0.0f,25.0f,0.0f });
                capsuleRadius = 25;
                //  当たっていたら位置を少し戻す
                if (HitCheck_Capsule_Triangle(tmpCapsuleSPos, tmpCapsuleEPos, capsuleRadius, hitPoliPos0, hitPoliPos1, hitPoliPos2))
                {
                    pos_ = VAdd(pos_, VScale(hitDim.Normal, 0.5f));
                }
                //  当たっていなかったら処理を終了する
                else
                {
                    break;
                }
            }
        }
    }

    hit = MV1CollCheck_Capsule(modelStageCoverId_, -1, capsuleSPos, capsuleEPos, capsuleRadius);
    //  MV1Coll…で当たっているポリゴン数が0より大きかったら（当たっていたら）
    if (hit.HitNum > 0)
    {
        int HitNum = hit.HitNum;
        for (int i = 0; i < HitNum; i++)
        {

            auto hitDim = hit.Dim[i];
            VECTOR hitPoliPos0 = hitDim.Position[0];
            VECTOR hitPoliPos1 = hitDim.Position[1];
            VECTOR hitPoliPos2 = hitDim.Position[2];

            //  当たっていたら、当たらなくなるまで法線ベクトル方向に100回戻す
            for (int a = 0; a < 100; a++)
            {
                //  このループ内での当たり判定Pos
                VECTOR tmpCapsuleSPos = VAdd(pos_, { 0.0f,70.0f,0.0f });
                VECTOR tmpCapsuleEPos = VAdd(pos_, { 0.0f,25.0f,0.0f });
                capsuleRadius = 25;
                //  当たっていたら位置を少し戻す
                if (HitCheck_Capsule_Triangle(tmpCapsuleSPos, tmpCapsuleEPos, capsuleRadius, hitPoliPos0, hitPoliPos1, hitPoliPos2))
                {
                    pos_ = VAdd(pos_, VScale(hitDim.Normal, 0.5f));
                }
                //  当たっていなかったら処理を終了する
                else
                {
                    break;
                }
            }
        }
    }

    VECTOR spherePos = VAdd(pos_, { 0.0f,22.8f,0.0f });
    int sphereRadius = 23;

    auto hitLeg = MV1CollCheck_Sphere(modelStageId_, -1, spherePos, sphereRadius);
    if (hitLeg.HitNum > 0)
    {

        airDashSpeed_ = 0.0f;
        cntJumpInput_ = 0;
        isJump_ = false;
        isPutJumpKey_ = false;
        alreadyAirDash_ = false;
        isAirDash_ = false;
        alreadyHover_ = false;
        isHover_ = false;
        airDashCnt_ = 0;
        isSpriteEnd_ = false;

        //  地面に乗っていたら、重力がかからない
        for (int i = 0; i < hitLeg.HitNum; i++)
        {
            if (hitLeg.Dim[i].Normal.x <= 0.1f || hitLeg.Dim[i].Normal.z <= 0.1f)
            {
                SetJumpPow(0.0);
            }
        }
    }
    else
    {
        isJump_ = true;
    }

    //大きさ、角度、座標の3D制御
    MV1SetScale(modelId_, scl_);
    MV1SetRotationXYZ(modelId_, rot_);
    MV1SetPosition(modelId_, pos_);
}

void PlayerBase::Turn(void)
{
    auto& ins = InputManager::GetInstance();

    //  プレイヤーの入力を検知する
    auto playerCtl = ins.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(playerNumber_));

    //  PlayerとEnemyのベクトル
    VECTOR PlVec = { pos_.x,pos_.y,pos_.z };
    VECTOR EnVec = { enemyPos_.x,enemyPos_.y,enemyPos_.z };

    //  PlayerからEnemyへのベクトル
    VECTOR PlEnVec = VAdd(EnVec, VScale(PlVec, -1.0f));

    //  プレイヤー向き変更
    if (playerCtl.AKeyRX == 0 && playerCtl.AKeyRY == 0)
    {
        //  ここに通常時の向きを入力(右スティック入力がない限りプレイヤー2の方を向き続ける)
        
        //アークタンジェントでプレイヤー敵間の角度を出す
        float PlEnAngleY = atan2(-PlEnVec.z, PlEnVec.x);

        //  今向いてる方向のデグリー角
        float degNowAngleY = AsoUtility::Rad2DegF(rot_.y);
        //  向きたい方向(敵への方向)のデグリー角
        float degGoalAngleY = AsoUtility::Rad2DegF(PlEnAngleY - (90.0f * DX_PI_F / 180.0f));

        //  0度～360度以内に角度をおさめる
        degGoalAngleY = static_cast<float>(AsoUtility::DegIn360(degGoalAngleY));

        //  右方向と左方向どっち回りの方が近いか
        int aroundDir = AsoUtility::DirNearAroundDeg(degNowAngleY, degGoalAngleY);

        //  もし、目的の角度まで4度より差があったら
        if (!(degGoalAngleY - degNowAngleY < 8.0f && degGoalAngleY - degNowAngleY > -8.0f))
        {
            //  回転スピードを足す
            rot_.y += (aroundDir * SPEED_ROT_RAD);
        }
        else 
        {
            //  向きたい方向にする(ラジアン角)
            rot_.y = PlEnAngleY - (90.0f * DX_PI_F / 180.0f);
        };

        //  0度～360度以内に角度をおさめる
        rot_.y = static_cast<float>(AsoUtility::RadIn2PI(rot_.y));

    }
    else
    {
        //  ここに右スティック入力時の向きを入力
        //  スティック入力角度(X,Y要素それぞれ0~1000)
        float stickAngle = atan2(playerCtl.AKeyRY, playerCtl.AKeyRX);

        float CameraHAngle = SceneManager::GetInstance().GetCamera().lock()->GetHAngle();

        stickAngle += AsoUtility::Deg2RadF(-CameraHAngle);

        float degNowAngleY = AsoUtility::Rad2DegF(rot_.y);
        float degGoalAngleY = AsoUtility::Rad2DegF(stickAngle - (90.0f * DX_PI_F / 180.0f));

        //  0度～360度以内に角度をおさめる
        degGoalAngleY = static_cast<float>(AsoUtility::DegIn360(degGoalAngleY));

        int aroundDir = AsoUtility::DirNearAroundDeg(degNowAngleY, degGoalAngleY);

        if (!(degGoalAngleY - degNowAngleY < 8.0f && degGoalAngleY - degNowAngleY > -8.0f))
        {
            rot_.y += (aroundDir * SPEED_ROT_RAD);
        }
        else
        {
            rot_.y = stickAngle - (90.0f * DX_PI_F / 180.0f);
        };

        //  0度～360度以内に角度をおさめる
        rot_.y = static_cast<float>(AsoUtility::RadIn2PI(rot_.y));
    }

    //  弾のX軸回転を行うための角度を作る
    
    //  プレイヤー、敵間の距離を求める
    float distanceX = enemyPos_.x - pos_.x;
    float distanceZ = enemyPos_.z - pos_.z;
    float distanceY = enemyPos_.y - pos_.y;

    //  ピタゴラスの定理でXZ平面での直線距離を求める
    PythagorasDisXZ_ = fabsf(sqrt((distanceX * distanceX) + (distanceZ * distanceZ)));
    //  プレイヤー、敵の高さも考慮した直線距離を求める
    weaponDir_.x = atan2(-distanceY, PythagorasDisXZ_);
    bombDir_.x = atan2(-BOMB_HIGHEST, PythagorasDisXZ_);

    //  ↓弾の方向を決める
    //  単位行列(無回転の状態)
    MATRIX matRot = MGetIdent();

    //  それぞれの軸の行列を作り、更に行列を合成していく
    //  MMult  :行列の乗算を行う
    //  MgetRot:引数の回転地だけ軸回転する回転行列を戻り値にする（この場合はbarrelRot度回転する回転行列）
    matRot = MMult(matRot, MGetRotX(weaponDir_.x));
    matRot = MMult(matRot, MGetRotY(rot_.y+ AsoUtility::Deg2RadF(180.0f)));
    matRot = MMult(matRot, MGetRotZ(rot_.z));

    MATRIX matRotBomb = MGetIdent();
    //  それぞれの軸の行列を作り、更に行列を合成していく
    //  MMult  :行列の乗算を行う
    //  MgetRot:引数の回転地だけ軸回転する回転行列を戻り値にする（この場合はbarrelRot度回転する回転行列）
    matRotBomb = MMult(matRotBomb, MGetRotX(bombDir_.x));
    matRotBomb = MMult(matRotBomb, MGetRotY(rot_.y + AsoUtility::Deg2RadF(180.0f)));
    matRotBomb = MMult(matRotBomb, MGetRotZ(rot_.z));

    //  回転行列を使用して、方向ベクトルを回転させる
    weaponDir_ = VTransform({ 0.0f,0.0f,1.0f }, matRot);
    bombDir_ = VTransform({ 0.0f,0.0f,1.0f }, matRotBomb);

    //  方向ベクトルと同じ要領で、弾の相対座標を回転
    VECTOR localPosRot = VTransform(shotLocalPos_, matRot);

    //  弾の位置を設定
    weaponPos_ = VAdd(VAdd(pos_ ,shotLocalPos_), localPosRot);

}

void PlayerBase::Attack(void)
{
    //  リカバリーでも無敵使いたいから、明らかにinvincibleの色々でifを作るべきではなかった。STATUSを変えてあとで処理分けがベストだったなぁ
    //  STATUSの管理がムズい。Aの条件を満たしてるからステータスαにしたいけどBの条件も満たしてるからステータスβにもしたがってる場合どうするか・・・

    if (!invincible_)
    {
        delayAttackCnt_++;
    }

    auto& ins = InputManager::GetInstance();

    //  弾処理
    if (!(ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.TACKLE))&&(invincibleCnt_ > InvincibleCntMax) || isJump_ || isShot_)
    {
        invincible_ = false;
        alreadyAttackHit_ = false;
        return;
    }

    if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.TACKLE))
    { 
        if (delayAttackCnt_ < delayAttack_)
        {
            return;
        }

        if (invincibleCnt_ > InvincibleCntMax)
        {
            delayAttackCnt_ = 0;
            invincibleCnt_ = 0;

            //  PlayerとEnemyのベクトル
            VECTOR PlVec = { pos_.x,0.0f,pos_.z };
            VECTOR EnVec = { enemyPos_.x,0.0f,enemyPos_.z };
            attackPlEnVec_ = VAdd(EnVec, VScale(PlVec, -1.0f));
            attackPlEnVec_ = AsoUtility::NormalizeV(attackPlEnVec_);

            attackFlag = true;
        }
        SoundPlayer(SE_TYPE::TACKLE);
    }


    //  無敵時間カウンタが無敵時間未満だったら
    if (invincibleCnt_ < InvincibleCntMax && attackFlag == true)
    {
        //  突進

        //  MAXで移動距離を割ることによって、動く距離がちょうど敵までになるはず・・・？
        pos_.x += attackPlEnVec_.x * 30.0f;
        pos_.z += attackPlEnVec_.z * 30.0f;
        
        //  無敵フラグをON
        invincible_ = true;
    }
    else
    {
        //  無敵OFF
        invincible_ = false;

        speed_ = 0.0f;

        attackFlag = false;

        alreadyAttackHit_ = false;

    }

    if (attackFlag)
    {
        ChangeStatus(STATUS::TACKLE);
    }
    else
    {
        ChangeStatus(STATUS::IDLE);
    }
}

void PlayerBase::ProcessJump(void)
{
    auto& ins = InputManager::GetInstance();

    //  プレイヤーの入力を検知する
    auto playerCtl = ins.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(playerNumber_));

    //  接地していないと、ジャンプを開始できないようにする
    if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP) && !isJump_)
    {
        isJump_ = true;
        isPutJumpKey_ = true;
        jumpPos_ = pos_;
    }

    //入力時間に応じて、ジャンプ量を変動させる
    if (ins.IsPadBtnNew(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP) && cntJumpInput_ < INPUT_JUMP_FRAME && isPutJumpKey_)
    {
        //  ジャンプカウンタを増やす
        cntJumpInput_++;
        float pow = jumpPow_ + MAX_JUMP_POW / INPUT_JUMP_FRAME;
        SetJumpPow(pow);
        isJump_ = true;
    }

    if (ins.IsPadBtnTrgUp(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP))
    {
        //  ジャンプボタンが離されたとき
        cntJumpInput_ = INPUT_JUMP_FRAME;
    }

}

void PlayerBase::Jump(void)
{
    pos_.y += jumpPow_;

    if (pos_.y < 0.0f)
    {
        pos_.y = 0.0f;
    }

    if (pos_.y > 0.0 && isJump_ && (status_ != STATUS::STUN && status_ != STATUS::RECOVERY))
    {
        ChangeStatus(STATUS::JUMP);
    }
}

void PlayerBase::SetJumpPow(float jumpPow)
{
    //  ジャンプ力を設定
    jumpPow_ = jumpPow;

    //  ジャンプしすぎを防ぐ
    if (jumpPow_ > MAX_JUMP_POW)
    {
        jumpPow_ = MAX_JUMP_POW;
    }
}

void PlayerBase::AddGravity(void)
{
    //  空中ダッシュ中は重力無視
    if (isAirDash_)
    {
        return;
    }

    jumpPow_ -= gravityPow_;

    SetJumpPow(jumpPow_);


}

void PlayerBase::AirDash(void)
{
    if (cntJumpInput_ != INPUT_JUMP_FRAME)
    {
        return;
    }

    auto& ins = InputManager::GetInstance();

    if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP) && airDashCnt_ < MAX_AIRDASH_CNT && !isAirDash_)
    {
        airDashSpeed_ = 3.0f;
        isAirDash_ = true;
        alreadyAirDash_ = true;
        airDashCnt_++;
        SetJumpPow(0.0f);


        //  プレイヤー1（とりあえず1のみ）の入力を検知する
        auto playerCtl = ins.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(playerNumber_));

        int dirX = playerCtl.AKeyLX;
        int dirZ = playerCtl.AKeyLY * -1;

        //  スティックの倒し段階にかかわらず移動距離を一定にしたいので、入力が0～10の1段階目になったら値を固定する
        if (dirX >= 1)
        {
            dirX = 3;
        }
        else if (dirX <= -1)
        {
            dirX = -3;
        }
        if (dirZ >= 1)
        {
            dirZ = 3;
        }
        if (dirZ <= -1)
        {
            dirZ = -3;
        }
        //  空中ダッシュ方向の設定
        airDashDir_.x = dirX;
        airDashDir_.z = dirZ;


    }
    if (isAirDash_)
    {
        //  カメラの角度に合わせて移動ベクトルを回転してから加算
        float CameraHAngle = SceneManager::GetInstance().GetCamera().lock()->GetHAngle();
        VECTOR MoveVector = VScale(airDashDir_, airDashSpeed_);

        //  カメラの角度に合わせて移動ベクトルを回転してから加算
        float SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
        float CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);

        airDashVec_.x = MoveVector.x * CosParam - MoveVector.z * SinParam;
        airDashVec_.y = 0.0f;
        airDashVec_.z = MoveVector.x * SinParam + MoveVector.z * CosParam;







        if (airDashDir_.x == 0 && airDashDir_.z == 0)
        {
            airDashSpeed_ = 0.0f;
        }

        //  移動処理
        pos_ = VAdd(pos_, VScale(airDashVec_, airDashSpeed_));

        if (airDashSpeed_ > 0)
        {
            airDashSpeed_ -= 0.1f;
        }
        if (airDashSpeed_ <= 0.1)
        {
            isAirDash_ = false;
            airDashSpeed_ = 3.0f;
            if (airDashCnt_ >= MAX_AIRDASH_CNT || (airDashDir_.x == 0 && airDashDir_.z == 0))
            {
                SetJumpPow(-8.0f);
            }
        }
    }

}

void PlayerBase::Stun(void)
{  
    size_t size = shots_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (shots_[i]->IsAlive())
        {
            shots_[i]->Blast();
        }
    }

    size = pods_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (pods_[i]->IsAlive())
        {
            pods_[i]->Blast();
        }
    }

    if (stunCnt_ > 180 || stunDmg_ >= 100)
    {
        RecoveryInit();
        //  ステータスをそのままいじってるけど、リカバリー関数を用意すべき（ステータスを戻したり、無敵時間をくれる）
    }
    if (status_ == STATUS::STUN)
    {
        stunCnt_++;
    }
   
}

void PlayerBase::RecoveryInit(void)
{
    ChangeStatus(STATUS::RECOVERY);
    stunCnt_ = 0;
    stunDmg_ = 0;
    stunHp_ = stunHpMax_;
    recovery_ = true;
    recoveryCnt_ = 0;
}

void PlayerBase::Recovery(void)
{
    if (recoveryCnt_ >= 60)
    {
        ChangeStatus(status_ = STATUS::IDLE);
    }
}

void PlayerBase::Hover(void)
{
    if (cntJumpInput_ != INPUT_JUMP_FRAME)
    {
        return;
    }

    auto& ins = InputManager::GetInstance();

    if (alreadyHover_ == false)
    {
        hoverCnt_ = 0;

    }

    if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP) && alreadyHover_ == false)
    {
        isHover_ = true;
        alreadyHover_ = true;
    }

    if (ins.IsPadBtnNew(static_cast<InputManager::JOYPAD_NO>(playerNumber_), keyConfig_.JUMP) && isHover_ == true && hoverCnt_ < MAX_HOVER_CNT)
    {
        if (jumpPow_ <= 0.0f)
        {
            jumpPow_ = 0.0f;
        }
        gravityPow_ = jumpPow_;
        hoverCnt_++;
    }
    else
    {
        isHover_ = false;
        gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
        hoverCnt_ = MAX_HOVER_CNT;
    }
}

void PlayerBase::ShotUpdate(void)
{
    size_t size = shots_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (shots_[i]->IsAlive())
        {
            shots_[i]->Update();
        }
    }

    size = bombs_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (bombs_[i]->IsAlive())
        {
            bombs_[i]->Update();
        }
    } 

    size = pods_.size();
    for (int i = 0; i < size; i++)
    {
        //  i番目の弾が生きていたら
        if (pods_[i]->IsAlive())
        {
            pods_[i]->Update();
        }
    }

}

void PlayerBase::SoundPlayer(SE_TYPE type)
{
    switch (type)
    {
    case PlayerBase::SE_TYPE::SHOT:
        PlaySoundMem(soundShotH_, DX_PLAYTYPE_BACK, true);
        break;
    case PlayerBase::SE_TYPE::BOMB:
        PlaySoundMem(soundBombH_, DX_PLAYTYPE_BACK, true);
        break;
    case PlayerBase::SE_TYPE::POD:
        PlaySoundMem(soundPodH_, DX_PLAYTYPE_BACK, true);
        break;
    case PlayerBase::SE_TYPE::DAMAGE:
        PlaySoundMem(soundDamageH_, DX_PLAYTYPE_BACK, true);
        break;
    case PlayerBase::SE_TYPE::TACKLE:
        PlaySoundMem(soundTackleH_, DX_PLAYTYPE_BACK, true);
        break;
    default:
        break;
    }
}

void PlayerBase::SetModelStageId(int stageId)
{
    modelStageId_ = stageId;
}

void PlayerBase::SetModelCoverId(int coverId)
{
    modelStageCoverId_ = coverId;
}

int PlayerBase::GetPlayerModelId(void)
{
    return modelId_;
}

bool PlayerBase::GetInvincible(void)
{
    return invincible_;
}

bool PlayerBase::GetRecovery(void)
{
    return recovery_;
}

int PlayerBase::GetAttackDamage(void)
{
    return attackDamage_;
}

void PlayerBase::SetAlreadyAttack(bool hit)
{
    alreadyAttackHit_ = hit;
}

bool PlayerBase::GetAlreadyAttack(void)
{
    return alreadyAttackHit_;
}

PlayerBase::POD_TYPE PlayerBase::GetPodType(void)
{
    return podType_;
}

void PlayerBase::ChangeStatus(STATUS state)
{
    status_ = state;
}

std::vector<std::shared_ptr<WeaponBase>> PlayerBase::GetShots(void)
{
    return shots_;
}

std::vector<std::shared_ptr<WeaponBase>> PlayerBase::GetBombs(void)
{
    return bombs_;
}

std::vector<std::shared_ptr<WeaponBase>> PlayerBase::GetPods(void)
{
    return pods_;
}

PlayerBase::SHOT_TYPE PlayerBase::GetShotType(void)
{
    return shotType_;
}

PlayerBase::BOMB_TYPE PlayerBase::GetBombType(void)
{
    return bombType_;
}


