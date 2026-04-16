#include <iostream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <functional>
#include <algorithm>

using namespace std;

struct Vector3 {
    int x;
    int y;
    int z;
};

struct Matrix4x4 {
    float arr[4][4] = { 0, };

    static Matrix4x4 RotateX(float angle) {
        Matrix4x4 result;
        float radianAngle = angle * M_PI / 180.0f;
        float cosAngle = cos(radianAngle);
        float sinAngle = sin(radianAngle);
        result.arr[0][0] = 1.0f;
        result.arr[1][1] = cosAngle;
        result.arr[1][2] = -sinAngle;
        result.arr[2][1] = sinAngle;
        result.arr[2][2] = cosAngle;
        result.arr[3][3] = 1.0f;
        return result;
    }

    static Matrix4x4 RotateY(float angle) {
        Matrix4x4 result;
        float radianAngle = angle * M_PI / 180.0f;
        float cosAngle = cos(radianAngle);
        float sinAngle = sin(radianAngle);
        result.arr[0][0] = cosAngle;
        result.arr[0][2] = sinAngle;
        result.arr[1][1] = 1.0f;
        result.arr[2][0] = -sinAngle;
        result.arr[2][2] = cosAngle;
        result.arr[3][3] = 1.0f;
        return result;
    }

    static Matrix4x4 RotateZ(float angle) {
        Matrix4x4 result;
        float radianAngle = angle * M_PI / 180.0f;
        float cosAngle = cos(radianAngle);
        float sinAngle = sin(radianAngle);
        result.arr[0][0] = cosAngle;
        result.arr[0][1] = -sinAngle;
        result.arr[1][0] = sinAngle;
        result.arr[1][1] = cosAngle;
        result.arr[2][2] = 1.0f;
        result.arr[3][3] = 1.0f;
        return result;
    }

    static Vector3 TransformVector(const Vector3& v, const Matrix4x4& matrix) {
        float x = v.x * matrix.arr[0][0] + v.y * matrix.arr[1][0] + v.z * matrix.arr[2][0] + matrix.arr[3][0];
        float y = v.x * matrix.arr[0][1] + v.y * matrix.arr[1][1] + v.z * matrix.arr[2][1] + matrix.arr[3][1];
        float z = v.x * matrix.arr[0][2] + v.y * matrix.arr[1][2] + v.z * matrix.arr[2][2] + matrix.arr[3][2];
        return Vector3{ (int)round(x), (int)round(y), (int)round(z) };
    }
};

char GetColor(Vector3 direction) {
    float absX = abs(direction.x);
    float absY = abs(direction.y);
    float absZ = abs(direction.z);

    if (absX > absY && absX > absZ) {
        if (direction.x > 0)
            return 'b'; // Right
        else
            return 'g'; // Left
    }
    else if (absY > absX && absY > absZ) {
        if (direction.y > 0)
            return 'r'; // Front
        else
            return 'o'; // Back
    }
    else {
        if (direction.z > 0)
            return 'w'; // Up
        else
            return 'y'; // Down
    }
}

class Face {
    Vector3 frontVector;
    char color;

public:
    Face(Vector3 _frontVector, char _color)
    {
        frontVector = _frontVector;
        color = _color;
    }

    void Rotate(Vector3 eulerRotation)
    {
        if (eulerRotation.x != 0)
        {
            frontVector = Matrix4x4::TransformVector(frontVector, Matrix4x4::RotateX(eulerRotation.x));
        }
        if (eulerRotation.y != 0)
        {
            frontVector = Matrix4x4::TransformVector(frontVector, Matrix4x4::RotateY(eulerRotation.y));
        }
        if (eulerRotation.z != 0)
        {
            frontVector = Matrix4x4::TransformVector(frontVector, Matrix4x4::RotateZ(eulerRotation.z));
        }
    }

    Vector3 GetFrontVector() { return frontVector; }

    char GetColor() { return color; }
};

class CubeBlock {
    vector<Face> faces;
    Vector3 position;

public:
    CubeBlock(vector<Face> _faces, Vector3 _position)
    {
        faces = _faces;
        position = _position;
    }

    void Rotate(Vector3 eulerRotation)
    {
        if (eulerRotation.x != 0)
        {
            position = Matrix4x4::TransformVector(position, Matrix4x4::RotateX(eulerRotation.x));
        }
        if (eulerRotation.y != 0)
        {
            position = Matrix4x4::TransformVector(position, Matrix4x4::RotateY(eulerRotation.y));
        }
        if (eulerRotation.z != 0)
        {
            position = Matrix4x4::TransformVector(position, Matrix4x4::RotateZ(eulerRotation.z));
        }

        for(auto & face : faces)
        {
            face.Rotate(eulerRotation);
        }
    }

    Vector3 GetPosition() { return position; }

    vector<Face> GetFaces() { return faces; }
};


class Cube {
    vector<shared_ptr<CubeBlock>> blocks;

public:
    Cube() {
        for (int x = -1;x <= 1;++x)
        {
            for (int y = -1;y <= 1;++y)
            {
                for (int z = -1;z <= 1;++z)
                {
                    vector<Face> faces;
                    Vector3 position = Vector3{ x,y,z };
                    if (x != 0)
                    {
                        faces.push_back(Face(Vector3{ x, 0, 0 }, GetColor(Vector3{ x, 0, 0 })));
                    }
                    if (y != 0)
                    {
                        faces.push_back(Face(Vector3{ 0, y, 0 }, GetColor(Vector3{ 0, y, 0 })));
                    }
                    if (z != 0)
                    {
                        faces.push_back(Face(Vector3{ 0, 0, z }, GetColor(Vector3{ 0, 0, z })));
                    }

                    blocks.push_back(make_shared<CubeBlock>(faces, position));
                }
            }
        }
    }

    void Rotate(char direction, int sign)
    {
        function<void(vector<shared_ptr<CubeBlock>>&)> _rotateFunc;

        switch (direction)
        {
        case 'U':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.z == 1)
                    {
                        cubeBlock->Rotate(Vector3{ 0, 0, -sign * 90 });
                    }
                }
                };
            break;
        case 'D':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.z == -1)
                    {
                        cubeBlock->Rotate(Vector3{ 0, 0, sign * 90 });
                    }
                }
                };
            break;
        case 'F':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.y == 1)
                    {
                        cubeBlock->Rotate(Vector3{ 0, -sign * 90, 0 });
                    }
                }
                };
            break;
        case 'B':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.y == -1)
                    {
                        cubeBlock->Rotate(Vector3{ 0, sign * 90, 0 });
                    }
                }
                };
            break;
        case 'L':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.x == -1)
                    {
                        cubeBlock->Rotate(Vector3{ sign * 90, 0, 0 });
                    }
                }
                };
            break;
        case 'R':
            _rotateFunc = [sign](vector<shared_ptr<CubeBlock>>& cubeBlocks) {
                for (auto& cubeBlock : cubeBlocks) {
                    auto cubeBlockPos = cubeBlock->GetPosition();
                    if (cubeBlockPos.x == 1)
                    {
                        cubeBlock->Rotate(Vector3{ -sign * 90, 0, 0 });
                    }
                }
                };
            break;
        }

        _rotateFunc(blocks);
        sort(blocks.begin(), blocks.end(), [](shared_ptr<CubeBlock>& a, shared_ptr<CubeBlock>& b) {
            auto&& posA = a->GetPosition();
            auto&& posB = b->GetPosition();

            if (posA.z != posB.z)
            {
                return posA.z > posB.z;
            }
            else if (posA.y != posB.y)
            {
                return posA.y < posB.y;
            }
            else
            {
                return posA.x < posB.x;
            }
        });
    }

    void PrintUpFaceColors() const {
        int index = 0;
        for (const auto& block : blocks) {
            auto position = block->GetPosition();
            if (position.z == 1) 
            {
                for (auto& face : block->GetFaces()) {
                    if (face.GetFrontVector().z == 1)
                    {
                        putchar(face.GetColor());
                        ++index;
                        if (index % 3 == 0) printf("\n");
                    }

                }
            }
        }
    }
};



int main()
{
    int testCases;
    scanf("%d",&testCases);

    for(int testCount = 0; testCount < testCases; ++testCount)
    {
        Cube cube;
        int n;
        scanf("%d",&n);

        for(int cubeOperationCount = 0; cubeOperationCount < n; ++cubeOperationCount)
        {
            char operation[3];
            scanf("%s",operation);

            int sign;

            if(operation[1] == '-') sign = -1;
            else sign = 1;

            cube.Rotate(operation[0], sign);
        }
        cube.PrintUpFaceColors();
    }
    return 0;
}