#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Object/Stage.h"
#include "../Object/Weapon/WeaponBase.h"
#include "../Object/PlayerBase.h"
#include "GameScene.h"

GameScene::GameScene(void):resMng_(ResourceManager::GetInstance())
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = std::make_shared<Stage>();
	stage_->Init();
	
	//  カメラをフリーモードにする
	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::AUTO);
	SceneManager::GetInstance().GetCamera().lock()->SetHAngle(0.0f);
	//  プレイヤーのモデル
	modelPlayerId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_BIRB);
	modelPlayerId2_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_YETI);
	//  1Playerの初期化
	PlayerBase::KEY_CONFIG keyPl = {
		InputManager::JOYPAD_BTN::LEFT,
		InputManager::JOYPAD_BTN::DOWN,
		InputManager::JOYPAD_BTN::R,
		InputManager::JOYPAD_BTN::L,
		InputManager::JOYPAD_BTN::ZR,
		InputManager::JOYPAD_BTN::ZL,
	};
	//  CustomSceneのシェアードポインタを使ってるから、新しくmakeしない
	players_[0]->Init(PlayerBase::TYPE::PLAYER_1, keyPl);
	players_[1]->Init(PlayerBase::TYPE::PLAYER_2, keyPl);
	for (int i = 0; i < 2; i++)
	{
		players_[i]->SetModelStageId(stage_->GetModelId());
		players_[i]->SetModelCoverId(stage_->GetCoverModelId());
	}

	//  ゲームオーバー判定
	//  配列にするか悩んだけど、P1P2分けにした方が読みやすいと思った
	p2win_ = false;
	p1win_ = false;

	//  ゲームオーバー画像
	
	imgP1Win_ = resMng_.Load(ResourceManager::SRC::IMG_1P_WIN).handleId_;
	imgP2Win_ = resMng_.Load(ResourceManager::SRC::IMG_2P_WIN).handleId_;

	shadowH = MakeShadowMap(2048, 2048);
	SetShadowMapLightDirection(shadowH, VGet(0.0f, -1.0f, 0.0f));
	SetShadowMapDrawArea(shadowH, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

	for (int plNum = 0; plNum < 2; plNum++)
	{
		HpWindowH_[plNum] = MakeScreen(500, 163, true);


		int hp = players_[plNum]->GetHp();
		hpHundred_[plNum] = hp / 100;
		hp -= hp * hpHundred_[plNum];
		hpTens_[plNum] = hp / 10;
		hp -= hp * hpTens_[plNum];
		hpOnes_[plNum] = hp;

	}

	NumImageH_[0][0] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM0).handleId_;
	NumImageH_[0][1] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM1).handleId_;
	NumImageH_[0][2] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM2).handleId_;
	NumImageH_[0][3] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM3).handleId_;
	NumImageH_[0][4] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM4).handleId_;
	NumImageH_[0][5] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM5).handleId_;
	NumImageH_[0][6] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM6).handleId_;
	NumImageH_[0][7] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM7).handleId_;
	NumImageH_[0][8] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM8).handleId_;
	NumImageH_[0][9] = resMng_.Load(ResourceManager::SRC::IMG_1P_NUM9).handleId_;

	NumImageH_[1][0] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM0).handleId_;
	NumImageH_[1][1] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM1).handleId_;
	NumImageH_[1][2] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM2).handleId_;
	NumImageH_[1][3] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM3).handleId_;
	NumImageH_[1][4] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM4).handleId_;
	NumImageH_[1][5] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM5).handleId_;
	NumImageH_[1][6] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM6).handleId_;
	NumImageH_[1][7] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM7).handleId_;
	NumImageH_[1][8] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM8).handleId_;
	NumImageH_[1][9] = resMng_.Load(ResourceManager::SRC::IMG_2P_NUM9).handleId_;

	HpBarImageH_[0] = resMng_.Load(ResourceManager::SRC::IMG_1P_HPBAR).handleId_;
	HpBarImageH_[1] = resMng_.Load(ResourceManager::SRC::IMG_2P_HPBAR).handleId_;
	HpScaleImageH_ = resMng_.Load(ResourceManager::SRC::IMG_HPSCALE).handleId_;
	HpBarBlackImageH_ = resMng_.Load(ResourceManager::SRC::IMG_HPBLACK).handleId_;

	soundBgmH_ = LoadSoundMem((Application::PATH_BGM + "Battle.mp3").c_str());
	soundVicH_ = LoadSoundMem((Application::PATH_BGM + "Victory.mp3").c_str());

	gameNumImgH_[0] = resMng_.Load(ResourceManager::SRC::IMG_COUNTDOWN_NUM1).handleId_;
	gameNumImgH_[1] = resMng_.Load(ResourceManager::SRC::IMG_COUNTDOWN_NUM2).handleId_;
	gameNumImgH_[2] = resMng_.Load(ResourceManager::SRC::IMG_COUNTDOWN_NUM3).handleId_;
	gameNumImgH_[3] = resMng_.Load(ResourceManager::SRC::IMG_COUNTDOWN_NUM4).handleId_;
	gameNumImgH_[4] = resMng_.Load(ResourceManager::SRC::IMG_COUNTDOWN_NUM5).handleId_;

	GameCountFlame_ = 240;
	GameCount_ = 0;
	startH_ = resMng_.Load(ResourceManager::SRC::IMG_GAMESTART).handleId_;

	initFlag_ = false;

	Update();
}

void GameScene::Update(void)
{

	if (GameCountFlame_ > 0 && initFlag_ == true)
	{
		SceneManager::GetInstance().GetCamera().lock()->SetHAngle(0.0f);
		GameCountFlame_--;
		GameCount_ = GameCountFlame_/40;
		return;
	}


	if (p2win_ == true || p1win_ == true)
	{
		GameSet();
		//  ゲームオーバーになってたらここからは処理しない
		return;
	}

	if (!CheckSoundMem(soundBgmH_))
	{
		PlaySoundMem(soundBgmH_, DX_PLAYTYPE_LOOP, true);
	}

	stage_->Update();

	for (int i = 0; i < 2; i++)
	{
		//  i番目のプレイヤーが生きていたら
		if (players_[i]->IsAlive() == true)
		{
			players_[i]->Update();
			switch (i)
			{
			case 0:
				pl1Pos_ = players_[i]->GetPos();
				players_[i]->SetEnemyPos(players_[i + 1]->GetPos());
				break;
			case 1:
				pl2Pos_ = players_[i]->GetPos();
				players_[i]->SetEnemyPos(players_[i - 1]->GetPos());
				break;
			default:
				break;
			}
		}
	}

	SceneManager::GetInstance().GetCamera().lock()->SetTargetPos(pl1Pos_, pl2Pos_);

	//  ステージモデルID
	int modelStageId = stage_->GetModelId();

	for (int p = 0; p < 2; p++)	//  p = プレイヤー番号
	{
		switch (p)
		{
		case 0:
			//  自分が無敵で相手が無敵じゃなかったら当たり判定に入る
			if ((players_[p]->GetInvincible() && !players_[p+1]->GetInvincible()) && !players_[p]->GetAlreadyAttack() && !(players_[p + 1]->GetRecovery()))
			{
				VECTOR pPos = players_[p]->GetPos();
				VECTOR pPosUp = VAdd(pPos, { 0.0f,70.0f,0.0f });
				VECTOR pPosDown = VAdd(pPos, { 0.0f,25.0f,0.0f });

				VECTOR ePos = players_[p + 1]->GetPos();
				VECTOR ePosUp = VAdd(ePos, { 0.0f,70.0f,0.0f });
				VECTOR ePosDown = VAdd(ePos, { 0.0f,25.0f,0.0f });

				float COLRADIUS = 25.0f;
				if (HitCheck_Capsule_Capsule(pPosUp, pPosDown, COLRADIUS, ePosUp, ePosDown, COLRADIUS))
				{
					players_[p + 1]->Damage(players_[p]->GetAttackDamage(), players_[p]->GetAttackDamage(), {1.0f,1.0f,1.0f}, PlayerBase::ATTACK_TYPE::BOMB);
					players_[p]->SetAlreadyAttack(true);
				}
			}
			break;
		case 1:
			//  同上
			if ((players_[p]->GetInvincible() && !players_[p-1]->GetInvincible()) && !players_[p]->GetAlreadyAttack() && !(players_[p-1]->GetRecovery()))
			{
				VECTOR pPos = players_[p]->GetPos();
				VECTOR pPosUp = VAdd(pPos, { 0.0f,70.0f,0.0f });
				VECTOR pPosDown = VAdd(pPos, { 0.0f,25.0f,0.0f });

				VECTOR ePos = players_[p - 1]->GetPos();
				VECTOR ePosUp = VAdd(ePos, { 0.0f,70.0f,0.0f });
				VECTOR ePosDown = VAdd(ePos, { 0.0f,25.0f,0.0f });

				float COLRADIUS = 25.0f;
				if (HitCheck_Capsule_Capsule(pPosUp, pPosDown, COLRADIUS, ePosUp, ePosDown, COLRADIUS))
				{
					players_[p - 1]->Damage(players_[p]->GetAttackDamage(), players_[p]->GetAttackDamage(), { 1.0f,1.0f,1.0f }, PlayerBase::ATTACK_TYPE::BOMB);
					players_[p]->SetAlreadyAttack(true);
				}
			}
			break;
		default:
			break;
		}
	}

	for (int p = 0; p < 2; p++)	//  p = プレイヤー番号
	{

		auto shots = players_[p]->GetShots();
		for (auto shot : shots)
		{
			shot->Update();

			if (shot->IsShot() == false)
			{
				//  爆発中や処理終了後は、以降の処理を実行しない
				continue;
			}

			//  ステージモデルとの衝突判定
			for (int i = 0; i <= 500; i++)
			{
				VECTOR tmpPos = shot->GetPos();
				//  1フレームに移動したい距離の1/100移動させる
				VECTOR movepow = shot->GetMovePow();
				tmpPos = VAdd(tmpPos, VScale(VScale(movepow, 0.002), i));
				auto info = MV1CollCheck_Sphere(modelStageId, -1, tmpPos, shot->GetRadius());
				if (info.HitNum > 0)
				{
					shot->SetPos(VAdd(shot->GetPos(), VScale(movepow, 0.002)));
					if (players_[p]->GetShotType() != PlayerBase::SHOT_TYPE::ELECSHOCK)
					{
						shot->Blast();
						break;
					}
				}
				else
				{
					shot->SetPos(VAdd(shot->GetPos(), VScale(movepow, 0.002)));
				}
				//  当たり判定結果ポリゴン配列の後始末をする
				MV1CollResultPolyDimTerminate(info);

				switch (p)
				{
				case 0:
					//  i番目の人が生きていたら
					if (players_[p + 1]->IsAlive() == true)
					{
						//  モデルとの衝突判定（円と円）
						if (AsoUtility::IsHitSpheres(shot->GetPos(), shot->GetRadius(), players_[p + 1]->GetColPos(), players_[p + 1]->GetRadius()) && shot->GetState()!=WeaponBase::STATE::BLAST)
						{
							shot->Blast();
							if (!(players_[p + 1]->GetInvincible()) && !(players_[p + 1]->GetRecovery()))
							{
								players_[p + 1]->Damage(shot->GetHpDamage(), shot->GetStunDamage(), shot->GetDir(), PlayerBase::ATTACK_TYPE::SHOT);
							}
						}
					}
					break;
				case 1:
					//  i番目の人が生きていたら
					if (players_[p - 1]->IsAlive() == true)
					{
						//  モデルとの衝突判定（円と円）
						if (AsoUtility::IsHitSpheres(shot->GetPos(), shot->GetRadius(), players_[p - 1]->GetColPos(), players_[p - 1]->GetRadius()) && shot->GetState() != WeaponBase::STATE::BLAST)
						{
							shot->Blast();
							if (!(players_[p - 1]->GetInvincible()) && !(players_[p - 1]->GetRecovery()))
							{
								players_[p - 1]->Damage(shot->GetHpDamage(), shot->GetStunDamage(), shot->GetDir(), PlayerBase::ATTACK_TYPE::SHOT);
							}
						}
					}
					break;
				default:
					break;
				}

			}


		}
		auto bombs = players_[p]->GetBombs();
		for (auto bomb : bombs)
		{
			bomb->Update();

			if (bomb->IsShot() == false)
			{
				//  爆発中や処理終了後は、以降の処理を実行しない
				continue;
			}

			//  ステージモデルとの衝突判定
			auto info = MV1CollCheck_Sphere(modelStageId, -1, bomb->GetPos(), bomb->GetRadius());
			if (info.HitNum > 0)
			{
				bomb->Blast();
			}
			//  当たり判定結果ポリゴン配列の後始末をする
			MV1CollResultPolyDimTerminate(info);


			switch (p)
			{
			case 0:
				//  i番目の人が生きていたら
				if (players_[p + 1]->IsAlive() == true)
				{
					//  モデルとの衝突判定（円と円）
					if (AsoUtility::IsHitSpheres(bomb->GetPos(), bomb->GetRadius(), players_[p + 1]->GetColPos(), players_[p + 1]->GetRadius()))
					{
						bomb->Blast();
						if (!(players_[p + 1]->GetInvincible()) && !(players_[p + 1]->GetRecovery()))
						{
							players_[p + 1]->Damage(bomb->GetHpDamage(), bomb->GetHpDamage(), bomb->GetDir(), PlayerBase::ATTACK_TYPE::BOMB);
						}
					}
				}
				break;
			case 1:
				//  i番目の人が生きていたら
				if (players_[p - 1]->IsAlive() == true)
				{
					//  モデルとの衝突判定（円と円）
					if (AsoUtility::IsHitSpheres(bomb->GetPos(), bomb->GetRadius(), players_[p - 1]->GetColPos(), players_[p - 1]->GetRadius()))
					{
						bomb->Blast();
						if (!(players_[p - 1]->GetInvincible()) && !(players_[p - 1]->GetRecovery()))
						{
							players_[p - 1]->Damage(bomb->GetHpDamage(), bomb->GetHpDamage(), bomb->GetDir(), PlayerBase::ATTACK_TYPE::BOMB);
						}
					}
				}
				break;
			default:
				break;
			}

		}

		auto pods = players_[p]->GetPods();
		for (auto pod : pods)
		{
			pod->Update();

			if (pod->IsShot() == false)
			{
				//  爆発中や処理終了後は、以降の処理を実行しない
				continue;
			}




			//  ステージモデルとの衝突判定
			auto info = MV1CollCheck_Sphere(modelStageId, -1, pod->GetPos(), pod->GetRadius());

			if (info.HitNum > 0)
			{
				int HitNum = info.HitNum;
				for (int i = 0; i < HitNum; i++)
				{

					auto hitDim = info.Dim[i];
					VECTOR hitPoliPos0 = hitDim.Position[0];
					VECTOR hitPoliPos1 = hitDim.Position[1];
					VECTOR hitPoliPos2 = hitDim.Position[2];

					//  当たっていたら、当たらなくなるまで法線ベクトル方向に100回戻す
					for (int a = 0; a < 100; a++)
					{
						//  このループ内での当たり判定Pos
						VECTOR tmpSpherePos = pod->GetPos();
						float sphereRadius = 8.0f;
						//  当たっていたら位置を少し戻す
						if (HitCheck_Sphere_Triangle(tmpSpherePos, sphereRadius, hitPoliPos0, hitPoliPos1, hitPoliPos2))
						{
							pod->SetPos(VAdd(tmpSpherePos, VScale(hitDim.Normal, 15.0f)));
						}
						//  当たっていなかったら処理を終了する
						else
						{
							break;
						}
					}

				}


				VECTOR normal = info.Dim->Normal;
				pod->SetNormal(normal);
				pod->Blast();


			}
			//  当たり判定結果ポリゴン配列の後始末をする
			MV1CollResultPolyDimTerminate(info);

			switch (p)
			{
			case 0:
				//  i番目の人が生きていたら
				if (players_[p + 1]->IsAlive() == true)
				{
					//  モデルとの衝突判定（円と円）
					if (AsoUtility::IsHitSpheres(pod->GetPos(), pod->GetRadius(), players_[p + 1]->GetColPos(), players_[p + 1]->GetRadius()))
					{
						pod->PlayerHit(true);
						pod->Blast();
						if (!(players_[p + 1]->GetInvincible()) && !(players_[p + 1]->GetRecovery()))
						{
							players_[p + 1]->Damage(pod->GetHpDamage(), pod->GetHpDamage(), pod->GetDir(), PlayerBase::ATTACK_TYPE::POD);
						}
					}
				}
				break;
			case 1:
				//  i番目の人が生きていたら
				if (players_[p - 1]->IsAlive() == true)
				{
					//  モデルとの衝突判定（円と円）
					if (AsoUtility::IsHitSpheres(pod->GetPos(), pod->GetRadius(), players_[p - 1]->GetColPos(), players_[p - 1]->GetRadius()))
					{
						pod->PlayerHit(true);
						pod->Blast();
						if (!(players_[p - 1]->GetInvincible()) && !(players_[p - 1]->GetRecovery()))
						{
							players_[p - 1]->Damage(pod->GetHpDamage(), pod->GetHpDamage(), pod->GetDir(), PlayerBase::ATTACK_TYPE::POD);
						}
					}
				}
				break;
			default:
				break;
			}

		}

	}

	for (int plNum = 0; plNum < 2; plNum++)
	{
		if (players_[plNum]->GetHp() <= 0)
		{
			players_[plNum]->SetAlive(false);
		}
	}

	//  ゲームオーバー判定
	for (int i = 0; i < 2; i++)
	{
		if (players_[i]->IsAlive() == false)
		{
			switch (i)
			{
			case 0:
				p2win_ = true;
				break;
			case 1:
				p1win_ = true;
				break;
			}
		}
	}

	for (int plNum = 0; plNum < 2; plNum++)
	{
		int hp = players_[plNum]->GetHp();
		hpHundred_[plNum] = hp / 100;
		hp -= 100 * hpHundred_[plNum];
		hpTens_[plNum] = hp / 10;
		hp -= 10 * hpTens_[plNum];
		hpOnes_[plNum] = hp;
	}


	pl1ModelId_ = players_[0]->GetPlayerModelId();
	pl2ModelId_ = players_[1]->GetPlayerModelId();

	initFlag_ = true;
}

void GameScene::Draw(void)
{
	//  シャドウマップへの描画の準備
	ShadowMap_DrawSetup(shadowH);
	//  シャドウマップへモデルの描画
	MV1DrawModel(pl1ModelId_);
	MV1DrawModel(pl2ModelId_);
	//  シャドウマップへの描画を終了
	ShadowMap_DrawEnd();


	stage_->SetShadowH(shadowH);


	stage_->Draw();

	if (GameCountFlame_ > 40)
	{
		DrawGraph(0, 0, gameNumImgH_[GameCount_-1],true);
	}
	else if (GameCountFlame_ > 0)
	{
		DrawGraph(0, 0, startH_, true);
	}

	for (int i = 0; i < 2; i++)
	{
		//  i番目の敵が生きていたら
		if (players_[i]->IsAlive() == true)
		{
			players_[i]->Draw();
		}
	}

	for (int plNum = 0; plNum < 2; plNum++)
	{
		VECTOR pos = players_[plNum]->GetPos();
		pos.y += 283 * players_[plNum]->GetScl().y;
		SetDrawScreen(HpWindowH_[plNum]);
		ClsDrawScreen();

		DrawGraph(0, 0, HpBarImageH_[plNum], true);
		DrawGraph(0, 67, HpBarBlackImageH_, true);
		int hp = players_[plNum]->GetHp();
		for(int i =0; i < players_[plNum]->GetHp()/2;i++)
		{
			DrawGraph(i, 67, HpScaleImageH_, true);
		}
		DrawGraph(336, 92, NumImageH_[plNum][hpHundred_[plNum]], true);
		DrawGraph(336 + 51, 92, NumImageH_[plNum][hpTens_[plNum]], true);
		DrawGraph(336 + 100, 92, NumImageH_[plNum][hpOnes_[plNum]], true);

		SetDrawScreen(DX_SCREEN_BACK);

			SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();

		DrawBillboard3D(pos, 0.5f, 0.0f, 200, 0.0f, HpWindowH_[plNum], true);
	}

	if (p1win_ == true)
	{
		DrawGraph(0,0, imgP1Win_,true);
	}
	if (p2win_ == true)
	{
		DrawGraph(0,0, imgP2Win_,true);
	}

	//DrawFormatString(0, 200, 0x000000, "cameraHAngle:%0.f", SceneManager::GetInstance().GetCamera()->GetHAngle());
}

void GameScene::Release(void)
{
	stage_->Release();
	for (int i = 0; i < 2; i++)
	{

		players_[i]->Release();

	}
	DeleteShadowMap(shadowH);

	DeleteGraph(imgP1Win_);
	DeleteGraph(imgP2Win_);
	DeleteGraph(HpBarBlackImageH_);
	DeleteGraph(HpScaleImageH_);
	for (int plNum = 0; plNum < 2; plNum++)
	{
		DeleteGraph(HpBarImageH_[plNum]);
		DeleteGraph(HpWindowH_[plNum]);
	}

	for (int m = 0; m < 2; m++)
	{
		for (int n = 0; n < 10; n++)
		{
			DeleteGraph(NumImageH_[m][n]);
		}
	}

	MV1DeleteModel(modelPlayerId_);
	MV1DeleteModel(modelPlayerId2_);
	DeleteSoundMem(soundBgmH_);
	DeleteSoundMem(soundVicH_);

}

void GameScene::SetPlayer(std::weak_ptr<PlayerBase> player[2])
{
	for (int i = 0; i < 2; i++)
	{
		players_[i] = player[i].lock();
	}
}

void GameScene::GameSet(void)
{
	if (!CheckSoundMem(soundVicH_))
	{
		if (CheckSoundMem(soundBgmH_))
		{
			StopSoundMem(soundBgmH_);
		}

		PlaySoundMem(soundVicH_, DX_PLAYTYPE_LOOP, true);
	}

	//  シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) || ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}
