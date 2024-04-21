#include "Screen.h"
#include "Utils.h"
Screen::Screen(int W, int H,std::string _name, bool _fromStart)
{
    WIDTH = W;
    HEIGTH = H;
    name = _name;

    window.create(sf::VideoMode(WIDTH, HEIGTH), name);


}
void Screen::Events() 
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            MouseButtonPressedEvents(event);
            break;
        case sf::Event::MouseButtonReleased:
            MouseButtonRelesedEvents(event);
            break;
        case sf::Event::MouseWheelScrolled:


            scroll += (event.mouseWheelScroll.delta > 0) ? 20 : -20;

            break;
        case sf::Event::KeyPressed:
            KeyPressedEvents(event);
        default:
            break;
        }
    }
}
void Screen::Update()
{



    Draw();
    Events();
}

void Screen::Draw()
{
    window.clear(sf::Color::Black);

    for (sf::Drawable* draweable : drawables)
    {
        window.draw(*draweable); 
    }
    window.display();
}

void Screen::AddDraweable(sf::Drawable* draweable) {

    if (dynamic_cast<Button*>(draweable) != nullptr) {
        buttons.push_back(dynamic_cast<Button*>(draweable));
    }
    drawables.push_back(draweable);
}
void Screen::MouseButtonPressedEvents(sf::Event event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i clickPixelPos = { event.mouseButton.x, event.mouseButton.y };

        for (int i = 0; i < buttons.size(); i++)
        {
            if (buttons[i]->getGlobalBounds().contains(clickPixelPos.x, clickPixelPos.y))
                buttons[i]->onClick();
        }

    }
}
void Screen::KeyPressedEvents(sf::Event event) 
{
    sf::Keyboard::Key key = event.key.code;
    if (selectedInputText != nullptr)
    {
        if (key == sf::Keyboard::BackSpace)
        {
            selectedInputText->DeleteChar();
        }
        else if (key == sf::Keyboard::Space)
        {
            selectedInputText->AddChar(' ');
        }
        else if (key == sf::Keyboard::Period)
        {
            selectedInputText->AddChar('.');
        }
        else if (key == sf::Keyboard::Tab)
        {
            selectedInputText->AddChar('.');
        }
        else
        {
            selectedInputText->AddChar(Utils::ParseKey(key));
        }
    }
}

float Screen::GetMiddleScreenX()
{
    return window.getSize().x/2;
}

bool Screen::isOpen()
{
    return window.isOpen();
}
int Screen::GetScroll()
{
    return scroll;
}
void Screen::ResetScroll()
{
    scroll = 0;
}
void Screen::RemoveDrawable(sf::Drawable* drawableToRemove)
{
    auto it = std::find(drawables.begin(), drawables.end(), drawableToRemove);
    if (it != drawables.end()) {
        drawables.erase(it); // Eliminar el Drawable de la lista
    }
}
float Screen::GetMiddleScreenY()
{
    return window.getSize().x/2;
}
void Screen::MouseButtonRelesedEvents(sf::Event event)
{
}
