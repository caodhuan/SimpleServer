#pragma once
#include "singleton.h"
#include "blockingqueue.h"

#include "uv.h"

#include <mutex>
#include <atomic>

struct tm;
namespace CHServer {

#define CHDEBUGLOG(msg, ...) CHLog::Instance()->Log(__FILE__, __LINE__, CHLog::LOGLEVEL_DEBUG, msg, ## __VA_ARGS__);
#define CHERRORLOG(msg, ...) CHLog::Instance()->Log(__FILE__, __LINE__, CHLog::LOGLEVEL_ERROR, msg, ## __VA_ARGS__);

	struct LogData {
		std::string data[4];
	};
	// 日志相关
	// 线程安全的
	class CHLog
		: public SingletonBase<CHLog> {
	public:
		~CHLog();

		enum LOGLEVEL {
			LOGLEVEL_DEBUG = 0,
			LOGLEVEL_ERROR = 1,
		};

	public:
		bool InitLog(const char* path, const char* fileNamePrefix);
		void UninitLog();

		void Log(const char* fileName, uint32_t lineNum, LOGLEVEL logLevel, const char* msg, ...);

	private:

		void DoLog();

		static void PrepareFile(const char* path, const char* prefix, uint32_t& day, uv_fs_t& fileHandle);

		static void OpenFile(char* fileName, uv_fs_t& fileHandle);

		static void FormatTime(char* formatTime, int32_t size, uint32_t& lastSecond);
	private:
		BlockingQueue<LogData> m_logData; // 考虑换 T

		std::mutex m_mutex;
		std::atomic_bool m_exit;

		std::string m_path; // init之外，都是readonly
		std::string m_fileNamePrefix; // init之外，都是readonly
	private:
		friend class SingletonBase<CHLog>;
		CHLog();
	};
}