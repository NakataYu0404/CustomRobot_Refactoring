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

	//	今どこのパーツを選ぼうとしているか
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

	//	体パーツ
	enum class BODY_TYPE
	{
		Birb,
		Yeti,
		Cactoro,
		Bemon,
		Ghost,

	};


	// コンストラクタ
	CustomScene(void);

	// デストラクタ
	~CustomScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//	プレイヤーポインタの取得(SceneManagerがカスタムシーンからゲームシーンにポインタを渡すためにポインタを欲しがってる)
	std::weak_ptr<PlayerBase> GetPlayer(int plNum);

private:
	// 素体のリスト
	std::vector <std::string> body;
	// ガンのリスト
	std::vector <std::string> gun;
	// ボムのリスト
	std::vector <std::string> bomb;
	// ポッドのリスト
	std::vector <std::string> pod;
	// レッグのリスト
	std::vector <std::string> reg;

	//	セレクトウィンドウの最大、現在サイズ
	VECTOR windowMaxSizeSelect;
	VECTOR windowSizeSelect[2];

	//	フォントハンドル
	int fontH;
	//	文字描画するとき用プレイヤーごとのカラーハンドル
	int color_[2];

	// 各パーツ選択スクリーン、プレイヤープレビュースクリーンをまとめるスクリーン　これをBACKに描画する
	int FullScreenH;
	// 各パーツ選択画面スクリーンハンドル
	int bodyScreenH[2];
	int gunScreenH[2];
	int bombScreenH[2];
	int podScreenH[2];
	int regScreenH[2];

	// プレイヤープレビュー
	int PreviewScreenH[2];
	// プレイヤーごとにまとめたスクリーン
	int plScreenH[2];

	// プレイヤー、武器の説明をしてくれるスクリーン
	int expoScreenH[2];

	//	各スクリーンを作成する際に用いる隙間サイズ(行間とか)
	int blank;

	// キーコンフィグ
	PlayerBase::KEY_CONFIG keyPl;

	// 画像、モデルハンドル達
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
	
	//	カスタム終了画像位置(移動するため必要)
	VECTOR ImageEndPos_[2];

	// 選択されているプレイヤーモデルのid
	int modelPlayerId_[2];

	//	カーソル操作の際に用いる、コントローラースティックの傾き、１フレ前の傾き
	int ControllerTilt_[2];
	int ControllerTiltOld_[2];

	// 現在描画しているスクリーンのステート
	SelectState select_[2];

	// カーソルのステート(決定ボタンが押された時、このステートにselect_がきてselect_のステートはcursor_に。)
	SelectState cursor_[2];
	SelectState cursorOld_[2];

	//	カーソルの位置
	VECTOR arrowPos_[2];

	//	カスタムが終わったかフラグ
	bool finishFlag_[2];
	bool finishChangeFlag_[2];

	//	プレイヤー
	std::shared_ptr<PlayerBase> players_[2];
	 
	//	自分がプレイヤー1か2か
	PlayerBase::TYPE type_[2];

	//	各種パーツのタイプ
	BODY_TYPE bodyType_[2];
	PlayerBase::SHOT_TYPE shotType_[2];
	PlayerBase::BOMB_TYPE bombType_[2];
	PlayerBase::POD_TYPE podType_[2];
	PlayerBase::REG_TYPE regType_[2];

	//	各種パーツ選択のとき、カーソルをどこにおくか(カーソル位置を保存して、再び開いたときに、前回位置からカーソルを出発させるために必要)
	PlayerBase::SHOT_TYPE cursorShot_[2];
	PlayerBase::BOMB_TYPE cursorBomb_[2];
	PlayerBase::POD_TYPE cursorPod_[2];
	PlayerBase::REG_TYPE cursorReg_[2];

	//	スクリーンの切り替え（現在スクリーンAと、パーツ選択画面選択の決定時にカーソルが乗ってたパーツ選択画面スクリーンBの切り替え）
	void ChangeScreen(int player);
	// それぞれカスタムが終了した時に、武器、体を設定する(このあとゲームシーンへ)
	void ChangeWeapon(int plNum);
	void ChangeBody(int plNum);

	//	カーソル移動と描画
	void Cursor(void);

	//	各種パーツ描画スクリーンの描画
	void DrawBodyScreen(int player);
	void DrawShotScreen(int player);
	void DrawBombScreen(int player);
	void DrawPodScreen(int player);
	void DrawRegScreen(int player);

	//	説明書き描画スクリーンの描画
	void DrawExpoScreen(int player);

	//	プレイヤー描画スクリーンの描画
	void DrawPreviewScreen(int player);

	// ウィンドウがだんだんでかくなーる
	void WindowBeBig(int player, int maxSizeY);
};
