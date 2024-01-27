#pragma once
class GameScene : public Scene
{
public:

    GameScene();
    ~GameScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

private:
    Player* player = nullptr;

    Model* ground = nullptr;
    SkyBox* sky = nullptr;

    Quad* clockFrame;
    Quad* durability;
    Quad* durability_gauge;
    Quad* hpBar;
    Quad* idBar;
    Quad* itemSlot;
    Quad* lsCoting;
    Quad* lsCoting2;
    Quad* lsGauge;
    Quad* lsGauge2;
    Quad* quickSlot;
    Quad* slingerBug;
    Quad* staminarBar;
};

