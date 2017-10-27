#pragma once

#include <set>
#include <memory>
#include <deque>

#include "Generic/ChatMessage.h"

namespace Server {

struct ChatParticipant
{
    virtual ~ChatParticipant() {}
    virtual void deliver(const Generic::ChatMessage& msg) = 0;
};

using ChatParticipantPtr = std::shared_ptr<ChatParticipant>;
using ChatMessageQueue = std::deque<Generic::ChatMessage>;

class ChatRoom
{
public:
    void join(ChatParticipantPtr participant);
    void leave(ChatParticipantPtr participant);
    void deliver(const Generic::ChatMessage& msg);

private:
    static const int s_maxRecentMessages = 100;

private:
    std::set<ChatParticipantPtr>    m_participants;
    ChatMessageQueue                m_recentMessages;
};

} // namespace Server
