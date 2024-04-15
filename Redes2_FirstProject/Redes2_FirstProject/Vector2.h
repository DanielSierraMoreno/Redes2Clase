#pragma once
class Vector2D {
public:
    float x, y;

    // Inicialización in-class de las direcciones
    Vector2D(float X, float Y) : x(X), y(Y) {}
    Vector2D() : x(0), y(0) {}
    bool operator<(const Vector2D& other) const
    {
        if (x < other.x)
            return true;
        if (x > other.x)
            return false;
        // Si x es igual, comparamos y
        return y < other.y;
    }
    Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D operator*(const int& other) const
    {
        return Vector2D(x * other, y * other);
    }
    bool operator!=(const Vector2D& other) const
    {
        return !(*this == other);
    }
    bool operator==(const Vector2D& other) const
    {
        return x == other.x && y == other.y;
    }
    static const Vector2D Up()
    {
        return { 0, -1 };
    }
    static const Vector2D Right() {
        return { 1,0, };
    }
    static const Vector2D Down() {
        return { 0,1, };
    }
    static const Vector2D Left(){
        return { -1,0, };
            }
    static const Vector2D UpRight(){
        return { 1,1, };
            }
    static const Vector2D UpLeft(){
        return { -1,1, };
            }
    static const Vector2D DownRight(){
        return { 1,-1, };
            }
    static const Vector2D DownLeft(){
        return { -1,-1, };
            }
    static const Vector2D None(){
        return { -1,-1, };
            }
};



