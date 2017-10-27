#include "ChatRoom.h"

#include <iostream>

namespace Server {

void ChatRoom::join(ChatParticipantPtr participant)
{
    std::cout << "User joined." << std::endl;
    m_participants.insert(participant);
    for (const auto& msg : m_recentMessages) {
        participant->deliver(msg);
    }
}

void ChatRoom::leave(ChatParticipantPtr participant)
{
    std::cout << "User left." << std::endl;
    m_participants.erase(participant);
}

void ChatRoom::deliver(const Generic::ChatMessage& msg)
{
    m_recentMessages.push_back(msg);
    while (m_recentMessages.size() > s_maxRecentMessages) {
        m_recentMessages.pop_front();
    }
    for (auto participant : m_participants) {
        participant->deliver(msg);
    }
}

} // namespace Server
