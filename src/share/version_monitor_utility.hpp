#pragma once

#include "constants.hpp"
#include "version_monitor.hpp"

namespace krbn {
class version_monitor_utility final {
public:
  static void start_monitor_to_stop_main_run_loop_when_version_changed(void) {
    auto monitor = version_monitor::get_shared_instance();

    monitor->changed.connect([](auto&& version) {
      dispatch_async(dispatch_get_main_queue(), ^{
        CFRunLoopStop(CFRunLoopGetCurrent());
      });
    });

    monitor->start(constants::get_version_file_path());
  }
};
} // namespace krbn
