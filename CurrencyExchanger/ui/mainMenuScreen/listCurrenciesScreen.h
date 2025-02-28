#pragma once

#include "../screen.h"

class listCurrenciesScreen : protected screen
{
    static const std::string _title;
    static std::string _subtitle;

    static const std::array<std::string, 4> _columnTitles;
    static const std::array<std::streamsize, 4> _columnWidths;

    static void _renderTableHeaderRow()
    {
       for (size_t i = 0; i < _columnWidths.size(); ++i)
           std::cout << std::left << std::setw(_columnWidths.at(i)) << ("| " + _columnTitles.at(i));

        std::cout << '\n';
    }
    static void _renderTableRow(const currency& currency_)
    {
        if (currency_.isEmpty())
            return;

        std::cout << std::left << std::setw(_columnWidths.at(0)) << ("| " + currency_.state());
        std::cout << std::left << std::setw(_columnWidths.at(1)) << ("| " + currency_.code());
        std::cout << std::left << std::setw(_columnWidths.at(2)) << ("| " + currency_.name());
        std::cout << std::left << std::setw(_columnWidths.at(3)) << ("| " + currency_.strExchangeRate());

        std::cout << '\n';
    }
    
public:
    listCurrenciesScreen() = delete;

    static void display()
    {
        const std::vector<currency> currencies = currency::allCurrencies();

        if (currencies.empty())
        {
            _subtitle = "No currency data available.";

            _renderScreenHeader(_title, _subtitle);
            return;
        }

        _subtitle.clear();

        _renderScreenHeader(_title, _subtitle);

        std::cout << '\n' << "NOTE: Exchange Rates are relative to the United States Dollar (USD)" << '\n';

        std::cout << '\n' << h_sep << '\n';

        _renderTableHeaderRow();

        std::cout << h_sep << '\n';
        
        for (const currency& currency_ : currencies)
            _renderTableRow(currency_);

        std::cout << h_sep << '\n';
    }
};

const std::string listCurrenciesScreen::_title = "Currency Exchanger - Main Menu - List Currencies";
std::string listCurrenciesScreen::_subtitle = std::string();

const std::array<std::string, 4> listCurrenciesScreen::_columnTitles = { "State", "Code", "Name", "Rate" };
const std::array<std::streamsize, 4> listCurrenciesScreen::_columnWidths = { 84, 10, 84, 10 };