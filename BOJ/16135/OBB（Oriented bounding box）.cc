#include <iostream>
#include <vector>

using namespace std;

struct Vector2 {
	double x;
	double y;
};

struct Rect {
	Vector2 points[4];
};

double dot(Vector2& a, Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

int main()
{
	Rect a, b;

	for (int i = 0; i < 4; ++i)
	{
		cin >> a.points[i].x >> a.points[i].y;
	}

	for (int i = 0; i < 4; ++i)
	{
		cin >> b.points[i].x >> b.points[i].y;
	}

	Vector2 mA = { (a.points[0].x + a.points[2].x), (a.points[0].y + a.points[2].y)};
	Vector2 mB = { (b.points[0].x + b.points[2].x), (b.points[0].y + b.points[2].y) };

	Vector2 d = { mB.x - mA.x , mB.y - mA.y };

	Vector2 a1 = { (a.points[1].x - a.points[0].x), (a.points[1].y - a.points[0].y) };
	Vector2 a2 = { (a.points[2].x - a.points[1].x), (a.points[2].y - a.points[1].y)};

	Vector2 b1 = { (b.points[1].x - b.points[0].x), (b.points[1].y - b.points[0].y) };
	Vector2 b2 = { (b.points[2].x - b.points[1].x), (b.points[2].y - b.points[1].y) };

	vector<Vector2> vectors = { a1,a2,b1,b2 };

	bool result = true;

	for (Vector2& u : vectors)
	{
		if (abs(dot(d, u)) >= abs(dot(a1, u)) + abs(dot(a2, u)) + abs(dot(b1, u)) + abs(dot(b2, u)))
		{
			result = false;
			break;
		}
	}

	cout << (result ? 1 : 0) << endl;

	return 0;
}