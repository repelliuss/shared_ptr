#ifndef _MEMORYMANAGER_H_
#define _MEMORYMANAGER_H_

#include "Tracker.hpp"

namespace rps {

	template<class T, class Deleter>
	class MemoryManager : public Tracker<T> {

	public:
		MemoryManager(T *arg_data, Deleter arg_deleter) :
			data(arg_data), deleter(arg_deleter) {}

		void destroy() override final { deleter(data); }
		T* tracking() const noexcept final override { return data; }
	private:
		T *data;
		Deleter deleter;
	};
}

#endif // _MEMORYMANAGER_H_
