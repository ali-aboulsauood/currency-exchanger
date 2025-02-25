#pragma once

#include <string>
#include <windows.h>

class WindowsConsoleTheme
{
    std::string _name;
    static const std::string _defaultName;
	
    WORD _foreColor, _backColor;
    static const WORD _defaultForeColor, _defaultBackColor;

    WORD _successColor, _failureColor, _warningColor;
    static const WORD _defaultSuccessColor, _defaultFailureColor, _defaultWarningColor;

public:
    explicit WindowsConsoleTheme(std::string name = _defaultName, const WORD foregroundColor = _defaultForeColor, const WORD backgroundColor = _defaultBackColor, const WORD successColor = _defaultSuccessColor, const WORD failureColor = _defaultFailureColor, const WORD warningColor = _defaultWarningColor) : _name(std::move(name)), _foreColor(foregroundColor), _backColor(backgroundColor), _successColor(successColor), _failureColor(_defaultFailureColor), _warningColor(_defaultWarningColor) {}

    std::string name() const noexcept
    {
        return _name;
    }
    WindowsConsoleTheme& setName(const std::string& name = _defaultName) noexcept
    {
        _name = name;
		
        return *this;
    }

    __declspec(property(get = name, put = setName)) std::string Name;
	
    WORD foregroundColor() const noexcept
    {
        return _foreColor;
    }
    WindowsConsoleTheme& setForegroundColor(const WORD color = _defaultForeColor) noexcept
    {
        _foreColor = color;
		
        return *this;
    }

    __declspec(property(get = foregroundColor, put = setForegroundColor)) WORD ForegroundColor;

    WORD backgroundColor() const noexcept
    {
        return _backColor;
    }
    WindowsConsoleTheme& setBackgroundColor(const WORD color = _defaultBackColor) noexcept
    {
        _backColor = color;
		
        return *this;
    }

    __declspec(property(get = backgroundColor, put = setBackgroundColor)) WORD BackgroundColor;

    WORD successColor() const noexcept
    {
        return _successColor;
    }
    WindowsConsoleTheme& setSuccessColor(const WORD color = _defaultSuccessColor) noexcept
    {
        _successColor = color;
        
        return *this;
    }

    __declspec(property(get = successColor, put = setSuccessColor)) WORD SuccessColor;

    WORD failureColor() const noexcept
    {
        return _failureColor;
    }
    WindowsConsoleTheme& setFailureColor(const WORD color = _defaultFailureColor) noexcept
    {
        _failureColor = color;
        
        return *this;
    }

    __declspec(property(get = failureColor, put = setFailureColor)) WORD FailureColor;

    WORD warningColor() const noexcept
    {
        return _warningColor;
    }
    WindowsConsoleTheme& setWarningColor(const WORD color = _defaultWarningColor) noexcept
    {
        _warningColor = color;
        
        return *this;
    }

    __declspec(property(get = warningColor, put = setWarningColor)) WORD WarningColor;

    bool operator==(const WindowsConsoleTheme& other) const noexcept
    {
        const bool sameName = _name == other._name;
        
        const bool sameForeColor = _foreColor == other._foreColor;
        const bool sameBackColor = _backColor == other._backColor;
        
        const bool sameSuccessColor = _successColor == other._successColor;
        const bool sameFailureColor = _failureColor == other._failureColor;
        const bool sameWarningColor = _warningColor == other._warningColor;

        return sameName && sameForeColor && sameBackColor && sameSuccessColor && sameFailureColor && sameWarningColor;
    }
};

const std::string WindowsConsoleTheme::_defaultName = "Windows Console Theme";

const WORD WindowsConsoleTheme::_defaultForeColor = 0x7, WindowsConsoleTheme::_defaultBackColor = 0x0;

const WORD WindowsConsoleTheme::_defaultSuccessColor = 0x2, WindowsConsoleTheme::_defaultFailureColor = 0x4, WindowsConsoleTheme::_defaultWarningColor = 0x6;

namespace WindowsConsoleThemes
{
    WindowsConsoleTheme WindowsDefault("Windows Default");

    WindowsConsoleTheme LightDefault("Light Default", 0x0, 0x7);
    WindowsConsoleTheme DarkDefault("Dark Default", 0x7, 0x0);

    WindowsConsoleTheme LightBright("Light (High Contrast)", 0x0, 0xf);
    WindowsConsoleTheme DarkBright("Dark (High Contrast)", 0xf, 0x0);

    WindowsConsoleTheme Blue("Blue", 0x7, 0x1);
    WindowsConsoleTheme BlueBright("Blue (High Contrast)", 0xf, 0x1);

    WindowsConsoleTheme LightBlue("Light Blue", 0x7, 0x9);
    WindowsConsoleTheme LightBlueBright("Light Blue (High Contrast)", 0xf, 0x9);

    WindowsConsoleTheme Green("Green", 0x7, 0x2);
    WindowsConsoleTheme GreenBright("Green (High Contrast)", 0xf, 0x2);

    WindowsConsoleTheme Hacker("Hacker", 0x2, 0x0);
    WindowsConsoleTheme HackerLight("Hacker (Light)", 0xa, 0x0);

    WindowsConsoleTheme RedAlert("Red Alert", 0xc, 0xf);

    // TODO: Implement additional themes.
}

// TODO: Complete the other TODOs specified in the header.