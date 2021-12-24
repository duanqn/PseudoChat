#include "pch.h"

#include "Message.hpp"

#include <cstdint>
#include <string>

TEST(TestMessageField, Construction) {
    PseudoChat::MessageField<int32_t> intField;
    PseudoChat::MessageField<uint32_t> uintField;
    PseudoChat::MessageField<std::string> stringField;
    PseudoChat::MessageField<std::wstring> wstringField;
}

TEST(TestMessageField, getset) {
    PseudoChat::MessageField<int32_t> intField;
    PseudoChat::MessageField<unsigned long long> ulonglongField;
    PseudoChat::MessageField<std::string> stringField;
    PseudoChat::MessageField<std::wstring> wstringField;

    intField.set(5);
    EXPECT_EQ(5, intField.get());

    ulonglongField.set(0xDEADBEEF000DEADBULL);
    EXPECT_EQ(0xDEADBEEF000DEADBULL, ulonglongField.get());

    stringField.set("Hello, world!\n");
    EXPECT_EQ(std::string("Hello, world!\n"), stringField.get());

    wstringField.set(L"测试行为");
    EXPECT_EQ(std::wstring(L"测试行为"), wstringField.get());
}

TEST(TestMessageField, length) {
    PseudoChat::MessageField<int32_t> intField;
    PseudoChat::MessageField<uint32_t> uintField;
    PseudoChat::MessageField<std::string> stringField;
    PseudoChat::MessageField<std::wstring> wstringField;
    EXPECT_EQ(intField.length(), sizeof(decltype(intField)::type));
    EXPECT_EQ(uintField.length(), sizeof(decltype(uintField)::type));
    EXPECT_EQ(stringField.length(), 0);
    EXPECT_EQ(wstringField.length(), 0);
}
