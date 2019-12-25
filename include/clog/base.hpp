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

enum class Level {
  kEmergency,
  kAlert,
  kCritical,
  kError,
  kWarning,
  kNotice,
  kInfo,
  kDebug,
};

class LoggerBase {
 public:
  virtual ~LoggerBase() = default;

 public:
  virtual void write(Level level, const std::string& tag,
                     const std::string& message) = 0;

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
