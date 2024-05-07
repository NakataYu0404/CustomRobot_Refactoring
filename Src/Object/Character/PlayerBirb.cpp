#include "../../Manager/SceneManager.h"
#include "PlayerBirb.h"

void PlayerBirb::SetParam(void)
{
    //  �傫���̐ݒ�
    scl_ = { 0.3f,0.3f,0.3f };

    //  �ړ��X�s�[�h(1�����ɐݒ肵�Ă���������)
    speed_ = 1.0f;

    stunHpMax_ = 100;
    stunHp_ = stunHpMax_;
    defensePower_ = 5;

    attackDamage_ = 500;

    gravityPow_ = SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;

    airDashSpeed_ = 3.0f;

    //  �ő呬�x
    MAX_MOVE_SPEED = 10.0f;

    //  �G�A�_�b�V���ł����
    MAX_AIRDASH_CNT = 3;
    MAX_HOVER_CNT = 120;

    //  �W�����v�L�[���͂��󂯕t����t���[����
    INPUT_JUMP_FRAME = 12;

    //	�ő�W�����v��
    MAX_JUMP_POW = 8.0f;

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
