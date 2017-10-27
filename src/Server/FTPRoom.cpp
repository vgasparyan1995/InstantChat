#include "FTPRoom.h"

namespace Server {

void FTPRoom::join(FTParticipantPtr participant)
{
    m_participants.insert(participant);
    for (const auto& file : m_recentFiles) {
        participant->deliver(file);
    }
}

void FTPRoom::leave(FTParticipantPtr participant)
{
    m_participants.erase(participant);
}

void FTPRoom::deliver(const Generic::FilePackage& file)
{
    m_recentFiles.push_back(file);
    while (m_recentFiles.size() > s_maxRecentFiles) {
        m_recentFiles.pop_front();
    }
    for (auto participant : m_participants) {
        participant->deliver(file);
    }
}

} // namespace Server
