#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"
#include "Button.h"
class Screen;
class InputText
{
public:
    InputText(float x, float y, const std::string& content,Screen* screen);
    Text* text;
    Button* background;
    void AddDraweable();
    void StartTyping();
    void DeleteChar();
    void AddChar(char c);
    std::string stringContent;
    std::string extraStringContent = "_";
    std::string startingString;
    Screen* currentScreen;
    void SetSelected();
    void UnSelect();
    void UpdateTextContent(bool selected);

};

