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

#include <memory>
#include <vector>

#include "base.hpp"

namespace clog {

class Logger : public LoggerBase {
 private:
  std::vector<std::unique_ptr<LoggerBase>> internalLogger_;

 public:
  Logger() = default;

  template <class LoggerT, class... CArgs>
  explicit Logger(CArgs&&... args) {
    addLogger<LoggerT>(std::forward<CArgs>(args)...);
  }

  Logger(const Logger&) = delete;
  Logger(Logger&&) = default;

  Logger& operator=(const Logger&) = delete;
  Logger& operator=(Logger&&) = default;

  ~Logger() override = default;

 public:
  template <class LoggerT, class... CArgs>
  void addLogger(CArgs&&... args) {
    static_assert(std::is_base_of<LoggerBase, LoggerT>::value,
                  "Logger class must be inherited from clog::Logger.");
    internalLogger_.emplace_back(new LoggerT(std::forward<CArgs>(args)...));
  }

 public:
  void write(Level level, const std::string& tag,
             const std::string& message) override {
    if (level < this->level()) {
      return;
    }
    for (auto& logger : internalLogger_) {
      logger->write(level, tag, message);
    }
  }

 public:
  static Logger& GetLogger() {
    static Logger logger;
    return logger;
  }
};

}  // namespace clog
