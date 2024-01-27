#pragma once

class ModelClip
{
private:
    friend class ModelAnimator;
    friend class ModelAnimatorInstancing;

    ModelClip() = default;
    ~ModelClip();

    void Init();
    void Excute();

    KeyFrame* GetKeyFrame(string boneName);
    bool IsPlaying() { return playTime > 0; }



public:
    void SetEvent(Event event, float timeRatio);   
    bool IsNearEnd(float scale = 1.0f ) { return playTime / duration > (0.99f / scale); }

    bool IsEnd()      { return playTime / duration > 1.0f; }
    float GetRatio() { return playTime / duration; }
    void ResetPlayTime() { playTime = -DELTA * 2; }

    bool isFirstPlay()
    {
        if (playTime < DELTA)
            return true;
        else
            return false;
    }

private:
    string name;
    string lockBone;

    UINT frameCount;
    float tickPerSecond;
    float duration;

    float playTime = 0.0f;

    unordered_map<string, KeyFrame*> keyFrames;

    map<float, Event> events;
    map<float, Event>::iterator eventIter;
};