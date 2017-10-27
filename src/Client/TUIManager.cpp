#include <algorithm>
#include <cctype>
#include <iostream>

#include "ClientManager.h"
#include "ConfigManager.h"

#include "TUIManager.h"

namespace Client {

SINGLETON_DEFINITION(TUIManager)

const std::string TUIManager::s_defaultColorName("default");

void TUIManager::start()
{
    if (m_started) {
        return;
    }
    m_started = true;
    initscr();
    cbreak();
    start_color();
    registerColor(s_defaultColorName, {TextColor::WHITE, TextColor::BLACK});
    setColorDefault();
    auto gm = ClientManager::getInstance().greetingMessage();
    m_msgWriter(gm);
    const auto username = ConfigManager::getInstance().getUsername();
    std::string line;
    while (getline(line)) {
        if (line.empty()) {
            continue;
        }
        if (line[0] == '!') {
            CommandManager::getInstance().execute(line.substr(1));
            continue;
        }
        Generic::ChatMessage msg;
        msg.setSender(username);
        msg.setText(line);
        msg.encode();
        m_msgWriter(msg);
    }
}

void TUIManager::showReceivedMessage(const Generic::ChatMessage& msg)
{
    while (!m_started) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    const auto sender = msg.getSender();
    const auto username = ConfigManager::getInstance().getUsername();
    auto xPosition = clearCurrentLine(sender == username);
    const auto newColor = m_colors.size() % (static_cast<int>(TextColor::MAX_COLOR) - 1) + 1;
    registerColor(sender, TUIColor{ TextColor(newColor), TextColor::BLACK });
    setColor(sender);
    print(sender.c_str());
    print(": ");
    setColorDefault();
    print(msg.getText().c_str());
    print("\n");
    moveTo(getCursorPosition().m_y, xPosition);
    refresh();
}

void TUIManager::setMessageWriter(TUIManager::MsgWriter msgWriter)
{
    m_msgWriter = msgWriter;
}

void TUIManager::setFileSender(TUIManager::FileSender fileSender)
{
    m_fileSender = fileSender;
}

void TUIManager::sendFile(const Generic::FilePackage& file)
{
    m_fileSender(file);
}

void TUIManager::showInfo(const std::string& info)
{
    print("[I]", { TextAttribute::BOLD });
    print("\t");
    print(info.c_str());
    print("\n");
}

bool TUIManager::yesNoDialog(const std::string& question)
{
    print("[Q]", { TextAttribute::BOLD });
    print("\t");
    print(info.c_str());
    auto result = getch();
    return result == 'y' || result == 'Y';
}

void TUIManager::print(const char* str)
{
    printw(str);
    auto p = getCursorPosition();
    if (p.m_y == getRightBottomPosition().m_y - 2) {
        moveTo(0, 0);
        deleteln();
        moveTo(p.m_y - 1, p.m_x);
    }
}

void TUIManager::print(const char* str, const std::vector<TextAttribute>& style)
{
    auto attr = A_NORMAL;
    for (const auto& a : style) {
        attr |= static_cast<uint64_t>(a);
    }
    attron(attr);
    print(str);
    attroff(attr);
}

void TUIManager::moveTo(const int y, const int x)
{
    auto rbp = getRightBottomPosition();
    TUIPoint p = { y < 0 ? 0 : y >= rbp.m_y ? rbp.m_y - 1 : y,
                   x < 0 ? 0 : x >= rbp.m_x ? rbp.m_x - 1 : x };
    move(p.m_y, p.m_x);
}

TUIPoint TUIManager::getCursorPosition() const
{
    int y = 0;
    int x = 0;
    getyx(stdscr, y, x);
    return TUIPoint{ y, x };
}

TUIPoint TUIManager::getRightBottomPosition() const
{
    return TUIPoint{ LINES, COLS };
}

bool TUIManager::registerColor(const std::string& name, const TUIColor color)
{
    const int newId = m_colors.size() + 1;
    if (!m_colors.insert(std::make_pair(name, std::make_pair(newId, color))).second) {
        return false;
    }
    init_pair(newId, static_cast<uint64_t>(color.m_foreground),
                     static_cast<uint64_t>(color.m_background));
    return true;
}

void TUIManager::setColor(const std::string& name)
{
    if (m_currentColor != -1) {
        attroff(COLOR_PAIR(m_currentColor));
    }
    auto it = m_colors.find(name);
    if (it == m_colors.end()) {
        return;
    }
    m_currentColor = it->second.first;
    attron(COLOR_PAIR(m_currentColor));
}

void TUIManager::setColorDefault()
{
    setColor(s_defaultColorName);
}

int TUIManager::clearCurrentLine(const bool previous)
{
    int result = 0;
    auto p = getCursorPosition();
    if (previous) {
        moveTo(p.m_y - 1, p.m_x);
        clrtoeol();
    } else {
        if (p.m_x != 0) {
            insertln();
            result = p.m_x;
        }
        moveTo(p.m_y, 0);
    }
    refresh();
    return result;
}

bool TUIManager::getline(std::string& line)
{
    const auto capacity = getRightBottomPosition().m_x;
    line.clear();
    line.resize(capacity);
    getnstr(&line[0], capacity);
    return true;
}

TUIManager::TUIManager()
    : m_currentColor(-1)
    , m_started(false)
{
}

TUIManager::~TUIManager()
{
    if (m_started) {
        endwin();
    }
}

} // namespace Client
