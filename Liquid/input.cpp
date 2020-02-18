// インクルード --------------------------------------------------
#include "DxLib.h"

#include "Input.h"

// 関数実体 ------------------------------------------------------

Input* Input::instance = NULL;

void Input::Create()
{
    if (!instance)
    {
        instance = new Input;
    }
}

void Input::Destroy()
{
    delete instance;
    instance = NULL;
}

void Input::Init()
{

}

void Input::Updata()
{
    GetHitKeyStateAll(key);

    for (int i = 0; i < 256; i++)
    {
        if (key[i])
        {
            if (key_buf[i] == Not)
                key_buf[i] = Down;
            else if (key_buf[i] == Down)
                key_buf[i] = Stay;
        }
        else key_buf[i] = Not;
        key[i] = key_buf[i];
    }

    GetJoypadXInputState(DX_INPUT_PAD1, &input[0]);
    GetJoypadXInputState(DX_INPUT_PAD2, &input[1]);

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            if (input[j].Buttons[i])
            {
                if (button[j][i] == Not)
                    button[j][i] = Down;
                else if (button[j][i] == Down)
                    button[j][i] = Stay;
            }
            else button[j][i] = Not;
        }
#pragma region Thumb
        if (input[j].ThumbLX > 0)
        {
            if (input[j].ThumbLX < 8000)
                ThumbLX[j] = Not;
            else if (input[j].ThumbLX < 20000)
                ThumbLX[j] = Mid;
            else if (input[j].ThumbLX < 35000)
                ThumbLX[j] = Max;
        }
        if (input[j].ThumbLX < 0)
        {
            if (input[j].ThumbLX > -8000)
                ThumbLX[j] = Not;
            else if (input[j].ThumbLX > -20000)
                ThumbLX[j] = -Mid;
            else if (input[j].ThumbLX > -35000)
                ThumbLX[j] = -Max;
        }

        if (input[j].ThumbLY > 0)
        {
            if (input[j].ThumbLY < 8000)
                ThumbLY[j] = Not;
            else if (input[j].ThumbLY < 20000)
                ThumbLY[j] = Mid;
            else if (input[j].ThumbLY < 35000)
                ThumbLY[j] = Max;
        }
        if (input[j].ThumbLY < 0)
        {
            if (input[j].ThumbLY > -8000)
                ThumbLY[j] = Not;
            else if (input[j].ThumbLY > -20000)
                ThumbLY[j] = -Mid;
            else if (input[j].ThumbLY > -35000)
                ThumbLY[j] = -Max;
        }

        if (input[j].ThumbRX > 0)
        {
            if (input[j].ThumbRX < 8000)
                ThumbRX[j] = Not;
            else if (input[j].ThumbRX < 20000)
                ThumbRX[j] = Mid;
            else if (input[j].ThumbRX < 35000)
                ThumbRX[j] = Max;
        }
        if (input[j].ThumbRX < 0)
        {
            if (input[j].ThumbRX > -8000)
                ThumbRX[j] = Not;
            else if (input[j].ThumbRX > -20000)
                ThumbRX[j] = -Mid;
            else if (input[j].ThumbRX > -35000)
                ThumbRX[j] = -Max;
        }

        if (input[j].ThumbRY > 0)
        {
            if (input[j].ThumbRY < 8000)
                ThumbRY[j] = Not;
            else if (input[j].ThumbRY < 20000)
                ThumbRY[j] = Mid;
            else if (input[j].ThumbRY < 35000)
                ThumbRY[j] = Max;
        }
        if (input[j].ThumbRY < 0)
        {
            if (input[j].ThumbRY > -8000)
                ThumbRY[j] = Not;
            else if (input[j].ThumbRY > -20000)
                ThumbRY[j] = -Mid;
            else if (input[j].ThumbRY > -35000)
                ThumbRY[j] = -Max;
        }
#pragma endregion
    }
}

// 押した瞬間だけTRUEを返す
bool Input::GetKeyDown(int inputKey)
{
    if (key[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す(全てのキー)
bool Input::GetKeyDownAll(void)
{
    for (int inputKey = 0; inputKey < 256; inputKey++)
    {
        if (key[inputKey] == Down)
        {
            return true;
        }
    }

    return false;
}

// 押している間TRUEを返す
bool Input::GetKey(int inputKey)
{
    if (key[inputKey] == Stay || key[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す
bool Input::GetButtonDown(PL_Num plNum, int inputKey)
{
    if (button[plNum][inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す(全てのボタン)
bool Input::GetButtonDownAll(PL_Num plNum)
{
    for (int inputKey = 0; inputKey < 16; inputKey++)
    {
        if (button[plNum][inputKey] == Down)
        {
            return true;
        }
    }

    return false;
}

// 押している間TRUEを返す
bool Input::GetButton(PL_Num plNum, int inputKey)
{
    if (button[plNum][inputKey] == Stay || button[plNum][inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 左スティックを倒している時、各方向にTRUEを返す
bool Input::GetLeftThumb(PL_Num plNum, int  LeftThumb)
{
    switch (LeftThumb)
    {
    case Thumb::Not:
        if (ThumbLX[plNum] == Input::Thumb_State::Zero && ThumbLY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Up:
        if (ThumbLX[plNum] == Input::Thumb_State::Zero && ThumbLY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Before_Upper_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Upper_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::After_Upper_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Before_Lower_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Max && ThumbLY[plNum] == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Lower_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Max && ThumbLY[plNum] == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Lower_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid && ThumbLY[plNum] == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Down:
        if (ThumbLX[plNum] == Input::Thumb_State::Zero && ThumbLY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Before_Lower_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid && ThumbLY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Lower_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Max && ThumbLY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::After_Lower_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Max && ThumbLY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Before_Upper_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Upper_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Max && ThumbLY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Upper_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Little_Up:
        if (ThumbLX[plNum] == Input::Thumb_State::Zero && ThumbLY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Little_Down:
        if (ThumbLX[plNum] == Input::Thumb_State::Zero && ThumbLY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Little_Upper_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Little_Lower_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid && ThumbLY[plNum] == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Lower_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid && ThumbLY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Upper_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid && ThumbLY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Roughly_Up:
        if (ThumbLY[plNum] == Input::Thumb_State::Mid || ThumbLY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Right:
        if (ThumbLX[plNum] == Input::Thumb_State::Mid || ThumbLX[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Down:
        if (ThumbLY[plNum] == -Input::Thumb_State::Mid || ThumbLY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Roughly_Left:
        if (ThumbLX[plNum] == -Input::Thumb_State::Mid || ThumbLX[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    }
    return false;
}

// 右スティックを倒している時、各方向にTRUEを返す
bool Input::GetRightThumb(PL_Num plNum, int  RightThumb)
{
    switch (RightThumb)
    {
    case Thumb::Not:
        if (ThumbRX[plNum] == Input::Thumb_State::Zero && ThumbRY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Up:
        if (ThumbRX[plNum] == Input::Thumb_State::Zero && ThumbRY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Before_Upper_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Upper_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::After_Upper_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Before_Lower_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Max && ThumbRY[plNum] == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Lower_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Max && ThumbRY[plNum] == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Lower_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid && ThumbRY[plNum] == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Down:
        if (ThumbRX[plNum] == Input::Thumb_State::Zero && ThumbRY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Before_Lower_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid && ThumbRY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Lower_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Max && ThumbRY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::After_Lower_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Max && ThumbRY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Before_Upper_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Upper_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Max && ThumbRY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Upper_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Little_Up:
        if (ThumbRX[plNum] == Input::Thumb_State::Zero && ThumbRY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Little_Down:
        if (ThumbRX[plNum] == Input::Thumb_State::Zero && ThumbRY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Little_Upper_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Little_Lower_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid && ThumbRY[plNum] == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Lower_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid && ThumbRY[plNum] == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Upper_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid && ThumbRY[plNum] == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Roughly_Up:
        if (ThumbRY[plNum] == Input::Thumb_State::Mid || ThumbRY[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Right:
        if (ThumbRX[plNum] == Input::Thumb_State::Mid || ThumbRX[plNum] == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Down:
        if (ThumbRY[plNum] == -Input::Thumb_State::Mid || ThumbRY[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Roughly_Left:
        if (ThumbRX[plNum] == -Input::Thumb_State::Mid || ThumbRX[plNum] == -Input::Thumb_State::Max)   return true;
        break;
    }
    return false;
}