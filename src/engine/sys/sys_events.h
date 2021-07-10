/*
===========================================================================
Daemon BSD Source Code
Copyright (c) 2017, Daemon Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Daemon developers nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DAEMON DEVELOPERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===========================================================================
*/

#ifndef ENGINE_SYS_SYS_EVENTS_H_
#define ENGINE_SYS_SYS_EVENTS_H_

#include <string>
#include <vector>

#include "common/Assert.h"
#include "engine/client/keys.h"
#include "engine/qcommon/qcommon.h"

namespace Sys {

class EventBase {
public:
    const sysEventType_t type;
    EventBase(sysEventType_t type) : type(type) { }

    virtual ~EventBase() = 0;

    template<typename T>
    const T& Cast() const {
        ASSERT_EQ(this->type, T::ClassType());
        return *static_cast<const T*>(this);
    }

    EventBase(const EventBase&) = delete;
    EventBase& operator=(const EventBase&) = delete;
};
inline EventBase::~EventBase() = default;

class KeyEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_KEY; }

    const Keyboard::Key key;
    const bool down;
    const int time;
    KeyEvent(Keyboard::Key key, bool down, int time):
        EventBase(ClassType()), key(key), down(down), time(time) {}
};

class CharEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_CHAR; }

    const uint32_t ch; // Unicode code point
    CharEvent(uint32_t ch):
        EventBase(ClassType()), ch(ch) {}
};

// Relative mouse movement
class MouseEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_MOUSE; }

    const int dx, dy;
    MouseEvent(int dx, int dy):
        EventBase(ClassType()), dx(dx), dy(dy) {}
};

// Absolute mouse position
class MousePosEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_MOUSE_POS; }

    const int x, y;
    MousePosEvent(int x, int y):
        EventBase(ClassType()), x(x), y(y) {}
};

class JoystickEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_JOYSTICK_AXIS; }

    const int axis;
    const int value;
    JoystickEvent(int axis, int value):
        EventBase(ClassType()), axis(axis), value(value) {}
};

class ConsoleInputEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_CONSOLE; }

    const std::string text;
    ConsoleInputEvent(std::string text):
        EventBase(ClassType()), text(std::move(text)) {}
};

class PacketEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_PACKET; }

    const netadr_t adr;
    const std::vector<byte> data;
    PacketEvent(const netadr_t& adr, const byte* dataPtr, size_t dataLen):
        EventBase(ClassType()), adr(adr), data(dataPtr, dataPtr + dataLen) {}
};

class FocusEvent: public EventBase {
public:
    static constexpr sysEventType_t ClassType() { return sysEventType_t::SE_FOCUS; }

    const bool focus; // Whether the cgame has focus
    FocusEvent(bool focus):
        EventBase(ClassType()), focus(focus) {}
};

} // namespace Sys

#endif // ENGINE_SYS_SYS_EVENTS_H_
