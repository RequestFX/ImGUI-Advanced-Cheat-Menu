#pragma once

// Only for x64 !

#include <array>
#include <string>
#include <iterator>
#include <algorithm>

namespace Obf {

	inline std::string xor_(std::string s) {
		std::string out{};
		for (char& c : s) {
			out += c ^ (s.length() + 1) ^ 'f';
		}
		return out;
	}

	template<std::size_t S>
	struct Xor_String {
		std::array<char, S> charArr;

		inline auto operator()() {
			std::string str{};

			std::transform(charArr.begin(), charArr.end() - 1, std::back_inserter(str), [](auto const& c) {
				return c ^ S ^ 'f';
				});
			return str;
		}

		constexpr Xor_String(const char(&string)[S]) : charArr{} {
			auto it = charArr.begin();
			for (auto const& c : string) {
				*it = c ^ S ^ 'f';
				it++;
			}
		}
	};
}
#define obf(string) []() { static auto result = Obf::Xor_String<sizeof(string)/sizeof(char)>(string); return result(); }()