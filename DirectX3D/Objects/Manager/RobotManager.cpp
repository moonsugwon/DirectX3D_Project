#include "Framework.h"
#include "RobotManager.h"

RobotManager::RobotManager()
{
    //�ν��Ͻ� (�� ���� ��) ����
    robotInstancing = new ModelAnimatorInstancing("Robot");

    robotInstancing->ReadClip("StandUp");
    robotInstancing->ReadClip("Walk");
    robotInstancing->ReadClip("Run");
    robotInstancing->ReadClip("Hit");
    robotInstancing->ReadClip("Dying");

    //�κ� �ν��Ͻ� ���� �ν��Ͻ̰� ����
    FOR(SIZE)
    {
        Transform* transform = robotInstancing->Add(); // �ν��Ͻ̿��� Ʈ�������� �߰��� �� �Ŵ��������� �Ҵ�
        transform->SetActive(false); // ���� ���� ������ ������ ��ģ �� �ƴ϶� Ȱ��ȭ�� �� ��
        Robot* robot = new Robot(transform, robotInstancing, i); //���� �ε��� i��°, ���� �ν��Ͻ��� ���� �����ϴ� �κ� ����
        robots.push_back(robot); //���Ϳ� ���ٿ��� ���� �κ� �߰�
        delete transform;
    }

}

RobotManager::~RobotManager()
{
    delete robotInstancing;

    for (Robot* r : robots)
        delete r;
}

void RobotManager::Update()
{
    Collision();

    //�ð� ����� üũ
    time += DELTA;

    if (time >= SPAWN_TIME) //�ð��� ���� ���ݿ� �����ϸ�
    {
        time -= SPAWN_TIME; // time�� ���� �߻��� ������ �����ϰ� ����� ������ �켱
        // -> �� : ��ü�� �ð� ������ ���� ���� / �� : ������ �������� ��� �ұ�Ģ�� �����(���� ����)
// time = 0;        // time�� ���� �߻��� ������ �����ϰ� ���� ������ �켱
                    // -> �� : ��Ģ���� ���� ȯ���� ���� ���� / ���� : �ð� ������ ������ ������ �ִ�
        Spawn(); //�����
    }

    //�� ��ü�� ������Ʈ
    robotInstancing->Update();

    //�κ��� ��ü�鵵 ������Ʈ (��ü : ���赵�μ��� Ŭ���� + ������μ��� �ν��Ͻ��� ��Ī.)
    for (Robot* r : robots)
        r->Update();
}

void RobotManager::Render()
{
    robotInstancing->Render();

    //�κ��� ��ü�鵵 ������Ʈ (��ü : ���赵�μ��� Ŭ���� + ������μ��� �ν��Ͻ��� ��Ī.)
    for (Robot* r : robots)
        r->Render();
}

void RobotManager::PostRender()
{
    for (Robot* r : robots)
        r->PostRender();
}

void RobotManager::GUIRender()
{
}

void RobotManager::SetTarget(Transform* target)
{
    for (Robot* r : robots)
        r->SetTarget(target);
}

void RobotManager::Collision()
{

}

void RobotManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.y = 0;
    dir.z = Random(-1.0f, 1.0f);

    // �Ŵ����� ���� ���� ǥ���� ���� ��ġ���� ��� ���� ������, ������ ������ ��Ҹ� ����
    // �Ÿ��� �����ϰų�, �Ÿ����� �������� �ϰ� �ʹٸ� �Ʒ� �ڵ��� 2000.0f ����� ����
    Vector3 randomPos = (dir.GetNormalized() * 1000.0f);

    //������ ���� ��ҿ��� �κ� ����
    for (Robot* r : robots)
    {
        if (!r->GetTransform()->Active()) // ���� �κ��� �� ���� �ִٸ�
        {
            r->Spawn(randomPos);
            break; //���� ����
        }
    }
}
