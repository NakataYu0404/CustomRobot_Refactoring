#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:


	// ���\�[�X��
	enum class SRC
	{
		//	�摜
		IMG_TITLE,		//	�^�C�g��

		IMG_1P_WIN,		//	����
		IMG_2P_WIN,

		IMG_1P_NUM0,	//	�v���C���[���Ƃ̗̑͂�\������
		IMG_1P_NUM1,	//	�����Ă�摜�̃X�v���C�g����ɓ������炱�����ɂ܂Ƃ߂����c
		IMG_1P_NUM2,
		IMG_1P_NUM3,
		IMG_1P_NUM4,
		IMG_1P_NUM5,
		IMG_1P_NUM6,
		IMG_1P_NUM7,
		IMG_1P_NUM8,
		IMG_1P_NUM9,
		IMG_2P_NUM0,
		IMG_2P_NUM1,
		IMG_2P_NUM2,
		IMG_2P_NUM3,
		IMG_2P_NUM4,
		IMG_2P_NUM5,
		IMG_2P_NUM6,
		IMG_2P_NUM7,
		IMG_2P_NUM8,
		IMG_2P_NUM9,

		IMG_1P_HPBAR,		//	HP�o�[�̘g�g��
		IMG_2P_HPBAR,

		IMG_HPSCALE,	//	HP�̃�����

		IMG_HPBLACK,	//	HP�o�[�̍��w�i

		IMG_COUNTDOWN_NUM1,	//	�Q�[���J�n���̃J�E���g�_�E������
		IMG_COUNTDOWN_NUM2,
		IMG_COUNTDOWN_NUM3,
		IMG_COUNTDOWN_NUM4,
		IMG_COUNTDOWN_NUM5,

		IMG_GAMESTART,	//	�J�E���g�_�E���I�����̃Q�[���X�^�[�g

		IMG_BIRB,		//	�L�����N�^�[����
		IMG_YETI,
		IMG_CACTORO,
		IMG_BEMON,
		IMG_GHOST,

		IMG_MACHINE,	//	�K������
		IMG_PUNCH,
		IMG_SNIPER,
		IMG_CANNON,		//	�{������
		IMG_DELAY,
		IMG_BOUNCE,		//	�|�b�h����
		IMG_AIR,
		IMG_STICKY,

		IMG_AIRDASH,	//	���b�O����
		IMG_HOVER,

		IMG_READY,		//	���������ɃJ�[�\�������킹���Ƃ��̉摜

		IMG_1P_CUSTOMEND,	//	��������
		IMG_2P_CUSTOMEND,

		IMG_SELECT_ANIM1,	//	�I�𑀍�����A�j���[�V����
		IMG_SELECT_ANIM2,
		IMG_SELECT_ANIM3,

		IMG_SMOKE,		//	�����X���[�N�摜

		IMG_STUN_ANIM1,	//	�X�^���摜�A�j���[�V����
		IMG_STUN_ANIM2,
		IMG_STUN_ANIM3,
		IMG_STUN_ANIM4,

		IMG_INSTRUCTION_BASE,	//	��{��������摜
		IMG_INSTRUCTION_ATTACK,	//	�U����������摜

		//	���f��
		MDL_SKYDOME,	//	�X�J�C�h�[��

		MDL_BIRB,		//	�L�����N�^�[
		MDL_YETI,
		MDL_CACTORO,
		MDL_BEMON,
		MDL_GHOST,

		MDL_STAGE,		//	�X�e�[�W
		MDL_COVER,		//	�����Ȃ��X�e�[�W�J�o�[(�����蔻�肾������)
		MDL_CHAR,		//	�X�e�[�W�̒n�ʂɏo������

		MDL_CROSSHAIR,	//	�N���X�w�A���f��(�L���m���{���Ŏg�p)
		MDL_SHOT,		//	�ʏ�V���b�g
		MDL_FIST,		//	��
		MDL_SPIKESHOT,	//	�g�Q(�o�E���X�A�X�e�B�b�L�[�|�b�h�Ŏg�p)
		MDL_BIRD,		//	��(�X�J�C�|�b�h�Ŏg�p)

	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	const Resource& Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, Resource*> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	// �������[�h
	Resource& _Load(SRC src);

};
