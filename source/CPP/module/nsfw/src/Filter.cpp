#include "pfw/Filter.h"
#include <iostream>

#pragma unmanaged

using namespace pfw;

Filter::Filter(CallBackSignatur callBack)
{
    mCallbackHandle = registerCallback(callBack);
}

Filter::~Filter() { deregisterCallback(mCallbackHandle); }

void Filter::sendError(const std::string &errorMsg)
{
    std::vector<EventPtr> events;
    events.emplace_back(std::make_unique<Event>(EventType::FAILED, errorMsg));
    notify(std::move(events));
}

void Filter::filterAndNotify(std::vector<EventPtr> &&events)
{
    if (events.empty()) {
        return;
    }
    notify(std::move(events));
}
