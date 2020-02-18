#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"

// 定数 ----------------------------------------------------------------
enum Thumb
{
    Not,    // 入力なし
    Up, Before_Upper_Right, Upper_Right, After_Upper_Right,     // 上から右
    Right, Before_Lower_Right, Lower_Right, After_Lower_Right,  // 右から下
    Down, Before_Lower_Left, Lower_Left, After_Lower_Left,      // 下から左
    Left, Before_Upper_Left, Upper_Left, After_Upper_Left,      // 左から上
    Little_Up, Little_Right, Little_Down, Little_Left,      // 中くらい倒してる時
    Little_Upper_Right, Little_Lower_Right, Little_Lower_Left, Little_Upper_Left,
    Roughly_Up, Roughly_Right, Roughly_Left, Roughly_Down   // 他の入力に関係なく各上下左右を取る
};

/// InputClass How to
// 1.Input.hをインクルードする
// 2. Input::GetInstance()でインスタンスを経由してpublic関数を呼び出す。
// 例）　Input::GetInstance()->GetButtonDown(PL_1, XINPUT_BUTTON_Y);

class Input
{
public:
    // シングルトン
    static Input* GetInstance()
    {
        return instance;
    }
    static void Create();
    static void Destroy();

    // 初期化
    void Init();
    // 入力更新
    void Updata();
    // 押した瞬間だけTRUEを返す
    bool GetKeyDown(int inputKey);
    // 押した瞬間だけTRUEを返す(全てのキー)
    bool GetKeyDownAll(void);
    // 押している間TRUEを返す
    bool GetKey(int inputKey);
    // 押した瞬間だけTRUEを返す
    bool GetButtonDown(PL_Num playerNum, int inputKey);
    // 押した瞬間だけTRUEを返す(全てのボタン)
    bool GetButtonDownAll(PL_Num plNum);
    // 押している間TRUEを返す
    bool GetButton(PL_Num playerNum, int inputKey);
    // 左スティックを倒している方向の値を返す
    bool GetLeftThumb(PL_Num plNum, int  LeftThumb);
    // 右スティックを倒している方向の値を返す
    bool GetRightThumb(PL_Num plNum, int  RightThumb);

private:
    XINPUT_STATE input[2] = {};
    char key[256] = {};// 入力情報
    char key_buf[256] = {};
    int button[2][16] = {};
    int ThumbLX[2] = {};
    int ThumbLY[2] = {};
    int ThumbRX[2] = {};
    int ThumbRY[2] = {};
    enum Input_State
    {
        Not, Down, Stay
    };
    enum Thumb_State
    {
        Zero, Mid, Max
    };

protected:


    Input() {};
    virtual ~Input() {};
    static Input* instance;
};