#include "pch.h"
#include "Settings.h"

using namespace PseudoChat;

Settings::Settings():
	language(std::string("language"), Settings::Language::Default) {}
