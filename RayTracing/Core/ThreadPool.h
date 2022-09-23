#pragma once
#include "Types.h"

#include <thread>
#include <vector>
#include <condition_variable>
#include <atomic>

class ThreadPool
{
public:
	ThreadPool(u32 numThreads = std::thread::hardware_concurrency())
		:
		mNumThreads(numThreads)
	{}

	static bool IsWorkCompleted() { return sNumCompletedThreads == std::thread::hardware_concurrency(); }
	static bool IsLineProcessed() { return sLineProcessed; }

	template<typename... Args>
	static UPtr<ThreadPool> Create(Args... args) { return std::make_unique<ThreadPool>(std::forward<Args>(args)...); }
private:
	std::vector<std::thread> mThreads;
	u32 mNumThreads;

	inline static std::condition_variable sCV;
	inline static std::mutex sCVMutex;
	inline static std::atomic<u32> sNumCompletedThreads = 0;
	inline static bool sLineProcessed = false;

	friend class Renderer;
};



