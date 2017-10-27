#pragma once

#include <gtest/gtest.h>
#include <Generic/ChatMessage.h>
#include <Generic/ChatMessage.cpp>

namespace Generic {

class ChatMessageTest : public ::testing::Test
{
protected:
    ChatMessage* object;

    virtual void SetUp()
    {
        object = new ChatMessage();
    }

    virtual void TearDown()
    {
        delete object;
        object = nullptr;
    }
};

TEST_F(ChatMessageTest, InitialState)
{
    auto pData = object->getRawData();
    ByteArray arr(pData, ChatMessage::s_headerSize);
    for (auto i = 0; i < ChatMessage::s_headerSize; ++i) {
        EXPECT_EQ(arr[i], pData[i]);
    }
}

TEST_F(ChatMessageTest, SettersAndGetters)
{
    const std::string sender("Alice");
    const std::string text("Hello World");
    object->setSender(sender);
    object->setText(text);
    EXPECT_EQ(sender, object->getSender());
    EXPECT_EQ(text, object->getText());
}

TEST_F(ChatMessageTest, EncodeAndLength)
{
    const std::string sender("Alice");
    const std::string text("Hello World");
    object->setSender(sender);
    object->setText(text);
    object->encode();
    const auto expectedLength = 2 * sizeof(uint32_t) + sender.size() + text.size();
    EXPECT_EQ(object->getLength(), expectedLength);
}

TEST_F(ChatMessageTest, Decode)
{
    const std::string sender("Alice");
    const std::string text("Hello World");
    object->setSender(sender);
    object->setText(text);
    object->encode();
    const auto length = object->getLength();
    object->setSender("");
    object->setText("");
    EXPECT_NE(sender, object->getSender());
    EXPECT_NE(text, object->getText());
    object->decode();
    EXPECT_EQ(sender, object->getSender());
    EXPECT_EQ(text, object->getText());
    EXPECT_EQ(length, object->getLength());
}

} // namespace Generic
