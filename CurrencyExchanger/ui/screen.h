#pragma once

#include "../currency.h"

#include "../libs.h"

class screen
{
protected:
    static constexpr size_t width = 188;

    static const WindowsConsoleTheme defaultTheme;

    static const std::string h_sep;

    static const std::string title_underline, underline;

    static void _renderScreenHeader(const std::string& screenTitle, const std::string& screenSubtitle = std::string(), const bool centerSubtitle = true) noexcept
    {
        WindowsConsole::setTheme(defaultTheme);
        
        WindowsConsole::clear();

        std::cout << '\n';

        const std::string screenTitle_ = strUtils::trim(screenTitle), screenSubtitle_ = strUtils::trim(screenSubtitle);

        std::cout << strUtils::underline(screenTitle, title_underline) << '\n';

        std::cout << '\n';

        if (!screenSubtitle_.empty())
        {
            if (centerSubtitle)
                std::cout << strUtils::pad(screenSubtitle_, width) << '\n';
            else
                std::cout << screenSubtitle_ << '\n';
        }
    }

public:
    screen() = delete;

    static void print(const currency& currency_) noexcept
    {
        if (currency_.isEmpty())
        {
            std::cout << "No information available." << '\n';
            return;
        }

        const std::vector<std::pair<std::string, std::string>> table
        {
            {"State", currency_.state()},
            {"Code", currency_.code()},
            {"Name", currency_.name()},
            {"Exchange Rate (USD 1)", currency_.strExchangeRate()}
        };

        std::cout << "Information regarding " << currency_.name() << ' ' << '(' << currency_.code() << ')' << ':' << '\n';

        std::cout << '\n';

        constexpr std::streamsize field_length = 55, value_length = (width - field_length + 2);

        std::cout << h_sep << '\n';

        for (const auto& row : table)
        {
            std::cout << std::setw(field_length) << std::left << "| " + row.first << "| " << std::setw(value_length) << std::left << row.second << '\n';
            std::cout << h_sep << '\n';
        }
    }
};

const WindowsConsoleTheme screen::defaultTheme = WindowsConsoleThemes::LightBlue;

const std::string screen::h_sep = strUtils::string("-", width);

const std::string screen::title_underline = "=", underline = "-";