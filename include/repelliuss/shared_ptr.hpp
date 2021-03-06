#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include "Tracker.hpp"
#include "MemoryManager.hpp"
#include "default_delete.hpp"
#include <cstddef> //for nullptr_t
#include <ostream> //for basic_ostream

namespace rps {

	template<class T>
	class shared_ptr {

	public:
		constexpr shared_ptr() : tracker(nullptr) {}

		constexpr shared_ptr(std::nullptr_t) : tracker(nullptr) {}

		explicit shared_ptr(T *data) :
			tracker(new MemoryManager<T, default_delete<T>>(data, default_delete<T>())) {}

		template<class Deleter>
		shared_ptr(T *data, Deleter deleter) :
			tracker(new MemoryManager<T, Deleter>(data, deleter)) {}

		shared_ptr(const shared_ptr &other) : tracker(other.tracker) { add(); }

		shared_ptr(shared_ptr &&other) :
			tracker(other.tracker) { other.tracker = nullptr; }

		~shared_ptr() { remove(); }

		bool unique() const noexcept {
			return tracker == nullptr ?
				false : tracker->get_tracked_count() == 1;
		}

		void reset() noexcept { remove(); }
		void reset(T *data) noexcept {
			remove();
			tracker = new MemoryManager<T, default_delete<T>>(data, default_delete<T>());
		}

		template<class Deleter>
		void reset(T *data, Deleter deleter) {
			remove();
			tracker = new MemoryManager<T, Deleter>(data, deleter);
		}

		long use_count() const noexcept {
			return tracker == nullptr ?
				0 : tracker->get_tracked_count();
		}

		T* get() const noexcept { return tracker == nullptr ?
				nullptr : tracker->tracking();
		}

		void swap(shared_ptr &other) noexcept {

			Tracker<T> *temp = tracker;
			tracker = other.tracker;
			other.tracker = tracker;
		}

		shared_ptr& operator=(const shared_ptr &other) {

			if(this != &other) {
				remove();
				tracker = other.tracker;
				add();
			}

			return *this;
		}

		bool owner_before(const shared_ptr &other) const noexcept {
			return tracker == other.tracker;
		}

		shared_ptr& operator=(shared_ptr &&other) {

			if(this != &other) {
				remove();
				tracker = other.tracker;
				other.tracker = nullptr;
			}

			return *this;
		}

		T* operator->() const noexcept { return tracker == nullptr ?
				nullptr : tracker->tracking();
		}

		//you never want to dereference null, do you?
		T& operator*() const noexcept { return *(tracker->tracking()); }

		explicit operator bool() const noexcept {
			if(tracker)
				return tracker->tracking() == nullptr ? false : true;
			return false;
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

	template<class T>
	void swap(shared_ptr<T> &left, shared_ptr<T> &right) noexcept {
		left.swap(right);
	}

	template<class charT, class traits, class T>
	std::basic_ostream<charT, traits>&
	operator<<(std::basic_ostream<charT, traits> &os,
			   const shared_ptr<T> &myself) {
			os << myself.get();
			return os;
	}

	template<class T>
	bool operator==(const shared_ptr<T> &l, const shared_ptr<T> &r) noexcept {
		return l.get() == r.get();
	}

	template<class T>
	bool operator==(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() == nullptr;
	}

	template <class T>
	bool operator==(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr = r.get();
	}

	template<class T>
	bool operator!=(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() != nullptr;
	}

	template<class T>
	bool operator!=(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr != r.get();
	}

	template<class T>
	bool operator<(const shared_ptr<T> &l, const shared_ptr<T> &r) noexcept {
		return l.get() < r.get();
	}

	template<class T>
	bool operator<(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() < nullptr;
	}

	template<class T>
	bool operator<(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr < r.get();
	}

	template<class T>
	bool operator<=(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() <= nullptr;
	}

	template<class T>
	bool operator<=(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr <= r.get();
	}

	template<class T>
	bool operator>(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() > nullptr;
	}

	template<class T>
	bool operator>(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr > r.get();
	}

	template<class T>
	bool operator>=(const shared_ptr<T> &l, std::nullptr_t) noexcept {
		return l.get() >= nullptr;
	}

	template<class T>
	bool operator>=(std::nullptr_t, const shared_ptr<T> &r) noexcept {
		return nullptr >= r.get();
	}
}

#endif // _SHARED_PTR_H_
