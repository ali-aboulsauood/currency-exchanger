#pragma once

#include "../menu.h"

class findCurrencyScreen : protected menu
{
    static const std::string _title;
    static std::string _subtitle;
public:
    findCurrencyScreen() = delete;

    static void display()
    {
        bool find = true;

        const std::vector<currency> currencies = currency::allCurrencies();

        while (find)
        {
            if (currencies.empty())
            {
                _subtitle = "No currency data available.";

                _renderScreenHeader(_title, _subtitle);

                return;
            }

            _subtitle = "Find Currency by...";
            _renderScreenHeader(_title, _subtitle, false);

            std::cout << '\n';

            const std::vector<std::string> menuItems = { "Code...", "State...", "Name...", "(RETURN TO MAIN MENU)" };

            _displayMenu(menuItems);
            
            const size_t chosenMenuItem = _getMenuItem(menuItems);

            if (chosenMenuItem == menuItems.size())
                return;

            const std::string& chosenProperty = strUtils::to_lower(strUtils::r_trim(menuItems.at(chosenMenuItem - 1), "."));
            
            auto prompt = [chosenProperty]() -> std::string {
                return "Please enter the " + chosenProperty + " of the currency you wish to find:";
            };
            const std::string error_prompt = "Please enter a valid character sequence";

            std::cout << '\n';

            const std::string searchTerm = inputs::ConsoleIn<std::string>(prompt(), error_prompt);

            auto requestedCurrency = currency();
            
            switch (chosenMenuItem)
            {
            case 1:
                requestedCurrency = currency::getCurrencyByCode(searchTerm);

                break;
            case 2:
                requestedCurrency = currency::getCurrencyByState(searchTerm);

                break;
            case 3:
                requestedCurrency = currency::getCurrencyByName(searchTerm);

                break;
            default:
                throw std::invalid_argument("Invalid input for the chosen property in the Find Currency screen.");
            }

            std::cout << '\n';

            if (requestedCurrency.isEmpty())
                WindowsConsole::printFailure("Could not find a currency with a " + chosenProperty + " of " + searchTerm);  // NOLINT(performance-inefficient-string-concatenation)
            else
                print(requestedCurrency);

            std::cout << '\n';

            find = inputs::ConsoleIn_YN("Do you wish to find another currency?");
        }
    }
};

const std::string findCurrencyScreen::_title = "Currency Exchanger - Main Menu - Find Currencies";
std::string findCurrencyScreen::_subtitle = std::string();
