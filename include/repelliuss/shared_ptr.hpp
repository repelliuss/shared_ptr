#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include "Tracker.hpp"
#include "MemoryManager.hpp"
#include "default_deleter.hpp"
#include <functional>

namespace rps {

	template<class T>
	class shared_ptr {

	public:
		shared_ptr() : tracker(nullptr) {}
		
		explicit shared_ptr(T *data) :
			tracker(new MemoryManager<T, default_deleter<T>>(data, default_deleter<T>())) {}

		template<class Deleter>
		shared_ptr(T *data, Deleter deleter) :
			tracker(new MemoryManager<T, Deleter>(data, deleter)) {}

		shared_ptr(const shared_ptr &other) : tracker(other.tracker) { add(); }

		~shared_ptr() { remove(); }

		shared_ptr& operator=(const shared_ptr& other) {

			if(this != &other) {
				remove();
				tracker = other.tracker;
				add();
			}

			return *this;
		}

		T* operator->() const noexcept { return tracker->tracking(); }

		T& operator*() const noexcept { return *(tracker->tracking()); }

		explicit operator bool() const noexcept {
			return tracker->tracking() == nullptr ? false : true;
		}

	private:
		Tracker<T> *tracker;

		void add() noexcept { if(tracker) tracker->increase(); }

		void remove() noexcept {
			if(tracker) {
				tracker->decrease();
				if(tracker->get_tracked_count() <= 0) {
					tracker->destroy();
					delete tracker;
					tracker = nullptr;
				}
			}
		}
	};
}

#endif // _SHARED_PTR_H_
