#include "buffer.h"

#include<cstring>
#include <stdio.h>

namespace CHServer {
	Buffer::Buffer()
		: m_head(0)
		, m_tail(0) {
		m_data.resize(2048);
	}

	Buffer::~Buffer() {

	}

	int32_t Buffer::GetDataLength() {
		if (m_head > m_tail) {
			return m_data.size() - (m_head - m_tail);
		}
		return m_tail - m_head;
	}

	int32_t Buffer::GetFreeLength() {
		if (m_head > m_tail) {
			return m_head - m_tail; // 留一个空位
		}

		if (m_tail == m_head && m_head != 0) {
			return 0;
		}
		return m_data.size() - m_tail + m_head;
	}

	int32_t Buffer::GetAllLength() {
		return m_data.size();
	}

	void Buffer::AdjustLength(int32_t len) {
		if (len < 0) {
			return;
		}

		int32_t newLen = m_data.size() + len;

		m_data.resize(newLen);

		// 防止转了一圈的情况下，resize了
		if (m_head >= m_tail) {
			if (m_tail <= len) {
				// 有足够长的空间将转一圈的buff移到后面去
				memcpy(&m_data[m_data.size() - len], &m_data[0], m_tail - 1);
				m_tail = m_data.size() - len + m_tail + 1;
				m_tail %= m_data.size() + 1;
			} else {
				memcpy(&m_data[m_data.size() - len], &m_data[0], len);
				m_tail -= len;
				memcpy(&m_data[0], &m_data[len], m_tail);
			}
		}
	}

	char* Buffer::GetFreePoint() {
		if (m_tail >= m_data.size()) {
			return NULL;
		}
		return m_data.data() + m_tail;
	}

	char* Buffer::GetDataPoint() {
		return m_data.data() + m_head;
	}

	int32_t Buffer::GetContinuesDatalength() {
		if (m_tail == 0 && m_head == 0) {
			return 0;
		}

		if (m_tail <= m_head) {
			return m_data.size() - m_head;
		}

		return m_tail - m_head;
	}

	void Buffer::FreeData(int32_t len) {
		if (m_head == 0 && m_tail == 0) {
			fprintf(stderr, "out out space\n");
			return;
		}

		if (m_head < m_tail) {
			if (m_tail - m_head < len) {
				fprintf(stderr, "out out space\n");
				return;
			}

			m_head += len;
			if (m_head == m_tail) {
				m_head = 0;
				m_tail = 0;
			}
		} else {
			// 不能一次性转圈
			if (m_data.size() - m_head < len) {
				fprintf(stderr, "out out space\n");
				return;
			}
			m_head += len;
			if (m_head == m_data.size()) {
				m_head = 0;
			}
		}
	}

	void Buffer::FillData(int32_t len) {
		if (GetFreeLength() < len) {
			// CTODO 错误日志
			fprintf(stderr, "out out space\n");
			return;
		}
		if (m_head == 0 && m_tail == 0) {
			m_tail += len;
			return;
		}

		if (m_head < m_tail) {
			if (m_data.size() - m_tail > len) {
				m_tail += len;
			} else if (m_data.size() - m_tail + m_head >= len) {
				m_tail = len + m_tail;
				if (m_head > 0) {
					if (m_tail >= m_data.size()) {
						m_tail -= m_data.size();
					}
				}
			} else {
				// CTODO 错误日志
			}
		} else {
			if (m_head - m_tail >= len) {
				m_tail += len;
			} else {
				fprintf(stderr, "out out space\n");
				return;

			}
		}
	}

}
