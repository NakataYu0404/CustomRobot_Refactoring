#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SceneBase.h"
#include "../Object/PlayerBase.h"
#include "../Object/Character/PlayerBirb.h"
#include "../Object/Character/PlayerYeti.h"
#include "../Object/Character/PlayerCactoro.h"
#include "../Object/Character/PlayerBemon.h"
#include "../Object/Character/PlayerGhost.h"


class PlayerBase;
class PlayerBirb;
class PlayerYeti;
class PlayerCactoro;
class PlayerBemon;


class CustomScene : public SceneBase
{

public:

	//	���ǂ��̃p�[�c��I�ڂ��Ƃ��Ă��邩
	enum class SelectState
	{
		NORMAL,
		BODY,
		GUN,
		BOMB,
		POD,
		REG,
		FINISH
	};

	//	�̃p�[�c
	enum class BODY_TYPE
	{
		Birb,
		Yeti,
		Cactoro,
		Bemon,
		Ghost,

	};


	// �R���X�g���N�^
	CustomScene(void);

	// �f�X�g���N�^
	~CustomScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//	�v���C���[�|�C���^�̎擾(SceneManager���J�X�^���V�[������Q�[���V�[���Ƀ|�C���^��n�����߂Ƀ|�C���^��~�������Ă�)
	std::weak_ptr<PlayerBase> GetPlayer(int plNum);

private:
	// �f�̂̃��X�g
	std::vector <std::string> body;
	// �K���̃��X�g
	std::vector <std::string> gun;
	// �{���̃��X�g
	std::vector <std::string> bomb;
	// �|�b�h�̃��X�g
	std::vector <std::string> pod;
	// ���b�O�̃��X�g
	std::vector <std::string> reg;

	//	�Z���N�g�E�B���h�E�̍ő�A���݃T�C�Y
	VECTOR windowMaxSizeSelect;
	VECTOR windowSizeSelect[2];

	//	�t�H���g�n���h��
	int fontH;
	//	�����`�悷��Ƃ��p�v���C���[���Ƃ̃J���[�n���h��
	int color_[2];

	// �e�p�[�c�I���X�N���[���A�v���C���[�v���r���[�X�N���[�����܂Ƃ߂�X�N���[���@�����BACK�ɕ`�悷��
	int FullScreenH;
	// �e�p�[�c�I����ʃX�N���[���n���h��
	int bodyScreenH[2];
	int gunScreenH[2];
	int bombScreenH[2];
	int podScreenH[2];
	int regScreenH[2];

	// �v���C���[�v���r���[
	int PreviewScreenH[2];
	// �v���C���[���Ƃɂ܂Ƃ߂��X�N���[��
	int plScreenH[2];

	// �v���C���[�A����̐��������Ă����X�N���[��
	int expoScreenH[2];

	//	�e�X�N���[�����쐬����ۂɗp���錄�ԃT�C�Y(�s�ԂƂ�)
	int blank;

	// �L�[�R���t�B�O
	PlayerBase::KEY_CONFIG keyPl;

	// �摜�A���f���n���h���B
	int UIBoxH;
	int arrowH[59];

	int arrowAnimCnt_;

	int plEndH_[2];

	int modelBirbH_;
	int modelYetiH_;
	int modelCactoroH_;
	int modelBemonH_;
	int modelGhostH_;

	int imageBirbH_;
	int imageYetiH_;
	int imageCactoroH_;
	int imageBemonH_;
	int imageGhostH_;

	int imageMachineH_;
	int imagePunchH_;
	int imageSniperH_;
	int imageCannonH_;
	int imageDelayH_;
	int imageBounceH_;
	int imageAirH_;
	int imageStickyH_;
	int imageAirdashH_;
	int imageHoverH_;

	int imageReadyH_;

	int imageSelectH_[3];
	int selectImgCnt_;

	int soundBgmH_;
	
	//	�J�X�^���I���摜�ʒu(�ړ����邽�ߕK�v)
	VECTOR ImageEndPos_[2];

	// �I������Ă���v���C���[���f����id
	int modelPlayerId_[2];

	//	�J�[�\������̍ۂɗp����A�R���g���[���[�X�e�B�b�N�̌X���A�P�t���O�̌X��
	int ControllerTilt_[2];
	int ControllerTiltOld_[2];

	// ���ݕ`�悵�Ă���X�N���[���̃X�e�[�g
	SelectState select_[2];

	// �J�[�\���̃X�e�[�g(����{�^���������ꂽ���A���̃X�e�[�g��select_������select_�̃X�e�[�g��cursor_�ɁB)
	SelectState cursor_[2];
	SelectState cursorOld_[2];

	//	�J�[�\���̈ʒu
	VECTOR arrowPos_[2];

	//	�J�X�^�����I��������t���O
	bool finishFlag_[2];
	bool finishChangeFlag_[2];

	//	�v���C���[
	std::shared_ptr<PlayerBase> players_[2];
	 
	//	�������v���C���[1��2��
	PlayerBase::TYPE type_[2];

	//	�e��p�[�c�̃^�C�v
	BODY_TYPE bodyType_[2];
	PlayerBase::SHOT_TYPE shotType_[2];
	PlayerBase::BOMB_TYPE bombType_[2];
	PlayerBase::POD_TYPE podType_[2];
	PlayerBase::REG_TYPE regType_[2];

	//	�e��p�[�c�I���̂Ƃ��A�J�[�\�����ǂ��ɂ�����(�J�[�\���ʒu��ۑ����āA�ĂъJ�����Ƃ��ɁA�O��ʒu����J�[�\�����o�������邽�߂ɕK�v)
	PlayerBase::SHOT_TYPE cursorShot_[2];
	PlayerBase::BOMB_TYPE cursorBomb_[2];
	PlayerBase::POD_TYPE cursorPod_[2];
	PlayerBase::REG_TYPE cursorReg_[2];

	//	�X�N���[���̐؂�ւ��i���݃X�N���[��A�ƁA�p�[�c�I����ʑI���̌��莞�ɃJ�[�\��������Ă��p�[�c�I����ʃX�N���[��B�̐؂�ւ��j
	void ChangeScreen(int player);
	// ���ꂼ��J�X�^�����I���������ɁA����A�̂�ݒ肷��(���̂��ƃQ�[���V�[����)
	void ChangeWeapon(int plNum);
	void ChangeBody(int plNum);

	//	�J�[�\���ړ��ƕ`��
	void Cursor(void);

	//	�e��p�[�c�`��X�N���[���̕`��
	void DrawBodyScreen(int player);
	void DrawShotScreen(int player);
	void DrawBombScreen(int player);
	void DrawPodScreen(int player);
	void DrawRegScreen(int player);

	//	���������`��X�N���[���̕`��
	void DrawExpoScreen(int player);

	//	�v���C���[�`��X�N���[���̕`��
	void DrawPreviewScreen(int player);

	// �E�B���h�E�����񂾂�ł����ȁ[��
	void WindowBeBig(int player, int maxSizeY);
};
