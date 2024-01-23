#ifndef PFW_SINGLESHOT_SEMAPHORE_H
#define PFW_SINGLESHOT_SEMAPHORE_H

#include <condition_variable>
#include <mutex>

namespace pfw {

/**
 * This is a convenience abstraction around std::condition_variable that allows
 * for a one-shot synchronization point. Therefore the Semaphore has no way to
 * reset its state.
 *
 * It doesn't matter if the waiting thread calls `wait()` before or after the
 * signaling thread calls `signal()`. Only in the latter case the `wait()` won't
 * block.
 */
class SingleshotSemaphore
{
  public:
    SingleshotSemaphore()
        : _state(false)
    {
    }

    /**
     * Blocks the calling thread until the semaphore is signaled asynchronously.
     * If `signal()` has been called on the semaphore already, this won't block.
     */
    void wait()
    {
        std::unique_lock<std::mutex> lk(_mutex);

        while (!_state) {
            _cond.wait(lk);
        }
    }

    /**
     * Blocks the calling thread for a given time period and continues either
     * when `signal()` was called asynchronously or when the time is up. The
     * return condition is indicated by the returned boolean.
     *
     * \return true if the semaphore was signal()ed; false on timeout reached
     */
    bool waitFor(std::chrono::milliseconds ms)
    {
        std::unique_lock<std::mutex> lk(_mutex);

        if (_state) {
            return true;
        }

        _cond.wait_for(lk, ms);
        return _state;
    }

    /**
     * Unblocks all waiting threads of the semaphore. Note that threads reaching
     * the `wait()` on this semaphore after `signal()` has been called won't
     * block but continue immediately.
     */
    void signal()
    {
        std::unique_lock<std::mutex> lk(_mutex);
        _state = true;
        _cond.notify_all();
    }

  private:
    std::mutex              _mutex;
    std::condition_variable _cond;
    bool                    _state;
};

}  // namespace pfw

#endif /* PFW_SINGLESHOT_SEMAPHORE_H */
