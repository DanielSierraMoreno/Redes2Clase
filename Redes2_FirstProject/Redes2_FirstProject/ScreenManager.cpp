#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
}

void ScreenManager::AddScreen(Screen* screen)
{
	screens.push_back(screen);
}

void ScreenManager::UpdateAllScreens()
{
	for (size_t i = 0; i < screens.size(); ++i) {
		Screen* screen = screens[i];
		if (screen != nullptr && screen->isOpen() && screen->visible) {
			screen->Update();
		}
	}
}

ScreenManager& ScreenManager::getInstance() {
	static ScreenManager instance;
	return instance;
}
