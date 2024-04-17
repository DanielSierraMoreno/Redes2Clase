#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <time.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
namespace Utils {

    static char ParseKey(const sf::Keyboard::Key& k) {
        std::string ret;
        switch (k) {

        case sf::Keyboard::A:

            ret = "A";
            break;
        case sf::Keyboard::B:

            ret = "B";
            break;
        case sf::Keyboard::C:

            ret = "C";
            break;
        case sf::Keyboard::D:

            ret = "D";
            break;
        case sf::Keyboard::E:

            ret = "E";
            break;
        case sf::Keyboard::F:

            ret = "F";
            break;
        case sf::Keyboard::G:

            ret = "G";
            break;
        case sf::Keyboard::H:

            ret = "H";
            break;
        case sf::Keyboard::I:

            ret = "I";
            break;
        case sf::Keyboard::J:

            ret = "J";
            break;
        case sf::Keyboard::K:

            ret = "K";
            break;
        case sf::Keyboard::L:

            ret = "L";
            break;
        case sf::Keyboard::M:

            ret = "M";
            break;
        case sf::Keyboard::N:

            ret = "N";
            break;
        case sf::Keyboard::O:

            ret = "O";
            break;
        case sf::Keyboard::P:

            ret = "P";
            break;
        case sf::Keyboard::Q:

            ret = "Q";
            break;
        case sf::Keyboard::R:

            ret = "R";
            break;
        case sf::Keyboard::S:

            ret = "S";
            break;
        case sf::Keyboard::T:

            ret = "T";
            break;
        case sf::Keyboard::U:

            ret = "U";
            break;
        case sf::Keyboard::V:

            ret = "V";
            break;
        case sf::Keyboard::W:

            ret = "W";
            break;
        case sf::Keyboard::X:

            ret = "X";
            break;
        case sf::Keyboard::Y:

            ret = "Y";
            break;
        case sf::Keyboard::Z:

            ret = "Z";
            break;
        case sf::Keyboard::Num0:

            ret = "0";
            break;
        case sf::Keyboard::Num1:

            ret = "1";
            break;
        case sf::Keyboard::Num2:

            ret = "2";
            break;
        case sf::Keyboard::Num3:

            ret = "3";
            break;
        case sf::Keyboard::Num4:

            ret = "4";
            break;
        case sf::Keyboard::Num5:

            ret = "5";
            break;
        case sf::Keyboard::Num6:

            ret = "6";
            break;
        case sf::Keyboard::Num7:

            ret = "7";
            break;
        case sf::Keyboard::Num8:

            ret = "8";
            break;
        case sf::Keyboard::Num9:

            ret = "9";
            break;
        case sf::Keyboard::Escape:

            ret = "Escape";
            break;
        case sf::Keyboard::LControl:

            ret = "LControl";
            break;
        case sf::Keyboard::LShift:

            ret = "LShift";
            break;
        case sf::Keyboard::LAlt:

            ret = "LAlt";
            break;
        case sf::Keyboard::LSystem:

            ret = "LSystem";
            break;
        case sf::Keyboard::RControl:

            ret = "RControl";
            break;
        case sf::Keyboard::RShift:

            ret = "RShift";
            break;
        case sf::Keyboard::RAlt:

            ret = "RAlt";
            break;
        case sf::Keyboard::RSystem:

            ret = "RSystem";
            break;
        case sf::Keyboard::Menu:

            ret = "Menu";
            break;
        case sf::Keyboard::LBracket:

            ret = "LBracket";
            break;
        case sf::Keyboard::RBracket:

            ret = "RBracket";
            break;
        case sf::Keyboard::SemiColon:

            ret = "SemiColon";
            break;
        case sf::Keyboard::Comma:

            ret = ",";
            break;
        case sf::Keyboard::Period:

            ret = ".";
            break;
        case sf::Keyboard::Quote:

            ret = "Quote";
            break;
        case sf::Keyboard::Slash:

            ret = "Slash";
            break;
        case sf::Keyboard::BackSlash:

            ret = "BackSlash";
            break;
        case sf::Keyboard::Tilde:

            ret = "Tilde";
            break;
        case sf::Keyboard::Equal:

            ret = "Equal";
            break;
        case sf::Keyboard::Dash:

            ret = "Dash";
            break;
        case sf::Keyboard::Space:

            ret = "Space";
            break;
        case sf::Keyboard::Return:

            ret = "Return";
            break;
        case sf::Keyboard::BackSpace:

            ret = "BackSpace";
            break;
        case sf::Keyboard::Tab:

            ret = "Tab";
            break;
        case sf::Keyboard::PageUp:

            ret = "PageUp";
            break;
        case sf::Keyboard::PageDown:

            ret = "PageDown";
            break;
        case sf::Keyboard::End:

            ret = "End";
            break;
        case sf::Keyboard::Home:

            ret = "Home";
            break;
        case sf::Keyboard::Insert:

            ret = "Insert";
            break;
        case sf::Keyboard::Delete:

            ret = "Delete";
            break;
        case sf::Keyboard::Add:

            ret = "Add";
            break;
        case sf::Keyboard::Subtract:

            ret = "Subtract";
            break;
        case sf::Keyboard::Multiply:

            ret = "Multiply";
            break;
        case sf::Keyboard::Divide:

            ret = "Divide";
            break;
        case sf::Keyboard::Left:

            ret = "Left";
            break;
        case sf::Keyboard::Right:

            ret = "Right";
            break;
        case sf::Keyboard::Up:

            ret = "Up";
            break;
        case sf::Keyboard::Down:

            ret = "Down";
            break;
        case sf::Keyboard::Numpad0:

            ret = "0";
            break;
        case sf::Keyboard::Numpad1:

            ret = "1";
            break;
        case sf::Keyboard::Numpad2:

            ret = "2";
            break;
        case sf::Keyboard::Numpad3:

            ret = "3";
            break;
        case sf::Keyboard::Numpad4:

            ret = "4";
            break;
        case sf::Keyboard::Numpad5:

            ret = "5";
            break;
        case sf::Keyboard::Numpad6:

            ret = "6";
            break;
        case sf::Keyboard::Numpad7:

            ret = "7";
            break;
        case sf::Keyboard::Numpad8:

            ret = "8";
            break;
        case sf::Keyboard::Numpad9:

            ret = "9";
            break;
        case sf::Keyboard::F1:

            ret = "F1";
            break;
        case sf::Keyboard::F2:

            ret = "F2";
            break;
        case sf::Keyboard::F3:

            ret = "F3";
            break;
        case sf::Keyboard::F4:

            ret = "F4";
            break;
        case sf::Keyboard::F5:

            ret = "F5";
            break;
        case sf::Keyboard::F6:

            ret = "F6";
            break;
        case sf::Keyboard::F7:

            ret = "F7";
            break;
        case sf::Keyboard::F8:

            ret = "F8";
            break;
        case sf::Keyboard::F9:

            ret = "F9";
            break;
        case sf::Keyboard::F10:

            ret = "F10";
        default:
            ret = "Unknow";
            break;
        }
        return ret[0];
    }


    static std::string timestamp32ToString(uint32_t timestamp) {
        // Convert timestamp to seconds since epoch
    /*
        time_t seconds = static_cast<time_t>(timestamp);

        // Use std::put_time for thread-safe time conversion
        std::tm* timeInfo = std::gmtime(&seconds);

        // Create stringstream for formatted output
        std::stringstream ss;

        // Format the date and time according to your desired format
        ss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

        // Return the formatted string
        */
        return "tiempo que no sabemos";//ss.str();
    }
}