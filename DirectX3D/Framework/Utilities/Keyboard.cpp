#include "Framework.h"

void Keyboard::Update()
{
    memcpy(oldState, curState, sizeof(oldState));

    //0, 1 -> 키보드 입력 X
    //128, 129 -> 키보드 입력 O
    GetKeyboardState(curState);

    for(UINT i = 0 ; i < KEY_MAX ; i++)
    {
        BYTE key = curState[i] & 0x80;
        
        curState[i] = key ? 1 : 0;

        if (curState[i] == 1 && (i == VK_LBUTTON || i == VK_RBUTTON))
            keyStorage.push_front(make_pair(i, 0.0f));

        BYTE old = oldState[i];
        BYTE cur = curState[i];

        if (old == 0 && cur == 1)
            mapState[i] = DOWN;
        else if (old == 1 && cur == 0)
            mapState[i] = UP;
        else if (old == 1 && cur == 1)
            mapState[i] = PRESS;
        else
            mapState[i] = NONE;
    }

    for (auto& p : keyStorage)
    {
        p.second += DELTA;

        if (p.second >= keyStoreTime)
            keyStorage.pop_back();
    }
}

bool Keyboard::IsInputBufferFront(UINT key)
{
    if (keyStorage.front().first == key)
        return true;
    else 
        return false;
}
