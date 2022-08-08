#include "log.h"

#include <fcntl.h>

#include <cstdarg>
#include <cstring>
#include <ctime>
#include <functional>
#include <string>
#include <thread>
#include <vector>

#include "common.h"

namespace CHServer {
static const char* const sLogLEVEL[] = {"ERROR ", "DEBUG ", "WARNING "};

// void CHLog::PrepareFile(const char* path, const char* prefix, uint32_t& day,
// uv_fs_t& fileHandle) { 	time_t  now = time(NULL); 	now += 8 * 60 * 60; 	tm*
// timeStruct = gmtime(&now); 	if (fileHandle.data == NULL) { 		day =
// timeStruct->tm_mday; 		char fileName[128] = { 0 };

// 		snprintf(fileName, sizeof(fileName), "%s%s.%4d%02d%02d.log", path,
// prefix, timeStruct->tm_year + 1900, timeStruct->tm_mon + 1,
// timeStruct->tm_mday); 		OpenFile(fileName, fileHandle); 	} else { 		if (day !=
// timeStruct->tm_mday) { 			day = timeStruct->tm_mday; 			char fileName[128] = { 0 };

// 			snprintf(fileName, sizeof(fileName), "%s%s.%4d%02d%02d.log",
// path, prefix, timeStruct->tm_year + 1900, timeStruct->tm_mon + 1,
// timeStruct->tm_mday); 			OpenFile(fileName, fileHandle);
// 		}
// 	}
// }

// void CHLog::FormatTime(char* formatTime, int32_t size, uint32_t& lastSecond)
// { 	time_t  now = time(NULL); 	now += 8 * 60 * 60; 	tm* timeStruct =
// gmtime(&now); 	if (now != lastSecond) { 		lastSecond = (uint32_t)now;
// 		memset(formatTime, 0, size);
// 		snprintf(formatTime, size, "%4d%02d%02d %02d:%02d:%02d ",
// 			timeStruct->tm_year + 1900, timeStruct->tm_mon + 1,
// timeStruct->tm_mday, 			timeStruct->tm_hour, timeStruct->tm_min,
// timeStruct->tm_sec);
// 	}
// }

// void CHLog::OpenFile(char* fileName, uv_fs_t& fileHandle) {
// 	int result = 0;

// 	if (fileHandle.data) {
// 		uv_fs_close(NULL, &fileHandle,
// (uv_file)*((int*)(&fileHandle.data)), NULL); 		fileHandle.data = NULL;

// 		uv_fs_req_cleanup(&fileHandle);
// 	}

// 	result = uv_fs_open(NULL, &fileHandle, fileName, O_CREAT | O_RDWR |
// O_APPEND, S_IREAD | S_IWRITE, NULL); 	if (result < 0) { 		fprintf(stderr, "open
// file failed! name=%s, reason=%s", fileName, uv_strerror(result)); 		return;
// 	}
// 	uv_fs_req_cleanup(&fileHandle);

// 	fileHandle.data = (void*)result;
// }

void CHLog::DoLog() {
  // 	uv_fs_t fileHandle = { 0 };

  // 	uint32_t currentDay = 0;
  // 	char newLine = '\n';

  // 	uv_buf_t buf[5]; // time level content fileandline newline
  // 	buf[4] = uv_buf_init(&newLine, 1);

  // 	uint32_t size = 5;
  // 	while (!m_exit) {
  // 		LogData log = m_logData.Take();

  // 		PrepareFile(m_path.c_str(), m_fileNamePrefix.c_str(), currentDay,
  // fileHandle);

  // 		buf[0] = uv_buf_init((char*)log.data[0].c_str(), (unsigned
  // int)log.data[0].size()); 		buf[1] = uv_buf_init((char*)log.data[1].c_str(),
  // (unsigned int)log.data[1].size()); 		buf[2] =
  // uv_buf_init((char*)log.data[2].c_str(), (unsigned int)log.data[2].size());
  // 		buf[3] = uv_buf_init((char*)log.data[3].c_str(), (unsigned
  // int)log.data[3].size());

  // 		if (buf[3].base[buf[3].len - 1] == '\n') {
  // 			size = 4;
  // 		} else {
  // 			size = 5;
  // 		}
  // 		int result = uv_fs_write(NULL, &fileHandle,
  // (uv_file)*((int*)(&fileHandle.data)), buf, size, -1, NULL); 		if (result < 0)
  // { 			fprintf(stderr, "log failed %s%s%s%s\n", log.data[0].c_str(),
  // log.data[1].c_str(), log.data[2].c_str(), log.data[3].c_str());
  // 		}
  // 		uv_fs_req_cleanup(&fileHandle);
  // 	}
  // 	uv_fs_close(NULL, &fileHandle, (uv_file)*((int*)(&fileHandle.data)),
  // NULL); 	uv_fs_req_cleanup(&fileHandle);
}

CHLog::CHLog() {}

CHLog::~CHLog() {
  if (m_thread.joinable()) {
    m_thread.join();
  }
}

bool CHLog::InitLog(const char* path, const char* fileNamePrefix) {
  // std::lock_guard<std::mutex> lock(m_mutex);

  // if (!m_fileNamePrefix.empty()) {
  // 	fprintf(stderr, "InitLog already inited!\n");
  // 	return false;
  // }

  // m_fileNamePrefix = fileNamePrefix;

  // m_path = path;

  // if (m_path.find("/") == std::string::npos) {
  // 	m_path += "/";
  // }
  // std::string tmpPath = m_path;
  // std::vector<std::string> paths;
  // size_t find = tmpPath.find("/");

  // uv_fs_t req;
  // uint32_t result = 0;

  // while (find != std::string::npos) {
  // 	result = uv_fs_mkdir(NULL, &req, tmpPath.substr(0, find).c_str(), 0755,
  // NULL); 	find = tmpPath.find("/", find + 1);
  // }
  // uv_fs_req_cleanup(&req);
  // m_exit = !(result == 0 || result == UV_EEXIST);

  // m_thread = std::thread(&CHLog::DoLog, this);

  return !m_exit;
}

void CHLog::UninitLog() {
  m_exit = true;
  std::lock_guard<std::mutex> lock(m_mutex);
  // 唤醒一下，安全退出
  warning_log("UninitLog");
}

void CHLog::Log(const char* fileName, uint32_t lineNum, LOGLEVEL logLevel,
                const char* msg, ...) {
  // static uint32_t lastSecond = 0;
  // static char formatTime[64] = { 0 };

  // FormatTime(formatTime, sizeof formatTime, lastSecond);

  // char msgContent[1024 * 10] = { 0 };
  // va_list args;
  // va_start(args, msg);
  // vsnprintf(msgContent, sizeof(msgContent), msg, args);

  // char msgMetaInfo[64] = { 0 };
  // snprintf(msgMetaInfo, sizeof(msgMetaInfo), "%s:%u  ", fileName, lineNum);

  // LogData log;
  // log.data[0].assign(formatTime);
  // log.data[1].assign(sLogLEVEL[logLevel]);
  // log.data[2].assign(msgMetaInfo);
  // log.data[3].assign(msgContent);

  // m_logData.Put(log);

  // if (logLevel == LOGLEVEL_WARNING || m_fileNamePrefix.empty()) {
  // 	fprintf(stdout, "%s\n", msgContent);
  // }
}

}  // namespace CHServer
