#include "Utils.h"
#include "pch.h"

#include <string>
#include <regex>
#include <utility>

winrt::hstring processNewMsg(winrt::hstring const& s) {
	std::wstring res;
	std::wstring temp(s.c_str());
	res.reserve(temp.size());

	std::wstring* in = &temp;
	std::wstring* out = &res;

	// 1. Replace newline characters to \n
	std::wregex newline_rn(L"\r\n");
	std::regex_replace(std::back_inserter(*out), in->begin(), in->end(), newline_rn, L"\n");
	std::swap(in, out);

	out->clear();
	std::wregex newline_r(L"\r");
	std::regex_replace(std::back_inserter(*out), in->begin(), in->end(), newline_r, L"\n");
	std::swap(in, out);

	// 2. Remove trailing newlines
	auto rit = in->rbegin();
	while (rit != in->rend()) {
		if (*rit != L'\n') {
			break;
		}
		++rit;
	}

	in->resize(in->rend() - rit);

	return winrt::hstring(std::move(*in));
}
