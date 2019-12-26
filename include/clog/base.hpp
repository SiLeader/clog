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

#include <sstream>
#include <string>

namespace clog {

namespace detail {

template <class MessageFragmentT>
void FragmentsToMessageStringImpl(std::stringstream& ss,
                                  MessageFragmentT&& messageFragment) {
  ss << std::forward<MessageFragmentT>(messageFragment) << std::flush;
}

template <class MessageFragmentT, class... MessageFragmentsT>
void FragmentsToMessageStringImpl(std::stringstream& ss,
                                  MessageFragmentT&& messageFragment,
                                  MessageFragmentsT&&... messageFragments) {
  ss << std::forward<MessageFragmentT>(messageFragment);
  FragmentsToMessageStringImpl(
      ss, std::forward<MessageFragmentsT>(messageFragments)...);
}

template <class... MessageFragmentsT>
std::string FragmentsToMessageString(MessageFragmentsT&&... messageFragments) {
  std::stringstream ss;
  FragmentsToMessageStringImpl(
      ss, std::forward<MessageFragmentsT>(messageFragments)...);

  return ss.str();
}

}  // namespace detail

enum class Level : char {
  kEmergency = 'e',
  kAlert = 'A',
  kCritical = 'C',
  kError = 'E',
  kWarning = 'W',
  kNotice = 'N',
  kInfo = 'I',
  kDebug = 'D',
};

inline bool operator<(Level lhs, Level rhs) {
  static auto toLevelInt = [](Level l) noexcept {
    switch (l) {
      case Level::kEmergency:
        return 7;
      case Level::kAlert:
        return 6;
      case Level::kCritical:
        return 5;
      case Level::kError:
        return 4;
      case Level::kWarning:
        return 3;
      case Level::kNotice:
        return 2;
      case Level::kInfo:
        return 1;
      case Level::kDebug:
        return 0;
    }
  };

  auto lhsInt = toLevelInt(lhs);
  auto rhsInt = toLevelInt(rhs);

  return lhsInt < rhsInt;
}

class LoggerBase {
 private:
  Level logLevel_ = Level::kInfo;

 public:
  virtual ~LoggerBase() = default;

 public:
  virtual void write(Level level, const std::string& tag,
                     const std::string& message) = 0;

  void level(Level level) noexcept { logLevel_ = level; }
  Level level() const noexcept { return logLevel_; }

 public:
  template <class... MessageFragmentsT>
  void emergency(const std::string& tag,
                 MessageFragmentsT&&... messageFragments) {
    write(Level::kEmergency, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void alert(const std::string& tag, MessageFragmentsT&&... messageFragments) {
    write(Level::kAlert, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void critical(const std::string& tag,
                MessageFragmentsT&&... messageFragments) {
    write(Level::kCritical, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void error(const std::string& tag, MessageFragmentsT&&... messageFragments) {
    write(Level::kError, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void warning(const std::string& tag,
               MessageFragmentsT&&... messageFragments) {
    write(Level::kWarning, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void notice(const std::string& tag, MessageFragmentsT&&... messageFragments) {
    write(Level::kNotice, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void info(const std::string& tag, MessageFragmentsT&&... messageFragments) {
    write(Level::kInfo, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }

  template <class... MessageFragmentsT>
  void debug(const std::string& tag, MessageFragmentsT&&... messageFragments) {
    write(Level::kDebug, tag,
          detail::FragmentsToMessageString(
              std::forward<MessageFragmentsT>(messageFragments)...));
  }
};

}  // namespace clog
