#pragma once

#include "ui/mainMenuScreen/listCurrenciesScreen.h"

#include "menu.h"

class mainMenuScreen : protected menu
{
    static const std::string _title;
    static std::string _subtitle;

    static std::vector<std::string> _menuItems;

    static void _returnToMainMenu() noexcept
    {
        std::cout << "Press the RETURN key to return to the " << _title << '.' << '\n';

        WindowsConsole::pause('\r');

        display();
    }

    static void _displayListCurrencies() noexcept
    {
        listCurrenciesScreen::display();

        std::cout << '\n';

        _returnToMainMenu();
    }
    static void _displayFindCurrency() noexcept
    {
        // findCurrency::display();

        std::cout << '\n';

        _returnToMainMenu();
    }
    static void _displayUpdateCurrencyExchangeRate() noexcept
    {
        // updateCurrencyRate::display();

        std::cout << '\n';

        _returnToMainMenu();
    }
    static void _displayCurrencyCalculator() noexcept
    {
        // currencyCalculator::display();

        std::cout << '\n';

        _returnToMainMenu();
    }
    [[noreturn]] static void _exit() noexcept
    {
        WindowsConsole::exit();
    }

    static void _displayMenuItem(const size_t menuItem)
    {
        switch (menuItem)
        {
        case 1:
            _displayListCurrencies();

            return;
        case 2:
            _displayFindCurrency();

            return;
        case 3:
            _displayUpdateCurrencyExchangeRate();

            return;
        case 4:
            _displayCurrencyCalculator();

            return;
        case 5:
            _exit();

        default:
            throw std::invalid_argument("Invalid input for the chosen Main Menu item.");
        }
    }
public:
    mainMenuScreen() = delete;

    static void display()
    {
        _renderScreenHeader(_title, _subtitle);

        std::cout << '\n';

        _displayMenu(_menuItems);

        _displayMenuItem(_getMenuItem(_menuItems));
    }
};

const std::string mainMenuScreen::_title = "Currency Exchanger - Main Menu";
std::string mainMenuScreen::_subtitle = std::string();

std::vector<std::string> mainMenuScreen::_menuItems
{
    "List Currencies",
    "Find Currency...",
    "Update Currency Exchange Rate...",
    "Currency Calculator...",
    "EXIT"
};
