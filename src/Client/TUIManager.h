#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <ncurses.h>

#include "Generic/ChatMessage.h"
#include "Generic/FilePackage.h"
#include "Generic/SingletonBase.h"

namespace Client {

enum class TextAttribute : uint64_t
{
    NORMAL      = A_NORMAL,
    HIGHLIGHT   = A_STANDOUT,
    UNDERLINE   = A_UNDERLINE,
    BLINKING    = A_BLINK,
    DIM         = A_DIM,
    BOLD        = A_BOLD,
    INVISIBLE   = A_INVIS,
    ITALIC      = A_ITALIC
};

enum class TextColor : uint64_t
{
    BLACK   = COLOR_BLACK,
    RED     = COLOR_RED,
    GREEN   = COLOR_GREEN,
    YELLOW  = COLOR_YELLOW,
    BLUE    = COLOR_BLUE,
    MAGENTA = COLOR_MAGENTA,
    CYAN    = COLOR_CYAN,
    WHITE   = COLOR_WHITE,
    MAX_COLOR
};

struct TUIPoint
{
    int m_y;
    int m_x;
};

struct TUIColor
{
    TextColor   m_foreground;
    TextColor   m_background;
};

class TUIManager : public Generic::SingletonBase
{
SINGLETON_INTERFACE(TUIManager)

private:
    using MsgWriter = std::function<void (const Generic::ChatMessage&)>;
    using FileSender = std::function<void (const Generic::FilePackage&)>;

public:
    void start();
    void showReceivedMessage(const Generic::ChatMessage& msg);
    void setMessageWriter(MsgWriter msgWriter);
    void setFileSender(FileSender fileSender);
    void sendFile(const Generic::FilePackage& file);
    void showInfo(const std::string& info);
    bool yesNoDialog(const std::string& question);
    void print(const char* str);
    void print(const char* str, const std::vector<TextAttribute>& style);

private:
    void moveTo(const int y, const int x);
    TUIPoint getCursorPosition() const;
    TUIPoint getRightBottomPosition() const;
    bool registerColor(const std::string& name, const TUIColor color);
    void setColor(const std::string& name);
    void setColorDefault();
    int clearCurrentLine(const bool previous);
    bool getline(std::string& line);

private:
    TUIManager();
    ~TUIManager();

private:
    static const std::string s_defaultColorName;

private:
    using Colors = std::unordered_map<std::string, std::pair<int, TUIColor> >;

    std::mutex  m_readWriteMutex;
    MsgWriter   m_msgWriter;
    FileSender  m_fileSender;
    Colors      m_colors;
    int         m_currentColor;
    bool        m_started;
};

} // namespace Client
