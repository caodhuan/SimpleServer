#pragma once

// 单例基类
namespace CHServer {
	template<typename T>
	class SingletonBase {
	public:
		static T* Instance() {
			static T instance;
			return &instance;
		}
	protected:
		SingletonBase() = default;
	private:
		SingletonBase(const SingletonBase&) = default;
		SingletonBase& operator=(const SingletonBase&) = default;
	};
}