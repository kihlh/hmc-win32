#include "pfw/win32/Collector.h"

#include <map>

using namespace pfw;

Collector::Collector(FilterPtr filter, std::chrono::milliseconds sleepDuration)
    : _filter(filter)
    , _sleepDuration(sleepDuration)
    , _stopEvent(CreateEvent(NULL, true, false, NULL))
{
    HANDLE semaphore = CreateSemaphoreW(NULL, 0, 1, NULL);
    _runner          = std::thread([this] {
        while (!_inDestruction) {
            sendEvents();

            WaitForSingleObject(_stopEvent, _sleepDuration.count());
        }
    });
}

Collector::~Collector()
{
    _inDestruction = true;
    SetEvent(_stopEvent);
    _runner.join();
    CloseHandle(_stopEvent);
}

void Collector::sendEvents()
{
    std::vector<EventPtr> result = std::vector<EventPtr>();

    {
        std::lock_guard<std::mutex> lockIn(_event_input_mutex);
        std::swap(_inputVector, result);
    }

    // remove duplicates
    std::map<fs::path, std::vector<EventPtr>::reverse_iterator> values;
    for (auto itr = result.rbegin(); itr != result.rend(); ++itr) {
        auto result = values.emplace((*itr)->relativePath, itr);

        if (result.second) {
            continue;
        }

        EventPtr &event           = *itr;
        EventPtr &conflictedEvent = *result.first->second;
        conflictedEvent->type     = conflictedEvent->type | event->type;

        event.reset(nullptr);
    }

    result.erase(std::remove_if(result.begin(), result.end(),
                                [&](const EventPtr &value) { return !value; }),
                 result.end());

    _filter->filterAndNotify(std::move(result));
}

void Collector::sendError(const std::string &errorMsg)
{
    _filter->sendError(errorMsg);
}

void Collector::insert(std::vector<EventPtr> &&events)
{
    std::lock_guard<std::mutex> lock(_event_input_mutex);
    for (auto &event : events) {
        _inputVector.push_back(std::move(event));
    }
}

void Collector::push_back(EventType type, const fs::path &relativePath)
{
    std::lock_guard<std::mutex> lock(_event_input_mutex);
    _inputVector.emplace_back(
        std::unique_ptr<Event>(new Event(type, relativePath)));
}
