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

int main() {
  clog::Logger logger;
  logger.addLogger<clog::loggers::StdoutLogger>();

  const std::string TAG = "tag";
  logger.emergency(TAG, "emergency");
  logger.alert(TAG, "alert");
  logger.critical(TAG, "critical");
  logger.error(TAG, "error");
  logger.warning(TAG, "warning");
  logger.notice(TAG, "notice");
  logger.info(TAG, "info");
  logger.debug(TAG, "debug");

  logger.info(TAG, "int: ", 42, ", double: ", 3.14, ", string: ", TAG);
  return 0;
}
