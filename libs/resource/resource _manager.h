#pragma once
#include "singleton.h"

namespace CHServer {
	class Config;

	class ResourceManager : public Singleton<ResourceManager> {
	public:
		ResourceManager();
		~ResourceManager();
	
	public:
		bool Initialize();

		void Finalize();
	private:
		Config* m_config;
	};
}