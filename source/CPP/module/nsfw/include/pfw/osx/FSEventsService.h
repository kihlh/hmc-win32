#ifndef PFW_FS_EVENTS_SERVICE_H
#define PFW_FS_EVENTS_SERVICE_H

#include <filesystem>
#include <map>
#include <mutex>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <vector>

#include "pfw/Filter.h"
#include "pfw/osx/OSXHeader.h"

namespace pfw {

class RunLoop;

class FSEventsService
{
  public:
    FSEventsService(std::shared_ptr<Filter>          filter,
                    std::filesystem::path            path,
                    const std::chrono::milliseconds &latency);

    static void
    FSEventsServiceCallback(ConstFSEventStreamRef         streamRef,
                            void *                        clientCallBackInfo,
                            size_t                        numEvents,
                            void *                        eventPaths,
                            const FSEventStreamEventFlags eventFlags[],
                            const FSEventStreamEventId    eventIds[]);

    void                         sendError(const std::string &errorMsg);
    bool                         isWatching();
    const std::filesystem::path &rootPath();

    ~FSEventsService();

  private:
    void dispatch(std::vector<EventPtr> &&events);

    std::filesystem::path   mPath;
    RunLoop *               mRunLoop;
    std::shared_ptr<Filter> mFilter;
};

}  // namespace pfw

#endif /* PFW_FS_EVENTS_SERVICE_H */