#ifndef PFW_EVENT_H
#define PFW_EVENT_H

#include <filesystem>

namespace pfw {

namespace fs = std::filesystem;

enum EventType : uint8_t {
    NOOP            = 0b00000000,
    CREATED         = 0b00000001,
    MODIFIED        = 0b00000010,
    DELETED         = 0b00000100,
    RENAMED         = 0b00001000,
    BUFFER_OVERFLOW = 0b00010000,
    FAILED          = 0b00100000
};

inline bool noop(EventType eventType) { return eventType == EventType::NOOP; }

inline bool created(EventType eventType)
{
    return (eventType & EventType::CREATED) == EventType::CREATED;
}

inline bool modified(EventType eventType)
{
    return (eventType & EventType::MODIFIED) == EventType::MODIFIED;
}

inline bool deleted(EventType eventType)
{
    return (eventType & EventType::DELETED) == EventType::DELETED;
}

inline bool renamed(EventType eventType)
{
    return (eventType & EventType::RENAMED) == EventType::RENAMED;
}

inline bool buffer_overflow(EventType eventType)
{
    return (eventType & EventType::BUFFER_OVERFLOW) ==
           EventType::BUFFER_OVERFLOW;
}

inline bool failed(EventType eventType)
{
    return (eventType & EventType::FAILED) == EventType::FAILED;
}

inline EventType operator|(EventType lhs, EventType rhs)
{
    return static_cast<EventType>(static_cast<uint8_t>(lhs) |
                                  static_cast<uint8_t>(rhs));
}

inline EventType operator&(EventType lhs, EventType rhs)
{
    return static_cast<EventType>(static_cast<uint8_t>(lhs) &
                                  static_cast<uint8_t>(rhs));
}
inline EventType operator~(EventType lhs)
{
    return static_cast<EventType>(~static_cast<uint8_t>(lhs));
}

struct Event {
    Event(const EventType type, const fs::path &relativePath)
        : type(type)
        , relativePath(relativePath)
    {
        timePoint = std::chrono::high_resolution_clock::now();
    }

    EventType                                      type;
    fs::path                          relativePath;
    std::chrono::high_resolution_clock::time_point timePoint;
};
using EventPtr = std::unique_ptr<Event>;

}  // namespace pfw

#endif /* PFW_EVENT_H */