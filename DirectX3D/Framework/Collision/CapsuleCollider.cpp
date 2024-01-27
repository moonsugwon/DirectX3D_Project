#include "Framework.h"

CapsuleCollider::CapsuleCollider(float radius, float height, UINT stackCount, UINT sliceCount)
    : radius(radius), height(height), stackCount(stackCount), sliceCount(sliceCount)
{
    type = CAPSULE;
    MakeMesh();
    mesh->CreateMesh();
}

bool CapsuleCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld();

    Vector3 dir = Up();
    Vector3 pa = GlobalPos() - dir * Height() * 0.5f;
    Vector3 pb = GlobalPos() + dir * Height() * 0.5f;

    float r = Radius();

    Vector3 rayOrigin = ray.pos;
    Vector3 rayDir = ray.dir;

    Vector3 ba = pb - pa;
    Vector3 oa = rayOrigin - pa;

    // ĸ���� ��, ����, �̵��� ��ġ ���踦 ��� ���� ������ ����
    float baba = Dot(ba, ba);
    float bard = Dot(ba, rayDir);
    float baoa = Dot(ba, oa);
    float rdoa = Dot(rayDir, oa);
    float oaoa = Dot(oa, oa);

    float a = baba - bard * bard;
    float b = baba * rdoa - baoa * bard;
    float c = baba * oaoa - baoa * baoa - r * r * baba;
    // ���� ���� ���� ����Ǵ� �� :  �ش� �� ���� �������� �ϴ� ������ ����

    float h = b * b - a * c;

    if (h >= 0)
    {
        float t = (-b - sqrt(h)) / a;
        float distance = baoa + t * bard;

        if (distance > 0 && distance < baba)
        {
            // ����� ��ġ�� �ٸ� �� ���� �������� ���ߴµ�, ��ǥ�� �����̸�
            // �� ���� ���� ���̴�
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }
            return true;
        }

        Vector3 oc = (distance < 0) ? oa : rayOrigin - pb;
        b = Dot(rayDir, oc);
        c = Dot(oc, oc) - r * r;
        h = b * b - c;

        if (h > 0 ) //  �Ʒ��� ���� �����ε� �޶�ƽ���� + ���
        {
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;

            }
            return true;
        }


    }


    return false;
}

bool CapsuleCollider::IsBoxCollision(BoxCollider* collider)
{  
    BoxCollider::ObbDesc box;
    collider->GetObb(box);

    // ĸ���� ����� ����
    Vector3 dir = Up();
    Vector3 pa = GlobalPos() - dir * Height() * 0.5f;
    Vector3 pb = GlobalPos() + dir * Height() * 0.5f;

    Vector3 closestPointToCapsuleArc = box.pos;
    Vector3 pointOnline = ClosestPointOnLine(pa, pb, box.pos);

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = pointOnline - box.pos;

        float length = Dot(box.axis[i], direction);

        float mult = (length < 0.0f) ? -1.0f : 1.0f;

        length = min(abs(length), box.halfSize[i]);

        closestPointToCapsuleArc += box.axis[i] * length * mult;
    }

    float distance = Distance(pointOnline, closestPointToCapsuleArc);

    return distance <= Radius();
}

bool CapsuleCollider::IsSphereCollision(SphereCollider* collider)
{
    // ĸ�� ����
    Vector3 dir = Up();
    Vector3 pa = GlobalPos() - dir * Height() * 0.5f;
    Vector3 pb = GlobalPos() + dir * Height() * 0.5f;

    Vector3 P = collider->GlobalPos();

    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, P);
    float distance = Distance(P, pointOnLine);

    return distance <= (Radius() + collider->Radius());
}

bool CapsuleCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    // ��츦 ������ 
    // 1. �� �κг��� �ε�ġ�� -> ������ ���� �Ÿ��� ��
    // 2.  �� ���� �ε�ġ�� - > ��������
    // 3. ��ü vs ���̴�??  ���� ���忡�� ��ü �߽ɱ����� �ִܰŸ� ����Ʈ�� �����ؼ� �ش� ���� ��ü ������ �������� Ȯ��

    Vector3 aDirection = Up();
    Vector3 aA = GlobalPos() - aDirection * Height() * 0.5f;
    Vector3 aB = GlobalPos() + aDirection * Height() * 0.5f;

    Vector3 bDirection = collider->Up();
    Vector3 bA = collider->GlobalPos() - bDirection * collider->Height() * 0.5f;
    Vector3 bB = collider->GlobalPos() + bDirection * collider->Height() * 0.5f;

    Vector3 v0 = bA - aA;
    Vector3 v1 = bB - aA;
    Vector3 v2 = bA - aB;
    Vector3 v3 = bB - aB;

    float d0 = Dot(v0, v0);
    float d1 = Dot(v1, v1);
    float d2 = Dot(v2, v2);
    float d3 = Dot(v3, v3);

    Vector3 bestA;
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 > d1)
        bestA = aB;
    else
        bestA = aA;

    Vector3 bestB = ClosestPointOnLine(bA, bB, bestA);
    bestA = ClosestPointOnLine(aA, aB, bestB);
    bestB = ClosestPointOnLine(bA, bB, bestA);

    float distance = Distance(bestA, bestB);

    return distance <= (Radius() + collider->Radius());
}

void CapsuleCollider::MakeMesh()
{
    float thetaStep = XM_2PI / sliceCount;
    float phiStep = XM_PI / stackCount;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * (stackCount + 1));

    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;
            vertex.pos.x = sin(phi) * cos(theta) * radius;
            vertex.pos.y = cos(phi) * radius;
            vertex.pos.z = sin(phi) * sin(theta) * radius;

            if (vertex.pos.y > 0)
                vertex.pos.y += height * 0.5f;
            else if(vertex.pos.y < 0)
                vertex.pos.y -= height * 0.5f;

            vertices.push_back(vertex);
        }
    }

    //Indices
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * stackCount * 6);

    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//1

            indices.push_back((sliceCount + 1) * i + j);//0            
            indices.push_back((sliceCount + 1) * i + j + 1);//2            
        }
    }
}
