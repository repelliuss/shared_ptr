#ifndef _TRACKER_H_
#define _TRACKER_H_

namespace rps {

	class Tracker {

	public:
		Tracker() : tracked_count(1) {}

		int get_tracked_count() const noexcept { return tracked_count; }
		void increase() noexcept { ++tracked_count; }
		void decrease() noexcept { --tracked_count; }

		virtual void destroy() = 0;
		virtual ~Tracker() {}

	private:
		int tracked_count;
	};
}

#endif // _TRACKER_H_
