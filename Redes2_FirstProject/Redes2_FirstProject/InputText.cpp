#include "InputText.h"
#include "Screen.h"
InputText::InputText(float x, float y, const std::string& content, Screen* screen)
{
	stringContent = "";
	startingString = content;
	currentScreen = screen;
	background = new Button(x, y, TextureManager::getInstance().buttonTexture);
	background->scale(1.5, 0.20f);
	background->CenterPivot();
	background->setColor(sf::Color(0,255,0,120));
	text = new Text(background->GetLeftPivotX() + 5, background->GetMiddlePosY() - 10, "", 20);
	text->text.setOrigin(0,0.5);

	background->AddOnClickListener([this]() {
		StartTyping();
		});

	UpdateTextContent(false);
}

void InputText::AddDraweable()
{
	currentScreen->AddDraweable(background);
	currentScreen->AddDraweable(&text->text);
}
void InputText::StartTyping()
{
	if(currentScreen->selectedInputText != nullptr)
		currentScreen->selectedInputText->UnSelect();
	currentScreen->selectedInputText = this;
	SetSelected();
	UpdateTextContent(true);
}

void InputText::DeleteChar()
{
	if (!stringContent.empty()) 
		stringContent.erase(stringContent.length() - 1);
	UpdateTextContent(true);
}

void InputText::AddChar(char c)
{
	stringContent.push_back(c);
	UpdateTextContent(true);
}

void InputText::SetSelected()
{
	background->setColor(sf::Color(0, 255, 0, 35));
}

void InputText::UnSelect()
{
	background->setColor(sf::Color(0, 255, 0, 120));
	UpdateTextContent(false);

}

void InputText::UpdateTextContent(bool selected)
{
	if(selected)
	 text->setContent(startingString + stringContent + extraStringContent);
	else
		text->setContent(startingString + stringContent);
}

