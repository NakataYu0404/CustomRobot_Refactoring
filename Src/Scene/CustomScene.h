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
class ResourceManager;

class CustomScene : public SceneBase
{
public:
    // プレイヤー数
    static constexpr int PLAYER_NUM = 2;
    // 矢印画像数
    static constexpr int ARROW_IMAGE_NUM = 59;
    // セレクト画像数
    static constexpr int SELECT_IMAGE_NUM = 3;
    // Expo画面サイズ
    static constexpr int EXPO_SCREEN_W = 600;
    static constexpr int EXPO_SCREEN_H = 428;
    // プレビュー画面サイズ
    static constexpr int PREVIEW_SCREEN_W = 428;
    static constexpr int PREVIEW_SCREEN_H = 428;
    // UIボックス座標
    static constexpr int UI_BOX_X = 8;
    static constexpr int UI_BOX_Y = 2;
    // ウィンドウ最大サイズ
    static constexpr float WINDOW_MAX_SIZE_X = 480.0f;
    static constexpr float WINDOW_MAX_SIZE_Y = 0.0f;
    // 矢印初期座標
    static constexpr float ARROW_POS_X_INIT = 430.0f;
    static constexpr float ARROW_POS_Y_INIT = 62.0f;
    // フォントサイズ
    static constexpr int FONT_SIZE = 32;
    // ウィンドウ拡大分割数
    static constexpr float WINDOW_DIV = 15.0f;
    // ライン色
    static constexpr int LINE_COLOR = 0xff8844;

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

    //  コンストラクタ
    CustomScene(void);
    //  デストラクタ
    ~CustomScene(void);
    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
    //	プレイヤーポインタの取得(SceneManagerがカスタムシーンからゲームシーンにポインタを渡すためにポインタを欲しがってる)
    std::weak_ptr<PlayerBase> GetPlayer(int plNum);

private:
    // ボディ名リスト
    std::vector <std::string> body;
    // ガン名リスト
    std::vector <std::string> gun;
    // ボム名リスト
    std::vector <std::string> bomb;
    // ポッド名リスト
    std::vector <std::string> pod;
    // レグ名リスト
    std::vector <std::string> reg;

    // ウィンドウ最大サイズ
    VECTOR windowMaxSizeSelect;
    // ウィンドウ現在サイズ
    VECTOR windowSizeSelect[PLAYER_NUM];

    // フォントハンドル
    int fontH;
    // プレイヤーカラー
    int color_[PLAYER_NUM];

    // フルスクリーンハンドル
    int FullScreenH;
    // 各種画面ハンドル
    int bodyScreenH[PLAYER_NUM];
    int gunScreenH[PLAYER_NUM];
    int bombScreenH[PLAYER_NUM];
    int podScreenH[PLAYER_NUM];
    int regScreenH[PLAYER_NUM];
    int PreviewScreenH[PLAYER_NUM];
    int plScreenH[PLAYER_NUM];
    int expoScreenH[PLAYER_NUM];

    // 1項目の高さ（blank）
    int blank;

    // キーコンフィグ
    PlayerBase::KEY_CONFIG keyPl;

    // UI画像ハンドル
    int UIBoxH;
    int arrowH[ARROW_IMAGE_NUM];
    int arrowAnimCnt_;
    int plEndH_[PLAYER_NUM];

    // モデルハンドル
    int modelBirbH_;
    int modelYetiH_;
    int modelCactoroH_;
    int modelBemonH_;
    int modelGhostH_;

    // 画像ハンドル
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
    int imageSelectH_[SELECT_IMAGE_NUM];
    int selectImgCnt_;
    int soundBgmH_;

    // カスタム終了画像座標
    VECTOR ImageEndPos_[PLAYER_NUM];
    // プレイヤーモデルID
    int modelPlayerId_[PLAYER_NUM];
    // コントローラー傾き
    int ControllerTilt_[PLAYER_NUM];
    int ControllerTiltOld_[PLAYER_NUM];
    // 選択状態
    SelectState select_[PLAYER_NUM];
    SelectState cursor_[PLAYER_NUM];
    SelectState cursorOld_[PLAYER_NUM];
    // 矢印座標
    VECTOR arrowPos_[PLAYER_NUM];
    // カスタム終了フラグ
    bool finishFlag_[PLAYER_NUM];
    bool finishChangeFlag_[PLAYER_NUM];
    // プレイヤー
    std::shared_ptr<PlayerBase> players_[PLAYER_NUM];
    // プレイヤータイプ
    PlayerBase::TYPE type_[PLAYER_NUM];
    // 各種タイプ
    BODY_TYPE bodyType_[PLAYER_NUM];
    PlayerBase::SHOT_TYPE shotType_[PLAYER_NUM];
    PlayerBase::BOMB_TYPE bombType_[PLAYER_NUM];
    PlayerBase::POD_TYPE podType_[PLAYER_NUM];
    PlayerBase::REG_TYPE regType_[PLAYER_NUM];
    // カーソル保存用
    PlayerBase::SHOT_TYPE cursorShot_[PLAYER_NUM];
    PlayerBase::BOMB_TYPE cursorBomb_[PLAYER_NUM];
    PlayerBase::POD_TYPE cursorPod_[PLAYER_NUM];
    PlayerBase::REG_TYPE cursorReg_[PLAYER_NUM];

    // 画面切り替え・武器/ボディ変更・カーソル・各種描画
    void ChangeScreen(int player);
    void ChangeWeapon(int plNum);
    void ChangeBody(int plNum);
    void Cursor(void);
    void DrawBodyScreen(int player);
    void DrawShotScreen(int player);
    void DrawBombScreen(int player);
    void DrawPodScreen(int player);
    void DrawRegScreen(int player);
    void DrawExpoScreen(int player);
    void DrawPreviewScreen(int player);
    void WindowBeBig(int player, int maxSizeY);
    ResourceManager& resMng_;
};
