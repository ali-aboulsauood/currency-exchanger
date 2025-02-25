#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <vector>

class strUtils
{
    static std::locale loc;
    static const std::locale default_loc;
    
    static char opposite_case(const char c)
    {
        return std::isupper(c, loc) ? std::tolower(c, loc) : std::toupper(c, loc);
    }
    
    static constexpr std::array<char, 5> vowels = { 'a', 'e', 'i', 'o', 'u' };
    static bool is_vowel(const char c, const bool is_y_vowel = false)
    {
        const char c_l = static_cast<char>(std::tolower(c));
    
        if (is_y_vowel && (c_l == 'y'))
            return true;
    
        return std::find(vowels.begin(), vowels.end(), c_l) != vowels.end();
    }
    static bool is_consonant(const char c, const bool is_y_vowel = false)
    {
        return !is_vowel(c, is_y_vowel);
    }

    static constexpr std::initializer_list<char> whitespaces = { ' ', '\t', '\n', '\v', '\f', '\r' };
    
public:
    strUtils() = delete;
    
    static std::locale current_locale() noexcept
    {
        return loc;
    }
    static void set_current_locale(const std::locale& new_locale = default_loc)
    {
        loc = new_locale;
    }
    
    static std::string current_locale_name() noexcept
    {
        return loc.name();
    }
    static void set_current_locale_name(const std::string& new_locale_name = default_loc.name())
    {
        loc = std::locale(new_locale_name);
    }
    
    static std::locale default_locale() noexcept
    {
        return default_loc;
    }
    static std::string default_locale_name() noexcept
    {
        return default_loc.name();
    }

    template<typename Number>
    static std::enable_if_t<std::is_arithmetic<Number>::value, std::string> string(const Number num, const bool trim_trailing_zeroes = true)
    {
        std::string num_ = std::to_string(num);
        
        if (trim_trailing_zeroes)
        {
            const size_t radix_point_off = num_.find('.');
        
            if (radix_point_off == std::string::npos)
                return num_;
            
            std::string num_non_int = num_.substr(radix_point_off + 1);
            num_non_int = r_trim(num_non_int, "0");
        
            num_.replace(radix_point_off + 1, std::string::npos, num_non_int);
        }

        return num_;
    }

    template<typename Number>
    static std::enable_if_t<std::is_integral<Number>::value, std::string> to_text(const Number num)
    {
        if (num < 0)
            return "Negative " + to_text(num);
        
        if (num == 0)
            return {};

        if (num >= 1 && num <= 19)
        {
            const std::string numbers[] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                                                "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

            return numbers[num - 1];
        }

        if (num >= 20 && num <= 99)
        {
            const std::string numbers[] = { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

            return trim_spaces(numbers[num / 10 - 2] + " " + to_text(num % 10));
        }

        if (num >= 100 && num <= 999)
            return trim_spaces(to_text(num / 100) + " Hundred " + to_text(num % 100));

        if (num >= 1000 && num <= 999999)
            return trim_spaces(to_text(num / 1000) + " Thousand " + to_text(num % 1000));

        if (num >= 1000000 && num <= 999999999)
            return trim_spaces(to_text(num / 1000000) + " Million " + to_text(num % 1000000));

        if (num >= 1000000000 && num <= 999999999999)
            return trim_spaces(to_text(num / 1000000000) + " Billion " + to_text(num % 1000000000));

        if (num >= 1000000000000 && num <= 999999999999999)
            return trim_spaces(to_text(num / 1000000000000) + " Trillion " + to_text(num % 1000000000000));

        if (num >= 1000000000000000 && num <= 999999999999999999)
            return trim_spaces(to_text(num / 1000000000000000) + " Quadrillion " + to_text(num % 1000000000000000));

        if (num >= 1000000000000000000 && num <= ULLONG_MAX)
            return trim_spaces(to_text(num / 1000000000000000000) + " Quintillion " + to_text(num % 1000000000000000000));

        throw std::out_of_range("The integer passed is out of range (should be between " + std::to_string(LLONG_MIN) + " and " + std::to_string(ULLONG_MAX) + ").");
    }
    
    static std::string string(const std::string& str, const size_t n = 1, const std::string& inner_sep = std::string(), const std::string& outer_sep = std::string()) noexcept
    {
        auto str_ = std::string();

        if (n == 0)
            return str_;
    
        str_ += outer_sep;
        for (size_t i = 1; i <= n; ++i)
        {
            str_ += str;
            if (i < n)
                str_ += inner_sep;
        }
        str_ += outer_sep;
    
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, const std::string&, const std::string&)> repeat;

    static std::string repeat_until(const std::string& str, const size_t target_len) noexcept
    {
        const size_t length = str.length();
        
        if (target_len <= length)
            return str;

        auto str_ = std::string();

        while (str_.length() < target_len)
            str_ += str;

        return str_.substr(0, target_len);
    }
    
    static std::string spaces(const std::streamsize n) noexcept
    {
        return string(" ", n);
    }
    static std::string tabs(const std::streamsize n) noexcept
    {
        return string("\t", n);
    }
    static std::string newlines(const std::streamsize n) noexcept
    {
        return string("\n", n);
    }
    static std::function<std::string(std::streamsize)> line_feeds;

    static std::string underline(const std::string& str, const std::string& underline = "-") noexcept
    {
        return str + '\n' + repeat_until(underline, str.length());
    }
    
    static std::string to_upper(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        
        if (str.empty())
            return str_;
        
        const size_t length = str.length();
        
        const size_t len_ = (len == std::string::npos ? length : len);
        
        size_t count = 0;
        for (size_t i = 0; i < length; ++i)
        {
            if (i >= start_off && count < len_)
            {
                str_.push_back(std::toupper(str.at(i), loc));
                ++count;
            }
            else
                str_.push_back(str.at(i));
        }
        
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, size_t)> upper;
    static std::function<std::string(const std::string&, size_t, size_t)> uppercase;
    static std::function<std::string(const std::string&, size_t, size_t)> to_uppercase;
    
    static std::string to_lower(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        
        if (str.empty())
            return str_;
        
        const size_t length = str.length();
        
        const size_t len_ = (len == std::string::npos ? length : len);
        
        size_t count = 0;
        for (size_t i = 0; i < length; ++i)
        {
            if (i >= start_off && count < len_)
            {
                str_.push_back(std::tolower(str.at(i), loc));
                ++count;
            }
            else
                str_.push_back(str.at(i));
        }
        
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, size_t)> lower;
    static std::function<std::string(const std::string&, size_t, size_t)> lowercase;
    static std::function<std::string(const std::string&, size_t, size_t)> to_lowercase;
    static std::function<std::string(const std::string&, size_t, size_t)> casefold;
    
    static std::string swap_case(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        
        if (str.empty())
            return str_;
        
        const size_t length = str.length();
        
        const size_t len_ = (len == std::string::npos ? length : len);
        
        size_t count = 0;
        for (size_t i = 0; i < length; ++i)
        {
            if (i >= start_off && count < len_)
            {
                str_.push_back(opposite_case(str.at(i)));
                ++count;
            }
            else
                str_.push_back(str.at(i));
        }
        
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, size_t)> swapcase;
    
    static bool is_upper(const std::string& str, const bool ignore_non_cased = true, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return false;

        auto str_ = str.substr(start_off, len);

		if (ignore_non_cased)
		{
		    str_ = remove_non_cased(str_);
		    if (str_.empty())
		        return false;
		}

        const auto loc_ = loc;
        auto isupper_ = [&loc_](const char c) { return std::isupper(c, loc_); };
        
        return std::all_of(str_.begin(), str_.end(), isupper_);
    }
	static std::function<bool(const std::string&, bool, size_t, size_t)> is_uppercase;
    static std::function<bool(const std::string&, bool, size_t, size_t)> isupper;

    static bool has_upper(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return false;

        auto str_ = str.substr(start_off, len);

        const auto loc_ = loc;
        auto isupper_ = [&loc_](const char c) { return std::isupper(c, loc_); };
        
        return std::any_of(str_.begin(), str_.end(), isupper_);
    }
    static std::function<bool(const std::string&, size_t, size_t)> has_uppercase;
    static std::function<bool(const std::string&, size_t, size_t)> contains_upper;

    static bool no_upper(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        return !has_upper(str, start_off, len);
    }
    static std::function<bool(const std::string&, size_t, size_t)> no_uppercase;
    
    static bool is_lower(const std::string& str, const bool ignore_non_cased = true, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return false;

        auto str_ = str.substr(start_off, len);

        if (ignore_non_cased)
        {
            str_ = remove_non_cased(str_);
            if (str_.empty())
                return false;
        }

        const auto loc_ = loc;
        auto islower_ = [&loc_](const char c) { return std::islower(c, loc_); };
        
        return std::find_if(str_.begin(), str_.end(), islower_) != str_.end();
    }
    static std::function<bool(const std::string&, bool, size_t, size_t)> is_lowercase;
    static std::function<bool(const std::string&, bool, size_t, size_t)> islower;

    static bool has_lower(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return false;

        auto str_ = str.substr(start_off, len);

        const auto loc_ = loc;
        auto islower_ = [&loc_](const char c) { return std::islower(c, loc_); };
        
        return std::any_of(str_.begin(), str_.end(), islower_);
    }
    static std::function<bool(const std::string&, size_t, size_t)> has_lowercase;
    static std::function<bool(const std::string&, size_t, size_t)> contains_lower;

    static bool no_lower(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        return !has_upper(str, start_off, len);
    }
    static std::function<bool(const std::string&, size_t, size_t)> no_lowercase;
    
    static size_t upper_count(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return 0;
        
        auto str_ = str.substr(start_off, len);
        
        const auto loc_ = loc;
        auto isupper_ = [&loc_](const char c) { return std::isupper(c, loc_); };
        
        return std::count_if(str_.begin(), str_.end(), isupper_);
    }
    static std::function<size_t(const std::string&, size_t, size_t)> uppercase_count;
    
    static size_t lower_count(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return 0;
        
        auto str_ = str.substr(start_off, len);
    
        const auto loc_ = loc;
        auto islower_ = [&loc_](const char c) { return std::islower(c, loc_); };
        
        return std::count_if(str_.begin(), str_.end(), islower_);
    }
    static std::function<size_t(const std::string&, size_t, size_t)> lowercase_count;
    
    static std::string capitalize(const std::string& str, const bool to_lower_rest = true, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        
        if (str.empty())
            return str_;
        
        str_ = str.substr(start_off, len);
        
        if (to_lower_rest)
            str_ = to_lower(str_);
        
        str_.front() = std::toupper(str_.front(), loc);
    
        return str_;
    }
    static std::string uncapitalize(const std::string& str, const bool to_upper_rest = false, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        
        if (str.empty())
            return str_;
        
        str_ = str.substr(start_off, len);
        
        if (to_upper_rest)
            str_ = to_upper(str_);
        
        str_.front() = std::tolower(str_.front(), loc);
        
        return str_;
    }

    static std::string l_trim(const std::string& str, const std::string& chars = " ") noexcept
    {
        if (str.empty())
            return str;
        
        const auto chars_ = (chars == " " ? std::string(whitespaces) : chars);

        const size_t start_pos = str.find_first_not_of(chars_);

        return str.substr(start_pos);
    }
    static std::function<std::string(const std::string&, const std::string&)> ltrim;
    static std::function<std::string(const std::string&, const std::string&)> l_strip;
    static std::function<std::string(const std::string&, const std::string&)> lstrip;
    static std::function<std::string(const std::string&, const std::string&)> trim_leading;

    static std::string trim_leading_spaces(const std::string& str)
    {
        return l_trim(str);
    }

    static std::string r_trim(const std::string& str, const std::string& chars = " ") noexcept
    {
        if (str.empty())
            return str;

        const auto chars_ = (chars == " " ? std::string(whitespaces) : chars);

        const size_t end_pos = str.find_last_not_of(chars_);

        return str.substr(0, end_pos + 1);
    }
    static std::function<std::string(const std::string&, const std::string&)> rtrim;
    static std::function<std::string(const std::string&, const std::string&)> r_strip;
    static std::function<std::string(const std::string&, const std::string&)> rstrip;
    static std::function<std::string(const std::string&, const std::string&)> trim_trailing;

    static std::string trim_trailing_spaces(const std::string& str)
    {
        return r_trim(str);
    }

    static std::string trim(const std::string& str, const std::string& chars = " ")
    {
        return r_trim(l_trim(str, chars), chars);
    }
    static std::function<std::string(const std::string&, const std::string&)> strip;
    static std::function<std::string(const std::string&, const std::string&)> trim_all;
    static std::function<std::string(const std::string&, const std::string&)> strip_all;

    static std::string trim_spaces(const std::string& str)
    {
        return trim_trailing_spaces(trim_leading_spaces(str));
    }

    static std::string l_pad(const std::string& str, const size_t target_len, const std::string& pad_str = " ", const bool shrink_to_target_len = false) noexcept
    {
        const size_t length = str.length();
        
        if (target_len <= length || pad_str.empty())
            return str;
        
        auto str_ = str;
        
        while (str_.length() < target_len)
            str_ = pad_str + str_;  // NOLINT(performance-inefficient-string-concatenation)

        if (shrink_to_target_len)
            str_.resize(target_len);
        
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> lpad;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> l_just;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> ljust;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> justify_left;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> pad_left;

    static std::string pad_with_leading_spaces(const std::string& str, const size_t target_len) noexcept
    {
        return l_pad(str, target_len);
    }
    static std::function<std::string(const std::string&, size_t)> justify_with_leading_spaces;

    static std::string r_pad(const std::string& str, const size_t target_len, const std::string& pad_str = " ", const bool shrink_to_target_len = false) noexcept
    {
        const size_t length = str.length();
        
        if (target_len <= length || pad_str.empty())
            return str;
        
        auto str_ = str;
        
        while (str_.length() < target_len)
            str_ += pad_str;

        if (shrink_to_target_len)
            str_.resize(target_len);
        
        return str_;
    }
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> rpad;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> r_just;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> rjust;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> justify_right;
    static std::function<std::string(const std::string&, size_t, const std::string&, bool)> pad_right;

    static std::string pad_with_trailing_spaces(const std::string& str, const size_t target_len) noexcept
    {
        return r_pad(str, target_len);
    }
    static std::function<std::string(const std::string&, size_t)> justify_with_trailing_spaces;

    static std::string pad(const std::string& str, const size_t target_len, const std::string& pad_str = " ") noexcept
    {
        const size_t length = str.length();
        
        if (target_len <= length || pad_str.empty())
            return str;
        
        auto str_ = str;
        
        while (str_.length() < target_len)
        {
            str_ = pad_str + str_;  // NOLINT(performance-inefficient-string-concatenation)
            str_ += pad_str;
        }

        return str_;
    }
    static std::function<std::string(const std::string&, size_t, const std::string&)> justify;
    static std::function<std::string(const std::string&, size_t, const std::string&)> center;

    static std::string zfill(const std::string& str, const size_t target_len) noexcept
    {
        return l_pad(str, target_len, "0");
    }

    static std::vector<std::string> chars_of(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        auto str_ = std::string();
        auto chars_ = std::vector<std::string>();
    
        if (str.empty())
            return chars_;

        str_ = str.substr(start_off, len);

        for (const char& c : str_)
            chars_.emplace_back(1, c);

        return chars_;
    }

    static std::string reverse(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        std::string str_ = str;

        const auto begin = str_.begin() + static_cast<long long>(start_off);  // NOLINT(bugprone-narrowing-conversions)
        const auto end = begin + static_cast<long long>(len == std::string::npos ? str_.length() : len);  // NOLINT(bugprone-narrowing-conversions)

        std::reverse(begin, end);

        return str_;
    }
    static bool is_palindrome(const std::string& str, const size_t start_off = 0, const size_t len = std::string::npos)
    {
        if (str.empty())
            return true;

        const std::string str_ = str.substr(start_off, len);

        return str_ == reverse(str_);
    }
    
    static std::vector<std::string> split(const std::string& str, const std::string& delim = " ", const size_t max_split = std::string::npos)
    {
        auto substrs = std::vector<std::string>();
        
        size_t start = 0, end = 0;
        
        size_t splits = 0;
        
        auto is_whitespace = [](const char c)
        {
            return std::isspace(c, loc);
        };

        if (delim == " ")
        {
            while (end < str.length() && (max_split == std::string::npos || splits < max_split))
            {
                while (start < str.length() && is_whitespace(str.at(start)))
                    ++start;
                
                end = start;
                
                while (end < str.length() && !is_whitespace(str.at(end)))
                    ++end;
                
                if (start < end)
                {
                    substrs.push_back(str.substr(start, end - start));
                    ++splits;
                }
                
                start = end;
            }
            if (start < str.length())
            {
                substrs.push_back(str.substr(start));
            }
        }
        else
        {
            while ((end = str.find(delim, start)) != std::string::npos && (max_split == std::string::npos || splits < max_split))
            {
                substrs.push_back(str.substr(start, end - start));
                start = end + delim.length();
                ++splits;
            }
            if (start < str.length()) {
                substrs.push_back(str.substr(start));
            }
        }

        return substrs;
    }

	static std::string remove_non_cased(const std::string& str, const bool preserve_spaces = false) noexcept
	{
		auto str_ = std::string();

        if (str.empty())
            return str_;

        for (const char& c : str)
        {
            if (std::isalpha(c, loc) || (std::isspace(c, loc) && preserve_spaces))
                str_.push_back(c);
        }

        return str_;
	}
    static std::function<std::string(const std::string&, bool)> remove_non_alpha;
};

std::function<std::string(const std::string&, size_t, const std::string&, const std::string&)> strUtils::repeat = static_cast<std::string(*)(const std::string&, size_t, const std::string&, const std::string&)>(string);

std::locale strUtils::loc("en_US.UTF-8");
const std::locale strUtils::default_loc("en_US.UTF-8");

std::function<std::string(const std::string&, size_t, size_t)> strUtils::upper = to_upper;
std::function<std::string(const std::string&, size_t, size_t)> strUtils::uppercase = to_upper;

std::function<std::string(const std::string&, size_t, size_t)> strUtils::lower = to_lower;
std::function<std::string(const std::string&, size_t, size_t)> strUtils::lowercase = to_lower;
std::function<std::string(const std::string&, size_t, size_t)> strUtils::casefold = to_lower;

std::function<std::string(const std::string&, size_t, size_t)> strUtils::swapcase = swap_case;

std::function<bool(const std::string&, bool, size_t, size_t)> strUtils::is_uppercase = is_upper;
std::function<bool(const std::string&, bool, size_t, size_t)> strUtils::isupper = is_upper;

std::function<bool(const std::string&, bool, size_t, size_t)> strUtils::is_lowercase = is_lower;
std::function<bool(const std::string&, bool, size_t, size_t)> strUtils::islower = is_lower;

std::function<size_t(const std::string&, size_t, size_t)> strUtils::uppercase_count = upper_count;
std::function<size_t(const std::string&, size_t, size_t)> strUtils::lowercase_count = lower_count;