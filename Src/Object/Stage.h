#pragma once

class ResourceManager;

class Stage
{
public:
    // コンストラクタ
    Stage();
    // デストラクタ
    ~Stage();

    void Init();
    void Update();
    void Draw();
    void Release();

    int GetModelId();
    int GetCoverModelId();

    void SetShadowH(int handle);

private:
    // 3DモデルのハンドルID
    int modelId_;
    int coverModelId_;

    int modelSkyId_;

    // ステージ上に配置する飾り文字のID（当たり判定不要）
    int charId_;

    // 背景画像のハンドルID
    int imgBack_;

    int shadowH;

    ResourceManager& resMng_;
};
