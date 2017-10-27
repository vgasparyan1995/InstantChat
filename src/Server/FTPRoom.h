#pragma once

#include <set>
#include <memory>
#include <deque>

#include "Generic/FilePackage.h"

namespace Server {

struct FTParticipant
{
    virtual ~FTParticipant() {}
    virtual void deliver(const Generic::FilePackage& msg) = 0;
};

using FTParticipantPtr = std::shared_ptr<FTParticipant>;
using FilePackageQueue = std::deque<Generic::FilePackage>;

class FTPRoom
{
public:
    void join(FTParticipantPtr participant);
    void leave(FTParticipantPtr participant);
    void deliver(const Generic::FilePackage& file);

private:
    static const int s_maxRecentFiles = 100;

private:
    std::set<FTParticipantPtr>  m_participants;
    FilePackageQueue            m_recentFiles;
};

} // namespace Server
