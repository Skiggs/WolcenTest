#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

#define PI 3.14159265

struct Vec2
{
	float x;
	float y;


	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(const Vec2& vec) { x = vec.x; y = vec.y; }

	Vec2 operator + (const Vec2& v) const
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator - (const Vec2& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 operator * (const float s) const
	{
		return Vec2(s * x, s * y);
	}

	Vec2 operator * (const Vec2& v) const
	{
		return Vec2(x * v.x, y * v.y);
	}

	Vec2 operator / (const float s) const
	{
		float r = float(1.0) / s;
		return *this * r;
	}

	bool operator == (const Vec2& v) const
	{
		return (x == v.x) && (y == v.y);
	}

	bool operator != (const Vec2& v) const
	{
		return (x != v.x) || (y != v.y);
	}

	Vec2& operator += (const Vec2& v)
	{
		x += v.x;  y += v.y;   return *this;
	}

	Vec2& operator -= (const Vec2& v)
	{
		x -= v.x;  y -= v.y;  return *this;
	}

	Vec2& operator *= (const float s)
	{
		x *= s;  y *= s;   return *this;
	}

	Vec2& operator *= (const Vec2& v)
	{
		x *= v.x;  y *= v.y; return *this;
	}

	Vec2& operator /= (const float s)
	{
		float r = float(1.0) / s;
		*this *= r;
		return *this;
	}


};


inline
float dot(const Vec2& u, const Vec2& v) {
	return u.x * v.x + u.y * v.y;
}

inline
float length(const Vec2& v) {
	return std::sqrt(dot(v, v));
}

inline
Vec2 normalize(const Vec2& v) {
	return v / length(v);
}

inline
Vec2 rotate(const Vec2& v, float angle) {
	float radian = angle * PI / 180;
	double sinAngle = sin(radian);
	double cosAngle = cos(radian);

	return Vec2(v.x * cosAngle - v.y * sinAngle, v.y * cosAngle + v.x * sinAngle);
}


class BoostDecider
{
public:
	BoostDecider() :allchecked(false), isBoostAvailable(true), boostabeCheckPoint(0.0, 0.0) {}
	void CheckNextCheckPoint(int distance, const Vec2& targetPt)
	{
		if (!allchecked)
		{
			if (checkPoints.empty())
			{
				checkPoints.push_back(targetPt);
				maxDistance = distance;
				boostabeCheckPoint = targetPt;
			}
			else if (checkPoints.back() != targetPt)
			{
				if (checkPoints.front() == targetPt)
				{
					allchecked = true;
				}

				if (!allchecked)
				{
					checkPoints.push_back(targetPt);
					if (distance > maxDistance)
					{
						maxDistance = distance;
						boostabeCheckPoint = targetPt;
					}
				}
			}
		}
	}

	bool isBoostableCheckPoint(const Vec2& checkpt, int distance)
	{
		if (allchecked && boostavailable)
		{
			cerr << "boosted" << " " << boostabeCheckPoint.x << " " << boostabeCheckPoint.y << " " << maxDistance << " " << distance << " " << checkpt.x << " " << checkpt.y << endl;
			if (distance >= maxDistance - 600 && distance <= maxDistance + 600)
			{
				boostavailable = false;
				return true;
			}
			else return false;
		}
		return false;
	}


private:
	std::vector<Vec2> checkPoints;
	bool allchecked = false;
	bool isBoostAvailable = false;
	int maxDistance = 0;
	Vec2 boostabeCheckPoint;
	bool boostavailable = true;
	bool firstCheck = true;
};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
	int thrust = 0;
	float visionAngle = 120.0f;
	BoostDecider bstDecider;
	// game loop
	while (1) {
		int x;
		int y;
		int nextCheckpointX; // x position of the next check point
		int nextCheckpointY; // y position of the next check point
		int nextCheckpointDist; // distance to the next checkpoint
		int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
		cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
		int opponentX;
		int opponentY;
		cin >> opponentX >> opponentY; cin.ignore();

		Vec2 nextCheckPointVector = Vec2(nextCheckpointX, nextCheckpointY);
		bstDecider.CheckNextCheckPoint(nextCheckpointDist, nextCheckPointVector);
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		if (nextCheckpointAngle >= -10 && nextCheckpointAngle <= 10)
		{
			if (bstDecider.isBoostableCheckPoint(nextCheckPointVector, nextCheckpointDist))
			{
				cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
			}
		}

		if (nextCheckpointAngle >= visionAngle || nextCheckpointAngle <= -visionAngle)
		{
			thrust = 0;
			if (nextCheckpointAngle >= visionAngle) nextCheckpointAngle -= 25;
			else if (nextCheckpointAngle <= -visionAngle) nextCheckpointAngle += 25;
		}

		else
		{

			if (nextCheckpointDist < 2000)
			{
				thrust = 60;
			}
			else thrust = 100;
		}


		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"
		cout << nextCheckpointX << " " << nextCheckpointY << " " << to_string(thrust) << endl;
	}
}