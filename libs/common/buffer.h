#pragma once

#include <vector>

namespace CHServer {

	class Buffer {
	public:
		Buffer();
		~Buffer();
	private:
		std::vector<char> m_data;
	};
}