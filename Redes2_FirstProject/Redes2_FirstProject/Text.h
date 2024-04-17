#pragma once
#include <SFML/Graphics.hpp>

class Text {
public:
    Text(float x, float y, const std::string& content, const std::string& fontPath, unsigned int characterSize);
    Text(float x, float y, const std::string& content, unsigned int characterSize);

    void setPosition(float x, float y);
    void setContent(const std::string& content);
    void CenterText();

    int posX;
    int posY;

    sf::Text text;
private:
    sf::Font font; 
    sf::FloatRect getLocalBounds() const { return text.getLocalBounds(); }
};

