#pragma once

#include "libs.h"

class currency
{
    enum mode : std::uint8_t { empty = 0, update = 1 };
    mode _mode;
    
    std::string _state, _code, _name;
    float _rate;

    static const std::string _delim;

    std::vector<std::string> _currencyDetails() const noexcept
    {
        return { _state, _code, _name, strExchangeRate() };
    }
    explicit currency(const std::vector<std::string>& currencyDetails)
    {
        const float exchangeRate = std::stof(currencyDetails.at(3));
        
        *this = currency(update, currencyDetails.at(0), currencyDetails.at(1), currencyDetails.at(2), exchangeRate);
    }
    
    explicit currency(const std::string& currencyDetailsLine)
    {
        const std::vector<std::string> currencyDetails = strUtils::split(currencyDetailsLine, _delim);

        *this = currency(currencyDetails);
    }
    std::string _currencyDetailsLine() const noexcept
    {
        const std::vector<std::string> currencyDetails = _currencyDetails();
        const size_t numberOfCurrencyDetails = currencyDetails.size();
        
        auto currencyDetailsLine = std::string();
        for (size_t i = 0; i < numberOfCurrencyDetails; ++i)
        {
            currencyDetailsLine += currencyDetails.at(i);

            if (i != numberOfCurrencyDetails - 1)
                currencyDetailsLine += _delim;
        }

        return currencyDetailsLine;
    }
public:
    currency(const mode mode, std::string state, std::string currencyCode, std::string currencyName, const float exchangeRate) : _mode(mode), _state(std::move(state)), _code(std::move(currencyCode)), _name(std::move(currencyName)), _rate(exchangeRate) {}
    
    bool isEmpty() const noexcept
    {
        return (_mode == empty);
    }

    std::string state() const noexcept
    {
        return _state;
    }
    
    std::string code() const noexcept
    {
        return _code;
    }
    std::string name() const noexcept
    {
        return _name;
    }

    float exchangeRate() const noexcept
    {
        return _rate;
    }
    void setExchangeRate(const float exchangeRate)
    {
        // TODO: Validate the exchange rate
        
        _rate = exchangeRate;

        // Records the modified currency object to the currency data file (`data\currency-list.txt`)
        _update();
    }

    __declspec(property(get = exchangeRate, put = setExchangeRate)) float ExchangeRate;

    std::string strExchangeRate() const noexcept
    {
        return strUtils::string(_rate);
    }
};

const std::string currency::_delim = "#//#";