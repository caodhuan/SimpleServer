#include "log.h"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace CHServer {

CHLog::CHLog() {}

CHLog::~CHLog() {}

bool CHLog::InitLog(const char* path, const char* fileNamePrefix) {
  logging::add_file_log(
      keywords::open_mode = std::ios_base::app,
      keywords::file_name =
          "path/fileNamePrefix_%Y%m%d.log", /*< file name pattern >*/
      keywords::rotation_size =
          10 * 1024 * 1024, /*< rotate files every 10 MiB... >*/
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(
          0, 0, 0), /*< ...or at midnight >*/
      keywords::format = "[%TimeStamp%] [%Severity%]: %Message%");
  return false;
}

void CHLog::UpdateLogLevel(log_level level) {
  logging::core::get()->set_filter(logging::trivial::severity >= level);
}

}  // namespace CHServer
