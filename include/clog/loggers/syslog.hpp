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

#include <iostream>
#include <string>

#include <clog/base.hpp>
#include <syslog.h>

namespace clog {

namespace loggers {

class SyslogOption {
 public:
  enum Options {
    kConsole_CONS = LOG_CONS,
    kNoDelay_NDELAY = LOG_NDELAY,
    kNoWait_NOWAIT = LOG_NOWAIT,
    kDelayed_ODELAY = LOG_ODELAY,
#ifdef LOG_PERROR
    kStderr_PERROR = LOG_PERROR,
#endif
    kPid_PID = LOG_PID,
  };

 private:
  int options_;

 private:
  static int ParseOptions() { return 0; }
  template <class OptionT, class... OptionsT>
  static int ParseOptions(OptionT o, OptionsT... os) {
    return static_cast<int>(o) | ParseOptions(os...);
  }

 public:
  template <class... OptionsT>
  explicit SyslogOption(OptionsT... options)
      : options_(ParseOptions(options...)) {}

 public:
  int options() const noexcept { return options_; }
};

enum class SyslogFacility {
  kAuth_AUTH = LOG_AUTH,
  kAuthPrivate_AUTHPRIV = LOG_AUTHPRIV,
  kCron_CRON = LOG_CRON,
  kDaemon_DAEMON = LOG_DAEMON,
  kFtpDaemon_FTP = LOG_FTP,
  kKernel_KERN = LOG_KERN,
#define L(n) kLocal##n##_LOCAL##n = LOG_LOCAL##n
  L(0),
  L(1),
  L(2),
  L(3),
  L(4),
  L(5),
  L(6),
  L(7),
#undef L
  kLinePrinter_LPR = LOG_LPR,
  kMail_MAIL = LOG_MAIL,
  kNews_NEWS = LOG_NEWS,
  kSyslog_SYSLOG = LOG_SYSLOG,
  kUser_USER = LOG_USER,
  kUucp_UUCP = LOG_UUCP,
};

class SyslogLogger : public LoggerBase {
 private:
  std::string identity_;

 public:
  SyslogLogger() = delete;
  explicit SyslogLogger(
      std::string identity,
      SyslogOption option = SyslogOption(SyslogOption::kPid_PID),
      SyslogFacility facility = SyslogFacility::kUser_USER)
      : identity_(std::move(identity)) {
    openlog(identity_.c_str(), option.options(), static_cast<int>(facility));
  }

  SyslogLogger(const SyslogLogger&) = delete;
  SyslogLogger(SyslogLogger&&) = delete;

  SyslogLogger& operator=(const SyslogLogger&) = delete;
  SyslogLogger& operator=(SyslogLogger&&) = delete;

  ~SyslogLogger() override { closelog(); }

 public:
  void write(Level level, const std::string& tag,
             const std::string& message) override {
    if (level < this->level()) {
      return;
    }
    int priority = 0;
    switch (level) {
      case Level::kEmergency:
        priority = LOG_EMERG;
        break;
      case Level::kAlert:
        priority = LOG_ALERT;
        break;
      case Level::kCritical:
        priority = LOG_CRIT;
        break;
      case Level::kError:
        priority = LOG_ERR;
        break;
      case Level::kWarning:
        priority = LOG_WARNING;
        break;
      case Level::kNotice:
        priority = LOG_NOTICE;
        break;
      case Level::kInfo:
        priority = LOG_INFO;
        break;
      case Level::kDebug:
        priority = LOG_DEBUG;
        break;
    }

    syslog(priority, "%c/%s: %s", static_cast<char>(level), tag.c_str(),
           message.c_str());
  }
};

}  // namespace loggers

}  // namespace clog
