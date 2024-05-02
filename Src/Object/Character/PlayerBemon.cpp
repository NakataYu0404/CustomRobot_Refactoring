#include "../../Manager/SceneManager.h"
#include "PlayerBemon.h"

void PlayerBemon::SetParam(void)
{
    // �傫���̐ݒ�
    scl_ = { 0.5f,0.5f,0.5f };

    // �ړ��X�s�[�h(1�����ɐݒ肵�Ă���������)
    speed_ = 0.6f;          // birb1

    stunHpMax_ = 160;       // birb100
    stunHp_ = stunHpMax_;
    defensePower_ = 6.0f;      // birb5

    attackDamage_ = 1000;    // birb500

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 3.0f;   // birb3.0

    // �ő呬�x
    MAX_MOVE_SPEED = 8.0f;    // birb10

    // �G�A�_�b�V���ł����
    MAX_AIRDASH_CNT = 2;    // birb3
    MAX_HOVER_CNT = 80;

    // �W�����v�L�[���͂��󂯕t����t���[����
    INPUT_JUMP_FRAME = 10;  // birb12

    //	�ő�W�����v��
    MAX_JUMP_POW = 8.0f;    // birb8

    playerAnim_.IdleAnim = 3;
    playerAnim_.WalkAnim = 11;
    playerAnim_.RunAnim = 9;
    playerAnim_.JumpAnim = 5;
    playerAnim_.StunAnim = 7;

    // �A�j���[�V�������A�^�b�`����
    MV1DetachAnim(modelId_, animAttachNo_);
    animAttachNo_ = MV1AttachAnim(modelId_, playerAnim_.IdleAnim);

    // �A�^�b�`���Ă���A�j���[�V�����̑��Đ����Ԃ��擾����
    animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

}
