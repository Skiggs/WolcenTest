#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<unordered_map>
#include<cmath>

using namespace std;

#define PI 3.14159265

struct Vec2 {

    float  x;
    float  y;

    Vec2(float s = float(0.0)) :
        x(s), y(s) {}

    Vec2(float x, float y) :
        x(x), y(y) {}

    Vec2(const Vec2& v)
    {
        x = v.x;  y = v.y;
    }

    float& operator [] (int i) { return *(&x + i); }
    const float operator [] (int i) const { return *(&x + i); }

    Vec2 operator - () const 
    {
        cerr << "it worked" << endl;
        return Vec2(-x, -y);
    }

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

    friend Vec2 operator * (const float s, const Vec2& v)
    {
        return v * s;
    }

    Vec2 operator / (const float s) const {
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

    Vec2& operator /= (const float s) {
        float r = float(1.0) / s;
        *this *= r;
        return *this;
    }
};


inline
float dot(const Vec2& u, const Vec2& v) {
    return u.x * v.x + u.y * v.y;
}

inline float Clamp(float value, float Min, float Max)
{
    if (value < Min) return Min;
    else if (value > Max) return Max;
    return value;
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

inline double Distance(const Vec2& pos1, const Vec2& pos2)
{
    return sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y));
}

inline bool CheckCollision(const Vec2& pos1, const Vec2& pos2)
{
    if (Distance(pos1, pos2) < 800) return true;
    else return false;
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
    std::vector<Vec2> checkPoints;.
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
    float visionAngle = 90.0f;
    BoostDecider bstDecider;
    int checkpointProximity = 2000;
    int lastX, lastY;
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
        int thrust = 100;

        Vec2 nextCheckPointVector = Vec2(nextCheckpointX, nextCheckpointY);
        bstDecider.CheckNextCheckPoint(nextCheckpointDist, nextCheckPointVector);
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (nextCheckpointAngle >= -1 && nextCheckpointAngle <= 1)
        {
            if (bstDecider.isBoostableCheckPoint(nextCheckPointVector, nextCheckpointDist))
            {
                cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
            }

            else if (nextCheckpointDist < checkpointProximity)
            {
                thrust *= nextCheckpointDist / checkpointProximity;
            }
        }


        else if (nextCheckpointAngle <= -1 || nextCheckpointAngle >= 1)
        {
            Vec2 targetDirection(nextCheckpointX - x, nextCheckpointY - y);
            targetDirection = normalize(targetDirection);

            Vec2 currentDirection = rotate(targetDirection, -nextCheckpointAngle);
            currentDirection = normalize(currentDirection);

            Vec2 displacement = targetDirection - currentDirection;
            displacement = normalize(displacement);

            nextCheckpointX += displacement.x * 100;
            nextCheckpointY += displacement.y * 100;

            // 2. Slowing Down ( angle )
            if (nextCheckpointAngle <= -90 || nextCheckpointAngle >= 90)
            {
                thrust = 0;
                Vec2 podPosition(x, y);
                Vec2 bossPodPosition(opponentX, opponentY);
                if (CheckCollision(podPosition, bossPodPosition))
                {
                    if (nextCheckpointAngle < -90)
                    {
                        nextCheckPointVector = rotate(nextCheckPointVector, -nextCheckpointAngle);
                    }
                    else
                    {
                        nextCheckPointVector = rotate(nextCheckPointVector, nextCheckpointAngle);
                    }
                    thrust = 60;
                    nextCheckpointX = nextCheckPointVector.x;
                    nextCheckpointY = nextCheckPointVector.y;
                }
            }
            else if (nextCheckpointDist < 2000)
            {
                thrust *= (90 - abs(nextCheckpointAngle)) / (float)90;
            }

        }

        lastX = x;
        lastY = y;

        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        cout << nextCheckpointX << " " << nextCheckpointY << " " << to_string(thrust) << endl;
    }

}