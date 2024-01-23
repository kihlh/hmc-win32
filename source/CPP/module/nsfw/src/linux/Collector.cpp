#include "pfw/linux/Collector.h"

#include <csignal>
#include <cstring>
#include <map>
#include <thread>

using namespace pfw;

Collector::Collector(std::shared_ptr<Filter>   filter,
                     std::chrono::milliseconds sleepDuration)
    : mFilter(filter)
    , mSleepDuration(sleepDuration)
    , mStopped(true)
{
    auto result = pthread_create(&mRunner, NULL, work, this);

    if (result != 0) {
        filter->sendError("Could not start Controller thread. ErrorCode: " +
                          std::string(strerror(errno)));
        return;
    }
}

Collector::~Collector()
{
    if (mStopped) {
        return;
    }

    mStopped = true;

    // \note(mathias): To be sure, that canceling the thread does not causes
    // abortion of the whole programm, because another lib reacts on signal 32,
    // we ignore the signal extra. Additionally we are saving the previous
    // handler to register this handler to signal 32 again at the end. (This is
    // only a assumption, because we was seeing this behaviour (abort of the
    // whole programm when calling dtor of Collector) in combination with other
    // libs without finding the root causes.
    auto previousHandler = std::signal(32, SIG_IGN);

    auto errorCode = pthread_cancel(mRunner);
    if (errorCode != 0) {
        mFilter->sendError("Could not cancel Collector thread. ErrorCode: " +
                           std::to_string(errorCode));
        return;
    }

    errorCode = pthread_join(mRunner, NULL);
    if (errorCode != 0) {
        mFilter->sendError("Could not join Collector thread. ErrorCode: " +
                           std::to_string(errorCode));
    }

    if (previousHandler != SIG_ERR) {
        std::signal(32, previousHandler);
    }
}

void Collector::finish(void *args)
{
    Collector *collector = reinterpret_cast<Collector *>(args);
    collector->mStopped  = true;
}

void *Collector::work(void *args)
{
    pthread_cleanup_push(Collector::finish, args);

    Collector *collector = reinterpret_cast<Collector *>(args);

    collector->mStopped = false;

    while (!collector->mStopped) {
        collector->sendEvents();
        std::this_thread::sleep_for(collector->mSleepDuration);
    }

    pthread_cleanup_pop(1);
    return nullptr;
}

void Collector::sendEvents()
{
    std::vector<EventPtr> result = std::vector<EventPtr>();

    {
        std::lock_guard<std::mutex> lockIn(event_input_mutex);
        std::swap(inputVector, result);
    }

    // remove duplicates
    std::map<std::filesystem::path, std::vector<EventPtr>::reverse_iterator>
        values;
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

    mFilter->filterAndNotify(std::move(result));
}

void Collector::sendError(const std::string &errorMsg)
{
    mFilter->sendError(errorMsg);
}

void Collector::insert(std::vector<EventPtr> &&events)
{
    std::lock_guard<std::mutex> lock(event_input_mutex);
    for (auto &event : events) {
        inputVector.push_back(std::move(event));
    }
}

void Collector::push_back(EventType                    type,
                          const std::filesystem::path &relativePath)
{
    std::lock_guard<std::mutex> lock(event_input_mutex);
    inputVector.emplace_back(
        std::unique_ptr<Event>(new Event(type, relativePath)));
}
