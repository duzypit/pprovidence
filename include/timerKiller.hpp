#ifndef __TIMER_KILLER_HPP__
#define __TIMER_KILLER_HPP__

#include <chrono>
#include <condition_variable>
#include <mutex>

struct TimerKiller {
  // returns false if killed:
  template<class R, class P>
  bool wait_for( std::chrono::duration<R,P> const& time ) {
    std::unique_lock<std::mutex> lock(m);
    return !cv.wait_for(lock, time, [&]{return terminate;});
  }
  void kill() {
    std::unique_lock<std::mutex> lock(m);
    terminate=true;
    cv.notify_all();
  }
private:
  std::condition_variable cv;
  std::mutex m;
  bool terminate = false;
};

#endif
