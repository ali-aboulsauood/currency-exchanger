#pragma once

#include "screen.h"

#include "../libs.h"

class menu : public screen
{
protected:
    static const std::pair<std::string, std::string> braces;
    
    static size_t _getMenuItem(const std::vector<std::string>& menuItems) noexcept
    {
        if (menuItems.empty())
            return 0;
        
        const size_t numberOfMenuItems = menuItems.size();

        const std::string prompt = "Please enter the number corresponding to the item desired:";
        const std::string error_prompt = "Please enter a valid integer between 1 and " + strUtils::string(numberOfMenuItems) + ":";

        return inputs::ReadNumberBetween<size_t>(1, numberOfMenuItems, true, prompt, error_prompt, error_prompt);
    }
    static void _displayMenu(const std::vector<std::string>& menuItems) noexcept
    {
        if (menuItems.empty())
            return;

        for (size_t i = 0; i < menuItems.size(); ++i)
            std::cout << braces.first << i + 1 << braces.second << ' ' << menuItems.at(i) << '\n';

        std::cout << '\n';
    }
public:
    menu() = delete;
};

const std::pair<std::string, std::string> braces = { "[", "]" };