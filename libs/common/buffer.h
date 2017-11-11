#pragma once

#include <vector>
#include <stdint.h>

namespace CHServer {
	
	// 非线程安全
	class Buffer {
	public:
		Buffer();
		~Buffer();
	public:
		// 有效数据大小
		int32_t GetDataLength();

		// 可用空间
		int32_t GetFreeLength();

		// 整个buffer大小
		int32_t GetAllLength();

		// 调整大小。只增不减
		// len 要增加的字节数
		void AdjustLength(int32_t len);

		// 可用空间头
		char* GetFreePoint();

		// 获取数据头
		char* GetDataPoint();
		
		int32_t GetContinuesDatalength();

		// 释放数据
		void FreeData(int32_t len);

		// 通过头指针， 填充了多少数据
		// 不可以超过GetFreeLength的大小！
		void FillData(int32_t len);

	private:
		std::vector<char> m_data;

		int32_t m_head;

		int32_t m_tail;
	};
}