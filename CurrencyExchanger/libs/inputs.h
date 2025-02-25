#pragma once

#include <algorithm>
#include <iostream>
#include <string>

class inputs
{
public:
	inputs() = delete;

	// TODO: Enforce data type restrictions for generic data types.
	
	template <typename Num> static bool isNumberBetween(const Num& n, const Num& start, const Num& end, const bool isInclusive = false)
	{
		Num start_ = std::min(start, end), end_ = std::max(start, end);

		if (isInclusive)
			return (n >= start_ && n <= end_);
		
		return (n > start_ && n < end_);
	}

	template <typename Val> static void ConsoleIn(Val& v, const std::string& prompt, const std::string& error_prompt, const bool append_newline = true)
	{
		const char& appended_char = (append_newline ? '\n' : ' ');

		std::cout << prompt << appended_char;

		std::cin >> v;

		while (std::cin.fail())
		{
			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << error_prompt << appended_char;
			std::cin >> v;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	template <> static void ConsoleIn(std::string& str, const std::string& prompt, const std::string& error_prompt, const bool append_newline)  // NOLINT(clang-diagnostic-explicit-specialization-storage-class)
	{
		const char& appended_char = (append_newline ? '\n' : ' ');

		std::cout << prompt << appended_char;

		std::getline(std::cin >> std::ws, str);

		while (std::cin.fail())
		{
			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << error_prompt << appended_char;
			std::getline(std::cin >> std::ws, str);
		}
	}

	template <typename Val> static Val ConsoleIn(const std::string& prompt, const std::string& error_prompt, bool append_newline = true)
	{
		Val v{};

		ConsoleIn(v, prompt, error_prompt, append_newline);

		return v;
	}

	template <typename Num> static void ReadNumberBetween(Num& n, const Num& start, const Num& end, bool isInclusive, const std::string& prompt, const std::string& error_prompt_1, const std::string& error_prompt_2, bool append_newline = true)
	{
		ConsoleIn(n, prompt, error_prompt_1, append_newline);

		while (!isNumberBetween(n, start, end, isInclusive))
			ConsoleIn(n, error_prompt_2, error_prompt_1, append_newline);
	}
	template <typename Num> static Num ReadNumberBetween(const Num& start, const Num& end, bool isInclusive, const std::string& prompt, const std::string& error_prompt_1, const std::string& error_prompt_2, bool append_newline = true)
	{
		Num n{};

		ReadNumberBetween(n, start, end, isInclusive, prompt, error_prompt_1, error_prompt_2, append_newline);

		return n;
	}

	static void ConsoleIn_YN(bool& b, const std::string& prompt, const std::string& error_prompt = "Please enter 'Y/y' for 'Yes' or 'N/n' for 'No'.", const bool append_newline = false) noexcept
	{
		constexpr std::pair<char, char> bool_chars = { 'Y', 'N' };
		
		char c = ConsoleIn<char>(prompt, error_prompt, append_newline);

		while (c != bool_chars.first && c != std::tolower(bool_chars.first) && c != bool_chars.second && c != std::tolower(bool_chars.second))
			c = ConsoleIn<char>(error_prompt, error_prompt, append_newline);
		
		if (c == bool_chars.first || c == std::tolower(bool_chars.first))
		{
			b = true;
			
			return;
		}
        
		if (c == bool_chars.second || c == std::tolower(bool_chars.second))
		{
			b = false;

			return;
		}

		return;
	}
	static bool ConsoleIn_YN(const std::string& prompt, const std::string& error_prompt = "Please enter 'Y/y' for 'Yes' or 'N/n' for 'No'.", const bool append_newline = false)
	{
		bool b = false;

		ConsoleIn_YN(b, prompt, error_prompt, append_newline);

		return b;
	}
	
	// TODO: Implement the functions (isDateBetween, isDateValid).
	
	/*
	static bool isDateBetween(Date& _Date, Date& StartDate, Date& EndDate, bool isInclusive = false)
	{
		return DateOperations::IsBetween(_Date, StartDate, EndDate, isInclusive);
	}
	static bool isDateValid(const unsigned short& day, const unsigned short& month, const unsigned short& year)
	{
		return DateOperations::IsValidDate(day, month, year);
	}
	*/
};

// TODO: Complete the other TODOs specified in the header.