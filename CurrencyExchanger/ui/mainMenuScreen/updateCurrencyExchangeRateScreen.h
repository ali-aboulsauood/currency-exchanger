#pragma once

#include "findCurrencyScreen.h"

class updateCurrencyExchangeRateScreen : protected screen
{
    static const std::string _title;
    static std::string _subtitle;
public:
    updateCurrencyExchangeRateScreen() = delete;

    static currency _findCurrency()
    {
        std::cout << "Press ENTER to be redirected to the Find Currency screen..." << '\n';

        WindowsConsole::pause('\r');

        return findCurrencyScreen::display();
    }

    static void display()
    {
        bool update = true;

        const std::vector<currency> currencies = currency::allCurrencies();

        while (update)
        {
            _renderScreenHeader(_title, _subtitle);

            std::cout << '\n';

            currency requestedCurrency = _findCurrency();

            _renderScreenHeader(_title, _subtitle);

            std::cout << '\n';

            if (requestedCurrency.isEmpty())
            {
                WindowsConsole::printFailure("UPDATE FAILED: No currency data available, or user has cancelled the operation.");

                return;
            }

            print(requestedCurrency);

            std::cout << '\n';

            bool edit = true;

            while (edit)
            {
                std::string prompt = "Please enter the new exchange rate for " + requestedCurrency.name() + " (" + requestedCurrency.code() + "): (A value of zero will return you to the main menu)";
                std::string error_prompt = "Please enter a number from 0 to " + strUtils::string(FLT_MAX) + ':';

                const float newExchangeRate = inputs::ReadNumberBetween<float>(0.f, FLT_MAX, true, prompt, error_prompt, error_prompt);

                if (newExchangeRate == 0.f)
                {
                    WindowsConsole::printFailure("UPDATE FAILED: User has cancelled the operation.");

                    return;
                }

                std::cout << '\n';

                prompt = "Are you sure you want to change the exchange rate for " + requestedCurrency.name() + " (" + requestedCurrency.code() + ") from " + requestedCurrency.strExchangeRate() + " to " + strUtils::string(newExchangeRate) + "?:";

                edit = inputs::ConsoleIn_YN(prompt);

                if (edit)
                {
                    requestedCurrency.setExchangeRate(newExchangeRate);

                    std::cout << '\n';
                    
                    WindowsConsole::printSuccess("UPDATE SUCCEEDED: The exchange rate for " + requestedCurrency.name() + " (" + requestedCurrency.code() + ") has been updated to " + requestedCurrency.strExchangeRate() + '.');

                    return;
                }
            }

            update = inputs::ConsoleIn_YN("Do you wish to update the exchange rate for another currency?");
        }
    }
};

const std::string updateCurrencyExchangeRateScreen::_title = "Currency Exchanger - Main Menu - Update Currency Exchange Rate";
std::string updateCurrencyExchangeRateScreen::_subtitle = std::string();
