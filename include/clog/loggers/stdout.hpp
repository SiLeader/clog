//   Copyright 2019 SiLeader.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>

#include <clog/base.hpp>

namespace clog {
namespace loggers {

class StdoutLogger : public LoggerBase {
 public:
  void write(Level level, const std::string& tag,
             const std::string& message) override {
    if (level < this->level()) {
      return;
    }
    auto tp = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(tp);
    auto tm = std::localtime(&t);

    std::string messagePrefix;
    messagePrefix += static_cast<char>(level);
    messagePrefix += '/';

    messagePrefix += tag;

    std::cout << std::put_time(tm, "") << " " << messagePrefix << ": "
              << message << std::endl;
  }
};

}  // namespace loggers
}  // namespace clog
