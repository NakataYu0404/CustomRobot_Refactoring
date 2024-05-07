#include "../../Manager/SceneManager.h"
#include "PlayerGhost.h"

void PlayerGhost::SetParam(void)
{
    //  �傫���̐ݒ�
    scl_ = { 0.3f,0.3f,0.3f };

    //  �ړ��X�s�[�h(1�����ɐݒ肵�Ă���������)
    speed_ = 0.3f;          //  birb1

    stunHpMax_ = 80;       //  birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 4;      //  birb5

    attackDamage_ = 200;    //  birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 2.4f;   //  birb3.0

    //  �ő呬�x
    MAX_MOVE_SPEED = 6.0f;    //  birb10

    //  �G�A�_�b�V���ł����
    MAX_AIRDASH_CNT = 4;    //  birb3
    MAX_HOVER_CNT = 160;

    //  �W�����v�L�[���͂��󂯕t����t���[����
    INPUT_JUMP_FRAME = 16;  //  birb12

    //	�ő�W�����v��
    MAX_JUMP_POW = 12.0f;    //  birb8

    playerAnim_.IdleAnim = 7;
    playerAnim_.WalkAnim = 2;
    playerAnim_.RunAnim = 1;
    playerAnim_.JumpAnim = 2;
    playerAnim_.StunAnim = 5;

    //  �A�j���[�V�������A�^�b�`����
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    //  �A�^�b�`���Ă���A�j���[�V�����̑��Đ����Ԃ��擾����
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
