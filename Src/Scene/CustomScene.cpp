#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/InputManager.h"
#include "../Object/Grid.h"
#include "GameScene.h"
#include "CustomScene.h"

CustomScene::CustomScene(void)
{
}

CustomScene::~CustomScene(void)
{
}

void CustomScene::Init(void)
{
	blank = 40;

	// あとから出てくるタイプのウィンドウのマックスサイズ
	windowMaxSizeSelect = { 480.0f,0.0f,0.0f };

	modelBirbH_ = MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str());
	modelYetiH_ = MV1LoadModel((Application::PATH_MODEL + "Enemy/Yeti.mv1").c_str());
	modelCactoroH_ = MV1LoadModel((Application::PATH_MODEL + "Enemy/Cactoro.mv1").c_str());
	modelBemonH_ = MV1LoadModel((Application::PATH_MODEL + "Enemy/BlueDemon.mv1").c_str());
	modelGhostH_ = MV1LoadModel((Application::PATH_MODEL + "Enemy/Ghost.mv1").c_str());

	imageBirbH_ = LoadGraph((Application::PATH_IMAGE + "Enemy/birb.png").c_str());
	imageYetiH_ = LoadGraph((Application::PATH_IMAGE + "Enemy/yeti.png").c_str());
	imageCactoroH_ = LoadGraph((Application::PATH_IMAGE + "Enemy/cactoro.png").c_str());
	imageBemonH_ = LoadGraph((Application::PATH_IMAGE + "Enemy/bluedemon.png").c_str());
	imageGhostH_ = LoadGraph((Application::PATH_IMAGE + "Enemy/ghost.png").c_str());

	 imageMachineH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/machine.png").c_str());
	 imagePunchH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/punch.png").c_str());
	 imageSniperH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/sniper.png").c_str());
	 imageCannonH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/cannon.png").c_str());
	 imageDelayH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/delay.png").c_str());
	 imageBounceH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/bounce.png").c_str());
	 imageAirH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/air.png").c_str());
	 imageStickyH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/sticky.png").c_str());
	 imageAirdashH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/airdash.png").c_str());
	 imageHoverH_ = LoadGraph((Application::PATH_IMAGE + "Weapon/hover.png").c_str());

	 imageReadyH_ = LoadGraph((Application::PATH_IMAGE + "ready.png").c_str());

	for (int i = 0; i < 3; i++)
	{
		imageSelectH_[i] = LoadGraph((Application::PATH_IMAGE + "Select/select" + std::to_string(i + 1) + ".png").c_str());
	}

	body.push_back("バーブ");
	body.push_back("イエティ");
	body.push_back("カクトロ");
	body.push_back("ベーモン");
	body.push_back("ゴースト");

	gun.push_back("マシンガン");
	gun.push_back("パンチガン");
	gun.push_back("スナイプガン");

	bomb.push_back("キャノンボム");
	bomb.push_back("ディレイボム");

	pod.push_back("バウンスポッド");
	pod.push_back("エアーポッド");
	pod.push_back("スティッキーポッド");

	reg.push_back("エアーダッシュ");
	reg.push_back("ホバーレッグ");

	FullScreenH = MakeScreen(Application::GetInstance().SCREEN_SIZE_X, Application::GetInstance().SCREEN_SIZE_Y);
	for (int plNum = 0; plNum < 2; plNum++)
	{
		modelPlayerId_[plNum] = modelBirbH_;

		windowSizeSelect[plNum] = { 0.0f,0.0f,0.0f };

		bodyScreenH[plNum] = MakeScreen(windowMaxSizeSelect.x, (body.size() + 2) * blank);
		gunScreenH[plNum] = MakeScreen(windowMaxSizeSelect.x, (gun.size() + 2) * blank);
		bombScreenH[plNum] = MakeScreen(windowMaxSizeSelect.x, (bomb.size() + 2) * blank);
		podScreenH[plNum] = MakeScreen(windowMaxSizeSelect.x, (pod.size() + 2) * blank);
		regScreenH[plNum] = MakeScreen(windowMaxSizeSelect.x, (reg.size() + 2) * blank);
		PreviewScreenH[plNum] = MakeScreen(428/*316*/, 428/*316*/);

		expoScreenH[plNum] = MakeScreen(600, 428);

		plScreenH[plNum] = MakeScreen(Application::GetInstance().SCREEN_SIZE_X, Application::GetInstance().SCREEN_SIZE_Y / 2);
	}

	color_[0] = GetColor(255, 60, 20);
	color_[1] = GetColor(20, 60, 255);


	keyPl = {
		InputManager::JOYPAD_BTN::LEFT,
		InputManager::JOYPAD_BTN::DOWN,
		InputManager::JOYPAD_BTN::R,
		InputManager::JOYPAD_BTN::L,
		InputManager::JOYPAD_BTN::ZR,
		InputManager::JOYPAD_BTN::ZL,


	};

	selectImgCnt_ = 0;

	for (int plNum = 0; plNum < 2; plNum++)
	{
		// プレイヤーのモデル
		modelPlayerId_[plNum] = MV1LoadModel((Application::PATH_MODEL + "Enemy/Birb.mv1").c_str());

		select_[plNum] = SelectState::NORMAL;
		cursor_[plNum] = SelectState::BODY;
		cursorOld_[plNum] = cursor_[plNum];

		finishFlag_[plNum] = false;
		finishChangeFlag_[plNum] = false;

		// 1Playerの初期化
		players_[plNum] = std::make_shared<PlayerBase>();

		// 初期のパーツタイプ
		type_[0] = PlayerBase::TYPE::PLAYER_1;
		type_[1] = PlayerBase::TYPE::PLAYER_2;
		shotType_[plNum] = PlayerBase::SHOT_TYPE::MACHINE;
		bombType_[plNum] = PlayerBase::BOMB_TYPE::CANNON;
		podType_[plNum] = PlayerBase::POD_TYPE::BOUNCE;
		regType_[plNum] = PlayerBase::REG_TYPE::AIRDASH;

		cursorShot_[plNum] = PlayerBase::SHOT_TYPE::MACHINE;
		cursorBomb_[plNum] = PlayerBase::BOMB_TYPE::CANNON;
		cursorPod_[plNum] = PlayerBase::POD_TYPE::BOUNCE;
		cursorReg_[plNum] = PlayerBase::REG_TYPE::AIRDASH;

		players_[plNum]->ChangeBody(modelPlayerId_[plNum]);
		players_[plNum]->ChangeShot(PlayerBase::SHOT_TYPE::MACHINE);
		players_[plNum]->ChangeBomb(PlayerBase::BOMB_TYPE::CANNON);
		players_[plNum]->ChangePod(PlayerBase::POD_TYPE::BOUNCE);
		players_[plNum]->Init(type_[plNum], keyPl);
		ImageEndPos_[plNum] = { 0.0f,-Application::SCREEN_SIZE_Y / 2,0.0f };

		bodyType_[plNum] = BODY_TYPE::Birb;
	}

	UIBoxH = LoadGraph((Application::PATH_IMAGE + "Box.png").c_str());
	
	for (int i = 0; i < 59; i++)
	{
		arrowH[i] = LoadGraph((Application::PATH_IMAGE + "Yarrow/" + "File" + std::to_string(i+1) + ".png").c_str());
	}

	plEndH_[0] = LoadGraph((Application::PATH_IMAGE + "P1customend.png").c_str());
	plEndH_[1] = LoadGraph((Application::PATH_IMAGE + "P2customend.png").c_str());

	arrowPos_[0] = { 430.0f,62.0f,0.0f };
	arrowPos_[1] = { 430.0f,62.0f,0.0f };

	arrowAnimCnt_ = 0;

	// 16で普通のフォントサイズ
	fontH = CreateFontToHandle(NULL, 32, -1, -1);

	soundBgmH_ = LoadSoundMem((Application::PATH_BGM + "Custom.mp3").c_str());
}

void CustomScene::Update(void)
{
	if (!CheckSoundMem(soundBgmH_))
	{
		PlaySoundMem(soundBgmH_, DX_PLAYTYPE_LOOP, true);
	}

	// Cursor_ステートをいまカーソルがある位置のステートに変える処理を作りたい
	Cursor();
	for (int plNum = 0; plNum < 2; plNum++)
	{
		if (finishFlag_[plNum] == true)
		{
			// このプレイヤーのカスタムが終わってたらスクリーン変えしなくていいよ！
			continue;
		}
		ChangeScreen(plNum);
	}
	if (finishFlag_[0] == true || finishFlag_[1] == true)
	{
		for (int plNum = 0; plNum < 2; plNum++)
		{
			if (finishFlag_[plNum] == true && finishChangeFlag_[plNum] == false)
			{
				// もし、選択が終わってて、選択後の登録が終わってなかったら
				// セレクトで使ったBaseを消して～
				// 新しい選択された体を登録！
				switch (bodyType_[plNum])
				{
				case CustomScene::BODY_TYPE::Birb:
					players_[plNum] = std::make_shared <PlayerBirb>();
					break;
				case CustomScene::BODY_TYPE::Yeti:
					players_[plNum] = std::make_shared <PlayerYeti>();
					break;
				case CustomScene::BODY_TYPE::Cactoro:
					players_[plNum] = std::make_shared <PlayerCactoro>();
					break;
				case CustomScene::BODY_TYPE::Bemon:
					players_[plNum] = std::make_shared <PlayerBemon>();
					break;
				case CustomScene::BODY_TYPE::Ghost:
					players_[plNum] = std::make_shared <PlayerGhost>();
					break;
				}
				players_[plNum]->Init(type_[plNum], keyPl);

			// 体と武器を変更し
			ChangeBody(plNum);
			ChangeWeapon(plNum);
			finishChangeFlag_[plNum] = true;

			}
		}
		if (finishFlag_[0] == true && finishFlag_[1] == true)
		{
			// ゲームシーンへ！
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
	}
}

void CustomScene::Draw(void)
{
	if (arrowAnimCnt_ > 58)
	{
		arrowAnimCnt_ = 0;
	}

	VECTOR SCREENSIZE = { Application::GetInstance().SCREEN_SIZE_X,Application::GetInstance().SCREEN_SIZE_Y,0 };
	for (int plNum = 0; plNum < 2; plNum++)
	{
		int i = 0;

		SetDrawScreen(plScreenH[plNum]);
		ClsDrawScreen();
		DrawExtendGraph(0,0, Application::GetInstance().SCREEN_SIZE_X, Application::GetInstance().SCREEN_SIZE_Y / 2,UIBoxH, true);

		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, color_[plNum], fontH, ("P""%d"),plNum+1);
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, 0xffffff, fontH, "ボディ：%s", body[static_cast<int>(bodyType_[plNum])].c_str());
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, 0xffffff, fontH, " ガン ：%s", gun[static_cast<int>(shotType_[plNum])].c_str());
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5,  0xffffff, fontH," ボム ：%s",bomb[static_cast<int>(bombType_[plNum])].c_str());
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, 0xffffff, fontH, "ポッド：%s", pod[static_cast<int>(podType_[plNum])].c_str());
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, 0xffffff, fontH, "レッグ：%s", reg[static_cast<int>(regType_[plNum])].c_str());
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);
		DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, blank * i + 5, 0xffffff, fontH, "準備完了！");
		i++;

		DrawLine(0, blank * i + 2, Application::SCREEN_SIZE_X, blank * i + 2, 0xff8844);

		if (cursor_[plNum] != SelectState::NORMAL)
		{
			DrawRotaGraph(arrowPos_[plNum].x, arrowPos_[plNum].y,0.13,AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
		}

		switch (select_[plNum])
		{
		case CustomScene::SelectState::NORMAL:
			windowSizeSelect[plNum] = {0.0f,0.0f,0.0f};
			break;
		case CustomScene::SelectState::BODY:
			DrawBodyScreen(plNum);
			break;
		case CustomScene::SelectState::GUN:
			DrawShotScreen(plNum);
			break;
		case CustomScene::SelectState::BOMB:
			DrawBombScreen(plNum);
			break;
		case CustomScene::SelectState::POD:
			DrawPodScreen(plNum);
			break;
		case CustomScene::SelectState::REG:
			DrawRegScreen(plNum);
			break;
		}

		DrawExpoScreen(plNum);

		DrawPreviewScreen(plNum);

		int pattern[4] = { 0, 1, 0, 2 };


		DrawGraph(0, 432 - 33, imageSelectH_[pattern[selectImgCnt_/30%4]], true);

		selectImgCnt_++;

		if (finishFlag_[plNum])
		{
			DrawGraph(ImageEndPos_[plNum].x, ImageEndPos_[plNum].y, plEndH_[plNum], false);
			if (ImageEndPos_[plNum].y < 0)
			{
				ImageEndPos_[plNum].y+= fabsf(ImageEndPos_[plNum].y)/10;
			}
		}

	}

	SetDrawScreen(FullScreenH);
	DrawGraph(0, 0, plScreenH[0], true);
	DrawGraph(0, SCREENSIZE.y/2, plScreenH[1], true);

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph(0, 0, FullScreenH, true);

	arrowAnimCnt_++;
}

void CustomScene::Release(void)
{
	for (int plNum = 0; plNum < 2; plNum++)
	{
		DeleteGraph(bodyScreenH[plNum]);
		DeleteGraph(gunScreenH[plNum]);
		DeleteGraph(bombScreenH[plNum]);
		DeleteGraph(podScreenH[plNum]);
		DeleteGraph(regScreenH[plNum]);
		DeleteGraph(PreviewScreenH[plNum]);
		DeleteGraph(plScreenH[plNum]);
		DeleteGraph(plEndH_[plNum]);

	}
	DeleteGraph(UIBoxH);
	for (int i = 0; i < 59; i++)
	{
		DeleteGraph(arrowH[i]);
	}

	MV1DeleteModel(modelBirbH_);
	MV1DeleteModel(modelYetiH_);
	MV1DeleteModel(modelCactoroH_);
	MV1DeleteModel(modelBemonH_);
	MV1DeleteModel(modelGhostH_);

	DeleteGraph(imageBirbH_);
	DeleteGraph(imageYetiH_);
	DeleteGraph(imageCactoroH_);
	DeleteGraph(imageBemonH_);
	DeleteGraph(imageGhostH_);

	DeleteSoundMem(soundBgmH_);
}

std::weak_ptr<PlayerBase> CustomScene::GetPlayer(int plNum)
{
	return players_[plNum];
}

// 変更を決定した時に、プレイャーの武器を変更する処理
void CustomScene::ChangeWeapon(int plNum)
{
	players_[plNum]->ChangeShot(shotType_[plNum]);
	players_[plNum]->ChangeBomb(bombType_[plNum]);
	players_[plNum]->ChangePod(podType_[plNum]);
	players_[plNum]->ChangeReg(regType_[plNum]);

}

void CustomScene::ChangeBody(int plNum)
{
	switch (bodyType_[plNum])
	{
	case CustomScene::BODY_TYPE::Birb:
		modelPlayerId_[plNum] = modelBirbH_;
		break;
	case CustomScene::BODY_TYPE::Yeti:
		modelPlayerId_[plNum] = modelYetiH_;
		break;
	case CustomScene::BODY_TYPE::Cactoro:
		modelPlayerId_[plNum] = modelCactoroH_;
		break;
	case CustomScene::BODY_TYPE::Bemon:
		modelPlayerId_[plNum] = modelBemonH_;
		break;
	case CustomScene::BODY_TYPE::Ghost:
		modelPlayerId_[plNum] = modelGhostH_;
		break;
	default:
		break;
	}
	players_[plNum]->ChangeBody(modelPlayerId_[plNum]);
}

void CustomScene::ChangeScreen(int player)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(static_cast<InputManager::JOYPAD_NO>(player+1), keyPl.BOMB))
	{
		if (select_[player] == SelectState::NORMAL)
		{
			if (cursor_[player] != SelectState::FINISH)
			{

				select_[player] = cursor_[player];
				cursorOld_[player] = cursor_[player];
 				cursor_[player] = SelectState::NORMAL;
			}
			else
			{
				finishFlag_[player] = true;
			}
		}
		else if (select_[player] != SelectState::NORMAL)
		{
			select_[player] = cursor_[player];
			cursor_[player] = cursorOld_[player];
		}
	}
}



void CustomScene::Cursor(void)
{

	InputManager& ins = InputManager::GetInstance();


	for (int plNum = 0; plNum < 2; plNum++)
	{
		auto playerCtl = ins.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(plNum+1));
		ControllerTilt_[plNum] = playerCtl.AKeyLY;
		if (finishFlag_[plNum] == true)
		{
			continue;
		}

		// カーソル移動,タイプ変更と、カーソルのY位置決め
		switch (select_[plNum])
		{
		case CustomScene::SelectState::NORMAL:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (cursor_[plNum])
				{
				case CustomScene::SelectState::BODY:
					break;
				case CustomScene::SelectState::GUN:
					cursor_[plNum] = SelectState::BODY;
					break;
				case CustomScene::SelectState::BOMB:
					cursor_[plNum] = SelectState::GUN;
					break;
				case CustomScene::SelectState::POD:
					cursor_[plNum] = SelectState::BOMB;
					break;
				case CustomScene::SelectState::REG:
					cursor_[plNum] = SelectState::POD;
					break;
				case CustomScene::SelectState::FINISH:
					cursor_[plNum] = SelectState::REG;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (cursor_[plNum])
				{
				case CustomScene::SelectState::BODY:
					cursor_[plNum] = SelectState::GUN;
					break;
				case CustomScene::SelectState::GUN:
					cursor_[plNum] = SelectState::BOMB;
					break;
				case CustomScene::SelectState::BOMB:
					cursor_[plNum] = SelectState::POD;
					break;
				case CustomScene::SelectState::POD:
					cursor_[plNum] = SelectState::REG;
					break;
				case CustomScene::SelectState::REG:
					cursor_[plNum] = SelectState::FINISH;
					break;
				case CustomScene::SelectState::FINISH:
					break;
				}
			}
			switch (cursor_[plNum])
			{
			case CustomScene::SelectState::BODY:
				arrowPos_[plNum].y = 62.0f;
				break;
			case CustomScene::SelectState::GUN:
				arrowPos_[plNum].y = 102.0f;
				break;
			case CustomScene::SelectState::BOMB:
				arrowPos_[plNum].y = 142.0f;
				break;
			case CustomScene::SelectState::POD:
				arrowPos_[plNum].y = 182.0f;
				break;
			case CustomScene::SelectState::REG:
				arrowPos_[plNum].y = 222.0f;
				break;
			case CustomScene::SelectState::FINISH:
				arrowPos_[plNum].y = 262.0f;
				break;
			}
			break;
		case CustomScene::SelectState::BODY:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (bodyType_[plNum])
				{
				case BODY_TYPE::Birb:
					break;
				case BODY_TYPE::Yeti:
					bodyType_[plNum] = BODY_TYPE::Birb;
					break;
				case BODY_TYPE::Cactoro:
					bodyType_[plNum] = BODY_TYPE::Yeti;
					break;
				case BODY_TYPE::Bemon:
					bodyType_[plNum] = BODY_TYPE::Cactoro;
					break;
				case BODY_TYPE::Ghost:
					bodyType_[plNum] = BODY_TYPE::Bemon;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (bodyType_[plNum])
				{
				case BODY_TYPE::Birb:
					bodyType_[plNum] = BODY_TYPE::Yeti;
					break;
				case BODY_TYPE::Yeti:
					bodyType_[plNum] = BODY_TYPE::Cactoro;
					break;
				case BODY_TYPE::Cactoro:
					bodyType_[plNum] = BODY_TYPE::Bemon;
					break;
				case BODY_TYPE::Bemon:
					bodyType_[plNum] = BODY_TYPE::Ghost;
					break;
				case BODY_TYPE::Ghost:
					break;
				}
			}
			switch (bodyType_[plNum])
			{
			case BODY_TYPE::Birb:
				arrowPos_[plNum].y = 20.0;
				break;
			case BODY_TYPE::Yeti:
				arrowPos_[plNum].y = 60.0;
				break;	
			case BODY_TYPE::Cactoro:
				arrowPos_[plNum].y = 100.0;
				break;
			case BODY_TYPE::Bemon:
				arrowPos_[plNum].y = 140.0;
				break;
			case BODY_TYPE::Ghost:
				arrowPos_[plNum].y = 180.0;
				break;
			}
			ChangeBody(plNum);
			break;
		case CustomScene::SelectState::GUN:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (shotType_[plNum])
				{
				case PlayerBase::SHOT_TYPE::MACHINE:
					break;
				case PlayerBase::SHOT_TYPE::ELECSHOCK:
					shotType_[plNum] = PlayerBase::SHOT_TYPE::MACHINE;
					break;
				case PlayerBase::SHOT_TYPE::SNIPER:
					shotType_[plNum] = PlayerBase::SHOT_TYPE::ELECSHOCK;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (shotType_[plNum])
				{
				case PlayerBase::SHOT_TYPE::MACHINE:
					shotType_[plNum] = PlayerBase::SHOT_TYPE::ELECSHOCK;
					break;
				case PlayerBase::SHOT_TYPE::ELECSHOCK:
					shotType_[plNum] = PlayerBase::SHOT_TYPE::SNIPER;
					break;
				case PlayerBase::SHOT_TYPE::SNIPER:
					break;
				}
			}
			switch (shotType_[plNum])
			{
			case PlayerBase::SHOT_TYPE::MACHINE:
				arrowPos_[plNum].y = 21.0;
				break;
			case PlayerBase::SHOT_TYPE::ELECSHOCK:
				arrowPos_[plNum].y = 62.0;
				break;
			case PlayerBase::SHOT_TYPE::SNIPER:
				arrowPos_[plNum].y = 103.0;
				break;
			}
			break;
		case CustomScene::SelectState::BOMB:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (bombType_[plNum])
				{
				case PlayerBase::BOMB_TYPE::CANNON:
					break;
				case PlayerBase::BOMB_TYPE::MINE:
					bombType_[plNum] = PlayerBase::BOMB_TYPE::CANNON;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (bombType_[plNum])
				{
				case PlayerBase::BOMB_TYPE::CANNON:
					bombType_[plNum] = PlayerBase::BOMB_TYPE::MINE;
					break;
				case PlayerBase::BOMB_TYPE::MINE:
					break;
				}
			}
			switch (bombType_[plNum])
			{
			case PlayerBase::BOMB_TYPE::CANNON:
				arrowPos_[plNum].y =21.0;
				break;
			case PlayerBase::BOMB_TYPE::MINE:
				arrowPos_[plNum].y = 62.0;
				break;
			}
			break;
		case CustomScene::SelectState::POD:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (podType_[plNum])
				{
				case PlayerBase::POD_TYPE::BOUNCE:
					break;
				case PlayerBase::POD_TYPE::FREEZE:
					podType_[plNum] = PlayerBase::POD_TYPE::BOUNCE;
					break;
				case PlayerBase::POD_TYPE::STICKY:
					podType_[plNum] = PlayerBase::POD_TYPE::FREEZE;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (podType_[plNum])
				{
				case PlayerBase::POD_TYPE::BOUNCE:
					podType_[plNum] = PlayerBase::POD_TYPE::FREEZE;
					break;
				case PlayerBase::POD_TYPE::FREEZE:
					podType_[plNum] = PlayerBase::POD_TYPE::STICKY;
					break;
				case PlayerBase::POD_TYPE::STICKY:
					break;
				}
			}
			switch (podType_[plNum])
			{
			case PlayerBase::POD_TYPE::BOUNCE:
				arrowPos_[plNum].y = 21.0;
				break;
			case PlayerBase::POD_TYPE::FREEZE:
				arrowPos_[plNum].y = 62.0;
				break;
			case PlayerBase::POD_TYPE::STICKY:
				arrowPos_[plNum].y = 103.0;
				break;
			}
			break;
		case CustomScene::SelectState::REG:
			if (ControllerTilt_[plNum] <= -4 && ControllerTiltOld_[plNum] > -4)
			{
				switch (regType_[plNum])
				{
				case PlayerBase::REG_TYPE::AIRDASH:
					break;
				case PlayerBase::REG_TYPE::HOVER:
					regType_[plNum] = PlayerBase::REG_TYPE::AIRDASH;
					break;
				}
			}
			if (ControllerTilt_[plNum] >= 4 && ControllerTiltOld_[plNum] < 4)
			{
				switch (regType_[plNum])
				{
				case PlayerBase::REG_TYPE::AIRDASH:
					regType_[plNum] = PlayerBase::REG_TYPE::HOVER;
					break;
				case PlayerBase::REG_TYPE::HOVER:
					break;
				}
			}
			switch (regType_[plNum])
			{
			case PlayerBase::REG_TYPE::AIRDASH:
				arrowPos_[plNum].y = 21.0;
				break;
			case PlayerBase::REG_TYPE::HOVER:
				arrowPos_[plNum].y = 62.0;
				break;
			}
			break;
		case CustomScene::SelectState::FINISH:
			break;
		}
		// カーソルのX位置決め
		if (select_[plNum] == SelectState::NORMAL || select_[plNum] == SelectState::FINISH)
		{
			arrowPos_[plNum].x = 430.0f;
		}
		else
		{
			arrowPos_[plNum].x = 410.0f;

		}
		ControllerTiltOld_[plNum] = ControllerTilt_[plNum];
	}
}

// 各種ウィンドウのDraw(関数がそれぞれ最後にでっかいキャンパスに自分を描画してる)
void CustomScene::DrawBodyScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(bodyScreenH[player]);
	ClsDrawScreen();

	int bodysize = body.size();

	DrawExtendGraph(0, 0, windowMaxSizeSelect.x, (body.size() + 2) * blank, UIBoxH, true);

	DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, 5, 0xffffff,fontH, "ボディ：");
	for (int i = 0; i < bodysize; i++)
	{
		DrawFormatStringToHandle(140+8, blank * (i)+5, 0xffffff,fontH, "%s", body[i].c_str());

		DrawLine(0, blank * (i + 1) + 2, Application::SCREEN_SIZE_X, blank * (i + 1) + 2, 0xff8844);
	}
	DrawRotaGraph(arrowPos_[player].x, arrowPos_[player].y, 0.13, AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
	SetDrawScreen(screenH);
	WindowBeBig(player, (bodysize+2) * (blank));
	DrawExtendGraph(8, 2, windowSizeSelect[player].x + 8, windowSizeSelect[player].y + 2, bodyScreenH[player], true);
}

void CustomScene::DrawShotScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(gunScreenH[player]);
	ClsDrawScreen();

	int gunsize = gun.size();

	DrawExtendGraph(0, 0, windowMaxSizeSelect.x, (gun.size() + 2) * blank, UIBoxH, true);

	DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, 5, 0xffffff, fontH, " ガン ：");
	for (int i = 0; i < gunsize; i++)
	{
		DrawFormatStringToHandle(140 + 8, blank * (i)+5, 0xffffff, fontH, "%s", gun[i].c_str());
		DrawLine(0, blank * (i + 1) + 2, Application::SCREEN_SIZE_X, blank * (i + 1) + 2, 0xff8844);
	}
	DrawRotaGraph(arrowPos_[player].x, arrowPos_[player].y, 0.13, AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
	SetDrawScreen(screenH);
	WindowBeBig(player, (gunsize + 2) * (blank));
	DrawExtendGraph(8, 2, windowSizeSelect[player].x + 8, windowSizeSelect[player].y + 2, gunScreenH[player], true);
}

void CustomScene::DrawBombScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(bombScreenH[player]);
	ClsDrawScreen();

	int bombsize = bomb.size();

	DrawExtendGraph(0, 0, windowMaxSizeSelect.x, (bomb.size() + 2) * blank, UIBoxH, true);

	DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, 5, 0xffffff, fontH, " ボム ：");
	for (int i = 0; i < bombsize; i++)
	{
		DrawFormatStringToHandle(140 + 8, blank * (i)+5, 0xffffff, fontH, "%s", bomb[i].c_str());
		DrawLine(0, blank * (i + 1) + 2, Application::SCREEN_SIZE_X, blank * (i + 1) + 2, 0xff8844);
	}
	DrawRotaGraph(arrowPos_[player].x, arrowPos_[player].y, 0.13, AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
	SetDrawScreen(screenH);
	WindowBeBig(player, (bombsize + 2) * (blank));
	DrawExtendGraph(8, 2, windowSizeSelect[player].x + 8, windowSizeSelect[player].y + 2, bombScreenH[player], true);
}

void CustomScene::DrawPodScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(podScreenH[player]);
	ClsDrawScreen();

	int podsize = pod.size();

	DrawExtendGraph(0, 0, windowMaxSizeSelect.x, (pod.size() + 2) * blank, UIBoxH, true);

	DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, 5, 0xffffff, fontH, "ポッド：");
	for (int i = 0; i < podsize; i++)
	{
		DrawFormatStringToHandle(140 + 8, blank * (i)+5, 0xffffff, fontH, "%s", pod[i].c_str());
		DrawLine(0, blank * (i + 1) + 2, Application::SCREEN_SIZE_X, blank * (i + 1) + 2, 0xff8844);
	}
	DrawRotaGraph(arrowPos_[player].x, arrowPos_[player].y, 0.13, AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
	SetDrawScreen(screenH);
	WindowBeBig(player, (podsize + 2) * (blank));
	DrawExtendGraph(8, 2, windowSizeSelect[player].x + 8, windowSizeSelect[player].y + 2, podScreenH[player], true);
}

void CustomScene::DrawRegScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(regScreenH[player]);
	ClsDrawScreen();

	int regsize = reg.size();

	DrawExtendGraph(0, 0, windowMaxSizeSelect.x, (reg.size() + 2) * blank, UIBoxH, true);

	DrawFormatStringToHandle(Application::SCREEN_SIZE_X / 128.0f, 5, 0xffffff, fontH, "レッグ：");
	for (int i = 0; i < regsize; i++)
	{
		DrawFormatStringToHandle(140 + 8, blank * (i)+5, 0xffffff, fontH, "%s", reg[i].c_str());
		DrawLine(0, blank * (i + 1) + 2, Application::SCREEN_SIZE_X, blank * (i + 1) + 2, 0xff8844);
	}
	DrawRotaGraph(arrowPos_[player].x, arrowPos_[player].y, 0.13, AsoUtility::Deg2RadD(90.0), arrowH[arrowAnimCnt_], true);
	SetDrawScreen(screenH);
	WindowBeBig(player,(regsize + 2) * (blank));
	DrawExtendGraph(8, 2, windowSizeSelect[player].x + 8, windowSizeSelect[player].y + 2, regScreenH[player], true);
}

void CustomScene::DrawExpoScreen(int player)
{
	int screenH;
	screenH = plScreenH[player];
	SetDrawScreen(expoScreenH[player]);
	ClsDrawScreen();
	DrawExtendGraph(0, 0, 600, 428, UIBoxH, true);

	switch (select_[player])
	{
	case SelectState::NORMAL:
		switch (cursor_[player])
		{
		case SelectState::BODY:
			switch (bodyType_[player])
			{
			case BODY_TYPE::Birb:
				DrawGraph(0, 0, imageBirbH_, true);
				break;
			case BODY_TYPE::Yeti:
				DrawGraph(0, 0, imageYetiH_, true);
				break;
			case BODY_TYPE::Cactoro:
				DrawGraph(0, 0, imageCactoroH_, true);
				break;
			case BODY_TYPE::Bemon:
				DrawGraph(0, 0, imageBemonH_, true);
				break;
			case BODY_TYPE::Ghost:
				DrawGraph(0, 0, imageGhostH_, true);
				break;
			default:
				break;
			}
			break;
		case SelectState::GUN:
			switch (shotType_[player])
			{
			case PlayerBase::SHOT_TYPE::MACHINE:
				DrawGraph(0, 0, imageMachineH_, true);
				break;
			case PlayerBase::SHOT_TYPE::ELECSHOCK:
				DrawGraph(0, 0, imagePunchH_, true);
				break;
			case PlayerBase::SHOT_TYPE::SNIPER:
				DrawGraph(0, 0, imageSniperH_, true);
				break;
			case PlayerBase::SHOT_TYPE::MAX:
				break;
			}
			break;
		case SelectState::BOMB:
			switch (bombType_[player])
			{
			case PlayerBase::BOMB_TYPE::CANNON:
				DrawGraph(0, 0, imageCannonH_, true);
				break;
			case PlayerBase::BOMB_TYPE::MINE:
				DrawGraph(0, 0, imageDelayH_, true);
				break;
			case PlayerBase::BOMB_TYPE::MAX:
				break;
			}
			break;
		case SelectState::POD:
			switch (podType_[player])
			{
			case PlayerBase::POD_TYPE::BOUNCE:
				DrawGraph(0, 0, imageBounceH_, true);
				break;
			case PlayerBase::POD_TYPE::FREEZE:
				DrawGraph(0, 0, imageAirH_, true);
				break;
			case PlayerBase::POD_TYPE::STICKY:
				DrawGraph(0, 0, imageStickyH_, true);
				break;
			case PlayerBase::POD_TYPE::MAX:
				break;
			}
			break;
		case SelectState::REG:
			switch (regType_[player])
			{
			case PlayerBase::REG_TYPE::AIRDASH:
				DrawGraph(0, 0, imageAirdashH_, true);
				break;
			case PlayerBase::REG_TYPE::HOVER:
				DrawGraph(0, 0, imageHoverH_, true);
				break;
			case PlayerBase::REG_TYPE::MAX:
				break;
			}
			break;
		case SelectState::FINISH:
			DrawGraph(0, 0, imageReadyH_, true);
			break;
		default:
			break;
		}
		break;
	case SelectState::BODY:
		switch (bodyType_[player])
		{
		case BODY_TYPE::Birb:
			DrawGraph(0, 0, imageBirbH_, true);
			break;
		case BODY_TYPE::Yeti:
			DrawGraph(0, 0, imageYetiH_, true);
			break;
		case BODY_TYPE::Cactoro:
			DrawGraph(0, 0, imageCactoroH_, true);
			break;
		case BODY_TYPE::Bemon:
			DrawGraph(0, 0, imageBemonH_, true);
			break;
		case BODY_TYPE::Ghost:
			DrawGraph(0, 0, imageGhostH_, true);
			break;
		default:
			break;
		}
		break;
	case SelectState::GUN:
		switch (shotType_[player])
		{
		case PlayerBase::SHOT_TYPE::MACHINE:
			DrawGraph(0, 0, imageMachineH_, true);
			break;
		case PlayerBase::SHOT_TYPE::ELECSHOCK:
			DrawGraph(0, 0, imagePunchH_, true);
			break;
		case PlayerBase::SHOT_TYPE::SNIPER:
			DrawGraph(0, 0, imageSniperH_, true);
			break;
		case PlayerBase::SHOT_TYPE::MAX:
			break;
		}
		break;
	case SelectState::BOMB:
		switch (bombType_[player])
		{
		case PlayerBase::BOMB_TYPE::CANNON:
			DrawGraph(0, 0, imageCannonH_, true);
			break;
		case PlayerBase::BOMB_TYPE::MINE:
			DrawGraph(0, 0, imageDelayH_, true);
			break;
		case PlayerBase::BOMB_TYPE::MAX:
			break;
		}
		break;
	case SelectState::POD:
		switch (podType_[player])
		{
		case PlayerBase::POD_TYPE::BOUNCE:
			DrawGraph(0, 0, imageBounceH_, true);
			break;
		case PlayerBase::POD_TYPE::FREEZE:
			DrawGraph(0, 0, imageAirH_, true);
			break;
		case PlayerBase::POD_TYPE::STICKY:
			DrawGraph(0, 0, imageStickyH_, true);
			break;
		case PlayerBase::POD_TYPE::MAX:
			break;
		}
		break;
	case SelectState::REG:
		switch (regType_[player])
		{
		case PlayerBase::REG_TYPE::AIRDASH:
			DrawGraph(0, 0, imageAirdashH_, true);
			break;
		case PlayerBase::REG_TYPE::HOVER:
			DrawGraph(0, 0, imageHoverH_, true);
			break;
		case PlayerBase::REG_TYPE::MAX:
			break;
		}
		break;
	case SelectState::FINISH:
		DrawGraph(0, 0, imageReadyH_, true);
	default:
		break;
	}


	SetDrawScreen(screenH);
	DrawGraph(500, 3, expoScreenH[player], false);

}

void CustomScene::DrawPreviewScreen(int player)
{
	SetDrawScreen(PreviewScreenH[player]);
	// カメラをフリーモードにする
	// カメラ設定
	SceneManager::GetInstance().Init3D();
	SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();
	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::FIXED_POINT);

	ClsDrawScreen();
	DrawExtendGraph(0, 0, 428, 428, UIBoxH, true);
	players_[player]->SetPos({ 0.0f,0.0f,0.0f });
	players_[player]->Animation();
	players_[player]->Draw();
	SetDrawScreen(plScreenH[player]);
	DrawGraph(Application::SCREEN_SIZE_X - 412 - 26, 1, PreviewScreenH[player], true);

}

void CustomScene::WindowBeBig(int player,int maxSizeY)
{
	float div = 15.0f;

		if (windowSizeSelect[player].x + windowMaxSizeSelect.x / div < windowMaxSizeSelect.x)
		{
			windowSizeSelect[player].x += windowMaxSizeSelect.x / div;
		}
		else
		{
			windowSizeSelect[player].x = windowMaxSizeSelect.x;
		}
		if (windowSizeSelect[player].y + maxSizeY / div < maxSizeY)
		{
			windowSizeSelect[player].y += maxSizeY / div;
		}
		else
		{
			windowSizeSelect[player].y = maxSizeY;
		}
}
