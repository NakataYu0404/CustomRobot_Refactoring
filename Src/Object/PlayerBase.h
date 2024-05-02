#pragma once
#include <vector>
#include <string>
#include <memory>
#include <DxLib.h>
#include "../Manager/InputManager.h"


class GameScene;
class WeaponBase;

class PlayerBase
{
public:

	// �Փ˔��a
	static constexpr float COL_RADIUS = 35.0f;

	// ��]��(deg)
	static constexpr float SPEED_ROT = 8.0f;

	// ��]��(rad)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * DX_PI_F / 180.0f;

	// �����̃A�j���[�V������
	static constexpr int BLAST_ANIM_NUM = 16;

	// �����̃T�C�Y
	static constexpr int BLAST_SIZE_X = 32;
	static constexpr int BLAST_SIZE_Y = 32;

	static constexpr float MIN_MOVE_SPEED = 0.1f;
	// ����(accelerator=�A�N�Z�����[�^�[)
	static constexpr float MOVE_ACC = 0.10f;

	// �̗͍ő�l
	const int hpMax_ = 999;

	const float BOMB_HIGHEST = 500.0f;

	int InvincibleCntMax = 10;

	int smokeImage_[12];
	VECTOR smokeSpriteSize_ = { 176,61,0 };
	VECTOR jumpPos_;
	int smokesprite = 0;
	bool isSpriteEnd_;

	int stunImgs_[4];

	enum class TYPE
	{
		// 1P,2P
		NONE,
		PLAYER_1,
		PLAYER_2,
		MAX
	};

	struct KEY_CONFIG
	{
		// �L�[�R���t�B�O(1P,2P)
		InputManager::JOYPAD_BTN SHOT;
		InputManager::JOYPAD_BTN BOMB;
		InputManager::JOYPAD_BTN POD;
		InputManager::JOYPAD_BTN JUMP;
		InputManager::JOYPAD_BTN AIRDASH;
		InputManager::JOYPAD_BTN TACKLE;

	};

	enum class STATUS
	{
		IDLE,
		WALK,
		RUN,
		JUMP,
		STUN,
		TACKLE,
		RECOVERY
	};

	// �e��
	struct BULLETS
	{
		static constexpr int S_MACHINE = 8;
		static constexpr int S_ELECSHOCK = 1;
		static constexpr int S_SNIPER = 1;
		static constexpr int B_CANNON = 1;
		static constexpr int B_MINE = 1;
		static constexpr int P_BOUNCE = 10;
		static constexpr int P_FREEZE = 2;
		static constexpr int P_STICKY = 1;
	};

	struct WeaponDelay
	{
		static constexpr int S_MACHINE = 25;
		static constexpr int S_ELECSHOCK = 1;
		static constexpr int S_SNIPER = 100;
		static constexpr int B_CANNON = 150;
		static constexpr int B_MINE = 220;
		static constexpr int P_BOUNCE = 50;
		static constexpr int P_FREEZE = 100;
		static constexpr int P_STICKY = 60;
	};

	enum class ATTACK_TYPE
	{
		SHOT,
		BOMB,
		POD,
		MAX
	};

	enum class SHOT_TYPE
	{
		MACHINE,
		ELECSHOCK,
		SNIPER,
		MAX,
	};

	enum class BOMB_TYPE
	{
		CANNON,
		MINE,
		MAX,
	};

	enum class POD_TYPE
	{
		BOUNCE,
		FREEZE,
		STICKY,
		MAX,
	};


	enum class REG_TYPE
	{
		AIRDASH,
		HOVER,
		MAX
	};

	struct PlayerAnim
	{
		int IdleAnim;
		int WalkAnim;
		int RunAnim;
		int JumpAnim;
		int StunAnim;
	};

	// �R���X�g���N�^
	PlayerBase(void);

	// �f�X�g���N�^
	~PlayerBase(void);

	// ��������(�ŏ���1��̂ݎ��s)
	void Init(TYPE type, KEY_CONFIG keyConfig);

	void ChangeBody(int modelId);
	void ChangeShot(SHOT_TYPE shotType);
	void ChangeBomb(BOMB_TYPE bombType);
	void ChangePod(POD_TYPE podType);
	void ChangeReg(REG_TYPE regType);

	// �p�����[�^�ݒ�(�������z�֐�)
	virtual void SetParam(void);

	// ���ʂ̃p�����[�^�ݒ�(�L�����ɂ���ĕς��Ȃ�)
	void SetCommon(void);

	// �X�V����(���t���[�����s)
	void Update(void);

	// �`�揈��(���t���[�����s)
	void Draw(void);

	// �������(�Ō�̂P��̂ݎ��s)
	void Release(void);

	void Animation(void);
	void ChangeAnim(void);

	// ���W�̎擾
	VECTOR GetPos(void);

	// �Փ˔�����W�̎擾
	VECTOR GetColPos(void);

	VECTOR GetScl(void);

	// ���W�̐ݒ�
	void SetPos(VECTOR pos);

	// ��������
	bool IsAlive(void);

	// ���������ݒ�
	void SetAlive(bool alive);

	// �_���[�W��^����
	void Damage(int hpDamage,int stunDamage,VECTOR weaponDir,ATTACK_TYPE type);

	// �Փ˔��苅�̔��a���擾����
	float GetRadius(void);

	// HP���擾����
	int GetHp(void);
	
	// �X�^���l���擾����
	int GetStunHp(void);


	// �G�ʒu���Z�b�g����(�G�Ɍ������Č��e�Ɏg���Ă���)�Q�[���V�[������Z�b�g����Ă���B
	void SetEnemyPos(VECTOR pos);

	// �e�̎擾
	std::vector<std::shared_ptr<WeaponBase>> GetShots(void);
	std::vector<std::shared_ptr<WeaponBase>> GetBombs(void);
	std::vector<std::shared_ptr<WeaponBase>> GetPods(void);

	SHOT_TYPE GetShotType(void);
	BOMB_TYPE GetBombType(void);

	// �X�e�[�W�ƊW��ID���Q�[���V�[���������Ă���(�����蔻����쐬���邽�߂ɕK�v)
	void SetModelStageId(int stageId);
	void SetModelCoverId(int coverId);

	// ���f��ID�擾
	int GetPlayerModelId(void);

	// ���G���H
	bool GetInvincible(void);
	bool GetRecovery(void);

	// �A�^�b�N�̃_���[�W
	int GetAttackDamage(void);

	// SETGET�ǂ���������N���X�Ŏg���Ȃ炱�̊֐����g������ɕϐ����Ηǂ��悤�ȋC�����邪�A�v���C���[���Ƃɕϐ��𕪂��邽�߂ɕK�v
	void SetAlreadyAttack(bool hit);
	bool GetAlreadyAttack(void);

	POD_TYPE GetPodType(void);

	void ChangeStatus(STATUS state);

protected:

	enum class SE_TYPE
	{
		SHOT,
		BOMB,
		POD,
		DAMAGE,
		TACKLE
	};

	// �u�L�n
	// �g���u�L�킪����
	SHOT_TYPE shotType_;
	BOMB_TYPE bombType_;
	POD_TYPE podType_;
	REG_TYPE regType_;

	// ���˂����e���̃J�E���^
	int shotFireCnt_;
	int bombFireCnt_;
	int podFireCnt_;

	int shotFlameCnt_;
	int podFlameCnt_;

	// �e�����ˉ\�ɂȂ�܂ł̃J�E���^
	int delayShotCnt_;
	int delayShot_;
	// �{�������ˉ\�ɂȂ�܂ł̃J�E���^
	int delayBombCnt_;
	int delayBomb_;
	// �|�b�h�����ˉ\�ɂȂ�܂ł̃J�E���^
	int delayPodCnt_;
	int delayPod_;

	int delayAttackCnt_;
	int delayAttack_;

	// ���ݒe�������Ă��邩(�����Ă����瑫��x������)
	bool isShot_;

	// �c�e��
	int shotBullet_;
	int bombBullet_;
	int podBullet_;

	// �ړ����x�̍ő�l
	float MAX_MOVE_SPEED;

	// �W�����v�A�󒆃A�N�V�����n
	// �G�A�_�b�V���A�W�����v�ł����
	int MAX_AIRDASH_CNT;

	// �z�o�[�ł��鎞��
	int MAX_HOVER_CNT;

	// �W�����v�L�[���͂��󂯕t����t���[����
	int INPUT_JUMP_FRAME;

	//	�ő�W�����v��
	float MAX_JUMP_POW;

	// ���݃W�����v�����̔��� YES�ŃW�����v��
	bool isJump_;

	// �W�����v�L�[�̉�������
	bool isPutJumpKey_;

	// �W�����v�L�[���̓J�E���^
	int cntJumpInput_;

	// ���G�A�_�b�V�������H
	bool isAirDash_;

	// ���łɃG�A�_�b�V�����s�������H
	bool alreadyAirDash_;

	// �G�A�_�b�V��������g�������̃J�E���^
	int airDashCnt_;

	bool isHover_;
	bool alreadyHover_;
	int hoverCnt_;

	// Init�n
	// ���ƂȂ�v���C���[�̃��f��ID
	int baseModelId_;


	// �v���C���[�̃��f��ID
	int modelId_;
	int modelIdOld_;

	// �ړ����x
	float speed_;

	// �󒆃_�b�V�����x
	float airDashSpeed_;

	// �̗�
	int hp_;

	// �X�^���l�̍ő�(�X�^�����₷��)�̓L�����ɂ���ĕύX������
	int stunHpMax_;
	// �X�^���l
	int stunHp_;

	// �A�^�b�N�������疳�G�Ȃ̂��H
	bool attackFlag;
	// �̓�����̃_���[�W
	int attackDamage_;

	bool alreadyAttackHit_;

	// �X�^�����ɂ�������_���[�W
	int stunDmg_;
	// �X�^�����Ă��鎞��
	int stunCnt_;

	// �h���(hp-damage/�h���=damage)
	float defensePower_;

	// �Ō�Ɏ��������������U���̎��
	ATTACK_TYPE lastHitType_;

	// �W�����v��
	float jumpPow_;

	// ���݂̏��
	STATUS status_;

	// �傫��
	VECTOR scl_;

	// �p�x
	VECTOR rot_;

	// �\�����W
	VECTOR pos_;

	// �G�̈ʒu
	VECTOR enemyPos_;

	// �ړ�����
	VECTOR dir_;

	// �󒆃_�b�V������
	VECTOR airDashDir_;

	// ���ۂɈړ�����x�N�g��
	VECTOR airDashVec_;


	// �A�j���[�V�������A�^�b�`����ԍ�
	int animAttachNo_;

	// �A�j���[�V�����̑��Đ�����
	float animTotalTime_;

	// �Đ����̃A�j���[�V��������
	float stepAnim_;

	PlayerAnim playerAnim_;

	// �A�j���[�V�������x
	float speedAnim_;

	// ��������Փ˔���Ɏg�������ǂ̂��炢�ړ������邩�i��{�I��Y�̂݁j
	VECTOR collisionLocalPos_;

	// �d��
	float gravityPow_;

	// ��������
	bool isAlive_;

	bool invincible_;
	int invincibleCnt_;
	bool recovery_;
	int recoveryCnt_;


	// �v���C���[�ԍ�
	TYPE playerNumber_;

	// �L�[�R���t�B�O
	KEY_CONFIG keyConfig_;

	// �v���C���[����G��X���p�x
	float PlEnAngleDegX;

	// �e�̃��f��ID
	int modelShotId_;
	int modelPodId_;
	int modelBombId_;
	int modelStageId_;
	int modelStageCoverId_;

	// �����̉摜(�{���͊O�����\�[�X�p�̊Ǘ��N���X�����ׂ��B�e���f����)
	int blastImgs_[BLAST_ANIM_NUM];

	int soundDamageH_;
	int soundShotH_;
	int soundBombH_;
	int soundPodH_;
	int soundTackleH_;


	// �e������VECTOR
	VECTOR weaponDir_;
	VECTOR bombDir_;
	float bombDirX_;
	VECTOR shotLocalPos_;
	VECTOR weaponPos_;


	// �V���b�g(�|�C���^)
	std::vector<std::shared_ptr<WeaponBase>> shots_;
	std::vector<std::shared_ptr<WeaponBase>> bombs_;
	std::vector<std::shared_ptr<WeaponBase>> pods_;

	int newPod = 0;

	// �G�Ƃ̋����̒���
	float PythagorasDisXZ_;

	// �̓����肷��Ƃ��̎����ƓG�̃x�N�g��(�m�[�}���C�Y����Ă���)
	VECTOR attackPlEnVec_;


	// HP�̊e�ʂ̐���
	int hpHundredPlace_;
	int hpTensPlace_;
	int hpOnesPlace_;

	void DrawUI(void);

	// �U������
	void Fire(SHOT_TYPE shotType, BOMB_TYPE bombType, POD_TYPE podType);
	void Shot(SHOT_TYPE shotType);
	void Bomb(BOMB_TYPE bombType);
	void Pod(POD_TYPE podType);

	void Attack(void);

	// �ړ�����
	void Move(void);
	void ProcessMove(void);
	void Accele(float speed);
	void Decelerate(void);

	// �����p�x����
	void Turn(void);

	// �W�����v����
	void ProcessJump(void);

	// �W�����v
	void Jump(void);

	// �W�����v�͂�ݒ�
	void SetJumpPow(float jumpPow);

	// �d��
	void AddGravity(void);

	// �󒆃_�b�V��
	void AirDash(void);

	// �z�o�[
	void Hover(void);
	void Stun(void);
	void RecoveryInit(void);
	void Recovery(void);

	// �e�̏���
	void ShotUpdate(void);

	void SoundPlayer(SE_TYPE type);

private:



};

