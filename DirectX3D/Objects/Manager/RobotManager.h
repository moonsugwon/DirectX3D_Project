#pragma once

class RobotManager : public Singleton<RobotManager>
{
private:
    UINT SIZE = 5; // �ִ� �� ��ü���� ������ ���ΰ� (���� ũ��)
    float SPAWN_TIME = 15.0f; // ���� Ȥ�� ������� �ʿ��� �ð� (����)

public:
    //�ܺ�ȣ���

    RobotManager();
    ~RobotManager();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    //�κ� Ȥ�� �κ����� ������ �Ѿư� ������ �Ŵ������� ���� �����ϵ���
    void SetTarget(Transform* target);

    vector<Robot*> GetRobots() { return robots; }

private:
    //���θ���Լ�
    void Collision(); // �浹 ���� ����
    void Spawn(); // (��)����

private:
    //���θ������

    ModelAnimatorInstancing* robotInstancing;
    vector<Robot*> robots;

    Transform* target;

    float time = 0; // ��� �ð�

};

