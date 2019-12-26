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

#include <iostream>

#include <clog/logger.hpp>
#include <clog/loggers/stdout.hpp>
#include <clog/loggers/syslog.hpp>

int main() {
  clog::Logger& logger = clog::Logger::GetLogger();
  logger.addLogger<clog::loggers::StdoutLogger>();
  logger.addLogger<clog::loggers::SyslogLogger>("clog");

  const std::string TAG = "tag";
  logger.emergency(TAG, "emergency log");
  logger.alert(TAG, "alert log");
  logger.critical(TAG, "critical log");
  logger.error(TAG, "error log");
  logger.warning(TAG, "warning log");
  logger.notice(TAG, "notice log");
  logger.info(TAG, "info log");
  logger.debug(TAG, "debug log");

  logger.info(TAG, "int: ", 42, ", double: ", 3.14, ", string: ", TAG);
  return 0;
}
