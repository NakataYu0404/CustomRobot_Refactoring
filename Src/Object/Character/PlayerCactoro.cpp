#include "../../Manager/SceneManager.h"
#include "PlayerCactoro.h"

void PlayerCactoro::SetParam(void)
{
    //  �傫���̐ݒ�
    scl_ = { 0.3f,0.3f,0.3f };

    //  �ړ��X�s�[�h(1�����ɐݒ肵�Ă���������)
    speed_ = 1.2f;          //  birb1

    stunHpMax_ = 80;       //  birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 4;      //  birb5

    attackDamage_ = 400;    //  birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 0.0f;   //  birb3.0

    //  �ő呬�x
    MAX_MOVE_SPEED = 14.0f;    //  birb10

    //  �G�A�_�b�V���ł����
    MAX_AIRDASH_CNT = 0;    //  birb3
    MAX_HOVER_CNT = 0;

    //  �W�����v�L�[���͂��󂯕t����t���[����
    INPUT_JUMP_FRAME = 0;  //  birb12

    //	�ő�W�����v��
    MAX_JUMP_POW = 0.0f;    //  birb8

    playerAnim_.IdleAnim = 3;
    playerAnim_.WalkAnim = 10;
    playerAnim_.RunAnim = 9;
    playerAnim_.JumpAnim = 5;
    playerAnim_.StunAnim = 7;

    //  �A�j���[�V�������A�^�b�`����
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    //  �A�^�b�`���Ă���A�j���[�V�����̑��Đ����Ԃ��擾����
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
