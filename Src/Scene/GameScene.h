#pragma once
#include <vector>
#include <memory>
#include "SceneBase.h"
#include "CustomScene.h"

class ResourceManager;
class Stage;
class Cannon;
class PlayerBase;

class GameScene : public SceneBase
{
public:

	//  ゲームオーバー地点衝突判定球の半径
	static constexpr float OVER_COL_RADIUS = 35.0f;

	//  コンストラクタ
	GameScene(void);

	//  デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//	カスタムしたプレイヤーをセットする(CustomScene→SceneManager→GameScene)
	void SetPlayer(std::weak_ptr<PlayerBase> player[2]);

private:

	//	ステージポインタ(このクラスで作る)
	std::shared_ptr<Stage> stage_;

	//  プレイヤーのid
	int modelPlayerId_;
	int modelPlayerId2_;

	//	プレイヤーポインタ(あるものを代入する)
	std::shared_ptr<PlayerBase> players_[2];

	//  ゲームオーバー判定
	bool p2win_;
	bool p1win_;

	//  ゲームオーバー画像
	int imgP1Win_;
	int imgP2Win_;

	//	プレイヤー座標
	VECTOR pl1Pos_;
	VECTOR pl2Pos_;

	//	影画像
	int shadowH;

	//	モデルID
	int pl1ModelId_;
	int pl2ModelId_;

	//	現在HPの各位を計算する(画像に直すため)
	int hpHundred_[2];
	int hpTens_[2];
	int hpOnes_[2];

	//  0～9の番号画像ハンドル（HPに使う）
	int NumImageH_[2][10];

	//	HP描画に使う画像ハンドル
	int HpWindowH_[2];
	int HpBarImageH_[2];
	int HpBarBlackImageH_;
	int HpScaleImageH_;

	//	最初のカウントダウンに使う画像ハンドル
	int gameNumImgH_[5];

	//	各サウンドハンドル
	int soundBgmH_;
	int soundVicH_;

	//	よーいどんカウント
	int GameCountFlame_;
	int GameCount_;

	//	スタート！画像ハンドル
	int startH_;
	
	//	1ゲームループだけ特定の処理を無視するためのフラグ
	bool initFlag_;

	//  決着がついた後の処理(セッターじゃないよ！)
	void GameSet(void);

	ResourceManager& resMng_;
};

