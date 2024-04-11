#pragma once
class Vector2D
{
private:

public:
	float x, y;

	Vector2D(float X, float Y){x = X; y = Y;}
    Vector2D() {};
    bool operator<(const Vector2D& other) const
    {
        if (x < other.x)
            return true;
        if (x > other.x)
            return false;
        // Si x es igual, comparamos y
        return y < other.y;
    }
    bool operator==(const Vector2D& other) const
    {
        return x == other.x && y == other.y;
    }
};

