#include "Text.h"



Text::Text(float x, float y, const std::string& content, const std::string& fontPath, unsigned int characterSize) {
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font from file: " + fontPath);
    }
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White); 
    text.setString(content);
    text.setPosition(x, y);
}
Text::Text(float x, float y, const std::string& content, unsigned int characterSize) {
    const std::string& fontPath = "resources/fonts/Info Story.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font from file: " + fontPath);
    }else 
        text.setFont(font);
    posX = x;
    posY = y;
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);
    text.setString(content);
    text.setPosition(x, y);
}


void Text::setPosition(float x, float y) {
    posX = x;
    posY = y;
    text.setPosition(x, y);
}

void Text::setContent(const std::string& content) {
    text.setString(content);
}

void Text::CenterText() {

    sf::FloatRect bounds = getLocalBounds();
    text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f); 
}



