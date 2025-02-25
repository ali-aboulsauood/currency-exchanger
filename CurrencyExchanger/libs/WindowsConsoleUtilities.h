#pragma once

#include <conio.h>
#include <functional>
#include <mutex>
#include <windows.h>

#include "WindowsConsoleTheme.h"

// TODO: Implement more features.

class WindowsConsole
{
	static WindowsConsoleTheme _currentTheme;
	
public:
	WindowsConsole() = delete;
	
	static void clear() noexcept
	{
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		
		const DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
		
		constexpr COORD topLeft = { 0, 0 };
		SetConsoleCursorPosition(hConsole, topLeft);
		
		DWORD charsWritten;
		FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &charsWritten);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, topLeft, &charsWritten);
		
		SetConsoleCursorPosition(hConsole, topLeft);
	}
	static std::function<void()> cls;
	static std::function<void()> clr;
	
	static void setForegroundColor(const WORD color) noexcept
	{
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE)
			return;
		
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
			return;
		
		SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xF0) | color);
	}
	static void setBackgroundColor(const WORD color) noexcept
	{
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE)
			return;
		
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
			return;
		
		SetConsoleTextAttribute(hConsole, static_cast<WORD>((csbi.wAttributes & 0x0F) | color << 4));
	}
	static void setColors(const WORD foreColor, const WORD backColor) noexcept
	{
		// TODO: Improve the function definition.
		
		setForegroundColor(foreColor);
		setBackgroundColor(backColor);
	}

	static WindowsConsoleTheme getTheme() noexcept
	{
		return _currentTheme;
	}
	
	static void setTheme(const WindowsConsoleTheme& theme = WindowsConsoleThemes::WindowsDefault) noexcept
	{
		_currentTheme = theme;
		
		setColors(theme.ForegroundColor, theme.BackgroundColor);
	}
	static void setLightTheme() noexcept
	{
		_currentTheme = WindowsConsoleThemes::LightDefault;
		
		setTheme(WindowsConsoleThemes::LightDefault);
	}
	static void setDarkTheme() noexcept
	{
		_currentTheme = WindowsConsoleThemes::DarkDefault;
		
		setTheme(WindowsConsoleThemes::DarkDefault);
	}

	template<typename T> static void print(const T& val, const WORD color = _currentTheme.ForegroundColor, const bool appendNewLine = true, const bool appendBell = false) noexcept
	{
		const WORD prevColor = _currentTheme.ForegroundColor;
		
		setForegroundColor(color);
		
		std::cout << val;
		
		if (appendNewLine)
			std::cout << '\n';

		if (appendBell)
			std::cout << '\a';

		setForegroundColor(prevColor);
	}
	
	static void printSuccess(const std::string& msg, const bool appendNewLine = true, const bool appendBell = false) noexcept
	{
		print(msg, _currentTheme.SuccessColor, appendNewLine, appendBell);
	}
	static void printFailure(const std::string& msg, const bool appendNewLine = true, const bool appendBell = true) noexcept
	{
		print(msg, _currentTheme.FailureColor, appendNewLine, appendBell);
	}
	static void printWarning(const std::string& msg, const bool appendNewLine = true, const bool appendBell = true) noexcept
	{
		print(msg, _currentTheme.WarningColor, appendNewLine, appendBell);
	}

	static void reset(const bool clear_ = true, const bool resetCursorPosition = true) noexcept
	{
		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE)
			return;

		if (clear_)
			clear();
		
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
			return;
		
		SetConsoleTextAttribute(hConsole, csbi.wAttributes);

		if (resetCursorPosition)
		{
			constexpr COORD topLeft = { 0, 0 };
			SetConsoleCursorPosition(hConsole, topLeft);
		}
	}

	static void pause(const char resumeKey = 0) noexcept
	{
		if (resumeKey == 0)
			_getch();
		else
		{
			char pressedKey;
			do
			{
				pressedKey = static_cast<char>(_getch());
			} while (pressedKey != resumeKey);
		}
	}

	[[noreturn]] static void exit(const int exit_code = EXIT_SUCCESS) noexcept
	{
		static std::mutex exit_mutex;

		std::lock_guard<std::mutex> lock(exit_mutex);

		ExitProcess(exit_code);
	}
	static std::function<void(int)> quit;
	static std::function<void(int)> terminate;
};

WindowsConsoleTheme WindowsConsole::_currentTheme = WindowsConsoleThemes::WindowsDefault;

std::function<void()> WindowsConsole::cls = clear;
std::function<void()> WindowsConsole::clr = clear;

std::function<void(int)> WindowsConsole::quit = exit;
std::function<void(int)> WindowsConsole::terminate = exit;

// TODO: Complete the other TODOs specified in the header.