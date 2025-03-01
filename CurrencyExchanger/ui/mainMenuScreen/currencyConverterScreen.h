#pragma once

#include "../screen.h"

class currencyConverterScreen : protected screen
{
    static const std::string _title;
    static std::string _subtitle;
public:
    currencyConverterScreen() = delete;

    static void display()
    {
        bool convert = true;

        while (convert)
        {
            if (!currency::hasCurrencies())
            {
                _subtitle = "No currency data available.";

                _renderScreenHeader(_title, _subtitle);

                return;
            }

            _subtitle = std::string();
            _renderScreenHeader(_title, _subtitle, false);

            float amount = 0.f;

            std::string prompt = "Amount to convert:";
            std::string error_prompt = "Please enter a number between 1 and " + strUtils::string(FLT_MAX);

            amount = inputs::ReadNumberBetween<float>(1, FLT_MAX, true, prompt, error_prompt, error_prompt);

            std::cout << '\n';

            // TODO: Simplify the following code
        
            auto fromCurrencyCode = std::string(), toCurrencyCode = std::string();

            prompt = std::string();
            error_prompt = "Please enter a valid character sequence:";

            prompt = "Convert from:";

            fromCurrencyCode = inputs::ConsoleIn<std::string>(prompt, error_prompt);
            currency fromCurrency = currency::getCurrencyByCode(fromCurrencyCode);

            while (fromCurrency.isEmpty())
            {
                std::cout << '\n';
            
                prompt = "There is no currency of code " + fromCurrencyCode + ". Please try again:";
            
                fromCurrencyCode = inputs::ConsoleIn<std::string>(prompt, error_prompt);
                fromCurrency = currency::getCurrencyByCode(fromCurrencyCode);
            }

            std::cout << "\n\n";

            prompt = "Convert to:";

            toCurrencyCode = inputs::ConsoleIn<std::string>(prompt, error_prompt);
            currency toCurrency = currency::getCurrencyByCode(toCurrencyCode);

            while (toCurrency.isEmpty())
            {
                std::cout << '\n';
            
                prompt = "There is no currency of code " + toCurrencyCode + ". Please try again:";
            
                toCurrencyCode = inputs::ConsoleIn<std::string>(prompt, error_prompt);
                toCurrency = currency::getCurrencyByCode(toCurrencyCode);
            }

            std::cout << "\n\n";

            std::cout << fromCurrencyCode << ' ' << amount << " = " << toCurrencyCode << ' ' << fromCurrency.convert(amount, toCurrency) << '\n';

            std::cout << '\n';

            convert = inputs::ConsoleIn_YN("Do you wish to perform another calculation?");
        }
    }
};

const std::string currencyConverterScreen::_title = "Currency Exchanger - Main Menu - Currency Converter";
std::string currencyConverterScreen::_subtitle = std::string();
