#pragma once

#include "libs.h"

class currency
{
    enum mode : std::uint8_t { empty = 0, update = 1 };
    mode _mode;
    
    std::string _state, _code, _name;
    float _rate;

    static const std::string _currencyDataFile;
    static const std::string _delim;

    class errors
    {
        static void logError(const std::string& errorMsg) noexcept
        {
            std::cerr << errorMsg << '\n';
        }
    public:
        static void logCurrencyDataFileNotOpen()
        {
            logError("ERROR: Failed to open the currency data file (`" + _currencyDataFile + "`).");
        }
    };

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
    
    static std::vector<currency> _loadCurrencies()
    {
        auto allCurrencies = std::vector<currency>();

        std::fstream file(_currencyDataFile, std::ios::in);

        if (file.is_open())
        {
            auto currentLine = std::string();

            while (std::getline(file, currentLine))
                allCurrencies.push_back(currency(currentLine));

            file.close();
        }
        else
            errors::logCurrencyDataFileNotOpen();
        
        return allCurrencies;
    }
    static void _saveCurrencies(const std::vector<currency>& currencies)
    {
        std::fstream file(_currencyDataFile, std::ios::out);

        if (file.is_open())
        {
            for (const currency& currency_ : currencies)
                file << currency_._currencyDetailsLine() << '\n';

            file.close();
        }
        else
            errors::logCurrencyDataFileNotOpen();
    }

    void _update() const
    {
        std::vector<currency> allCurrencies = _loadCurrencies();
        
        const currency thisCurrency = *this;
        
        for (currency& currency_ : allCurrencies)
        {
            if (thisCurrency == currency_)
            {
                currency_ = thisCurrency;
                break;
            }
        }

        _saveCurrencies(allCurrencies);
    }
    
public:
    currency() : _mode(empty), _state(std::string()), _code(std::string()), _name(std::string()), _rate(0.f) {}
    
    currency(const mode mode, std::string state, std::string currencyCode, std::string currencyName, const float exchangeRate) : _mode(mode), _state(std::move(state)), _code(std::move(currencyCode)), _name(std::move(currencyName)), _rate(exchangeRate) {}
    
    bool isEmpty() const noexcept
    {
        return (_mode == empty);
    }

    std::string state() const noexcept
    {
        return _state;
    }
    std::string stateLowerCase() const noexcept
    {
        return strUtils::to_lower(_state);
    }
    
    std::string code() const noexcept
    {
        return _code;
    }
    
    std::string name() const noexcept
    {
        return _name;
    }
    std::string nameLowerCase() const noexcept
    {
        return strUtils::to_lower(_name);
    }

    float exchangeRate() const noexcept
    {
        return _rate;
    }
    void setExchangeRate(const float exchangeRate)
    {
        _rate = exchangeRate;

        // Records the modified currency object to the currency data file (`data\currency-list.txt`)
        _update();
    }

    __declspec(property(get = exchangeRate, put = setExchangeRate)) float ExchangeRate;

    std::string strExchangeRate() const noexcept
    {
        return strUtils::string(_rate);
    }

    static std::vector<currency> allCurrencies()
    {
        return _loadCurrencies();
    }
    static bool hasCurrencies() noexcept
    {
        return !allCurrencies().empty();
    }

    bool operator==(const currency& other) const noexcept
    {
        return (_code == other._code);
    }

    static currency getCurrencyByState(const std::string& state) noexcept
    {
        const std::vector<currency> allCurrencies = _loadCurrencies();

        const std::string stateLowerCase = strUtils::to_lower(state);
        
        for (const currency& currency_ : allCurrencies)
        {
            if (currency_.stateLowerCase() == stateLowerCase)
                return currency_;
        }

        return {};
    }
    static currency getCurrencyByCode(const std::string& code) noexcept
    {
        const std::vector<currency> allCurrencies = _loadCurrencies();

        const std::string codeUpperCase = strUtils::to_upper(code);
        
        for (const currency& currency_ : allCurrencies)
        {
            if (currency_._code == codeUpperCase)
                return currency_;
        }

        return {};
    }
    static currency getCurrencyByName(const std::string& name) noexcept
    {
        const std::vector<currency> allCurrencies = _loadCurrencies();

        const std::string& nameLowerCase = strUtils::to_lower(name);
        
        for (const currency& currency_ : allCurrencies)
        {
            if (currency_.nameLowerCase() == nameLowerCase)
                return currency_;
        }

        return {};
    }

    float convert(const float amount, const currency& toCurrency) const noexcept
    {
        return amount * (toCurrency._rate / _rate);
    }
};

const std::string currency::_currencyDataFile = "data/currency-list.txt";
const std::string currency::_delim = "#//#";