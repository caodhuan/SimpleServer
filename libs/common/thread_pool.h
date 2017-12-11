#pragma once
#include <atomic>
#include <functional>
#include <vector>
#include <thread>

#include "blockingqueue.h"
#include "singleton.h"

namespace CHServer {
	class ThreadPool : public Singleton<ThreadPool> {

	private:
		std::atomic_bool m_done;

		BlockingQueue<std::function<void()> > m_workQueue;

		std::vector<std::thread> m_threads;

		void WorkerThread() {
			while (!m_done) {
				std::function<void()> task = m_workQueue.Take();
				task();
			}
		}

	public:
		ThreadPool(uint32_t threadCount = std::thread::hardware_concurrency())
			: m_done(false) {
			for (uint32_t i = 0; i < threadCount; ++i) {
				m_threads.push_back(std::thread(&ThreadPool::WorkerThread, this));
			}
		}

		~ThreadPool() {
			m_done = true;
			// CTODO: WorkerThread需要breakout 然后在此join
		}

		template<typename FunctionType>
		void AddTask(FunctionType func) {
			m_workQueue.Put(std::function<void()>(func));
		}
	};
}