#pragma once
#include "singleton.h"

namespace CHServer {
	class Config;

	class ResourceManager : public Singleton<ResourceManager> {
	public:
		ResourceManager();
		~ResourceManager();
	

	private:
		Config* m_config;
	};
}