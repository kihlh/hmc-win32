#ifndef PFW_COLLECTOR_H
#define PFW_COLLECTOR_H

#include "pfw/win32/WindowsHeader.h"

#include <atomic>
#include <chrono>
#include <mutex>
#include <vector>

#include "pfw/Filter.h"

namespace pfw {

class Collector
{
  public:
    Collector(FilterPtr filter, std::chrono::milliseconds sleepDuration);
    ~Collector();

    void sendError(const std::string &errorMsg);
    void insert(std::vector<EventPtr> &&events);
    void push_back(EventType type, const std::filesystem::path &relativePath);

  private:
    void sendEvents();

    std::mutex            _event_input_mutex;
    std::vector<EventPtr> _inputVector;

    FilterPtr _filter;

    std::thread               _runner;
    std::chrono::milliseconds _sleepDuration;
    HANDLE                    _stopEvent;
    std::atomic<bool>         _inDestruction{false};
};

}  // namespace pfw

#endif /* PFW_COLLECTOR_H */
