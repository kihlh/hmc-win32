#ifndef PFW_FILTER_H
#define PFW_FILTER_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "pfw/Event.h"
#include "pfw/Listener.h"

namespace pfw {

using CallBackSignatur =
    std::function<void(std::vector<std::unique_ptr<Event>> &&)>;

class Filter : public Listener<CallBackSignatur>
{
  public:
    Filter(CallBackSignatur callBack);
    ~Filter();

    void sendError(const std::string &errorMsg);
    void filterAndNotify(std::vector<EventPtr> &&events);

  private:
    Listener::CallbackHandle mCallbackHandle;
};

using FilterPtr = std::shared_ptr<Filter>;

}  // namespace pfw

#endif /* PFW_FILTER_H */