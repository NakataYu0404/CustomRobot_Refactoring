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
    // プレイヤー数
    static constexpr int PLAYER_NUM = 2;
    // HPウィンドウサイズ
    static constexpr int HP_WINDOW_W = 500;
    static constexpr int HP_WINDOW_H = 163;
    // HPバー座標
    static constexpr int HP_BAR_X = 0;
    static constexpr int HP_BAR_Y = 67;
    // HP数値座標
    static constexpr int HP_NUM_X = 336;
    static constexpr int HP_NUM_Y = 92;
    static constexpr int HP_NUM_TENS_OFFSET = 51;
    static constexpr int HP_NUM_ONES_OFFSET = 100;
    // カウントダウン最大
    static constexpr int GAME_COUNT_MAX = 5;
    // シャドウマップサイズ
    static constexpr int SHADOW_MAP_SIZE = 2048;
    // シャドウ描画範囲
    static constexpr float SHADOW_AREA_MIN = -1000.0f;
    static constexpr float SHADOW_AREA_MAX = 1000.0f;
    // カプセル判定半径
    static constexpr float CAPSULE_RADIUS = 25.0f;
    // HPバー描画倍率
    static constexpr float HP_BAR_SCALE = 0.5f;
    // ゲームオーバー判定用コリジョン半径
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
    void SetPlayer(std::weak_ptr<PlayerBase> player[PLAYER_NUM]);

private:
    //	ステージポインタ(このクラスで作る)
    std::shared_ptr<Stage> stage_;

    //  プレイヤーのid
    int modelPlayerId_;
    int modelPlayerId2_;

    //	プレイヤーポインタ(あるものを代入する)
    std::shared_ptr<PlayerBase> players_[PLAYER_NUM];

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
    int hpHundred_[PLAYER_NUM];
    int hpTens_[PLAYER_NUM];
    int hpOnes_[PLAYER_NUM];

    //  0～9の番号画像ハンドル（HPに使う）
    int NumImageH_[PLAYER_NUM][10];

    //	HP描画に使う画像ハンドル
    int HpWindowH_[PLAYER_NUM];
    int HpBarImageH_[PLAYER_NUM];
    int HpBarBlackImageH_;
    int HpScaleImageH_;

    //	最初のカウントダウンに使う画像ハンドル
    int gameNumImgH_[GAME_COUNT_MAX];

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

