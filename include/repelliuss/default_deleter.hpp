#ifndef _DEFAULT_DELETER_H_
#define _DEFAULT_DELETER_H_

namespace rps {

	template<typename T>
	class default_deleter {
	public:
		void operator()(T *ptr) const { delete ptr; }
		void operator()(T arr_ptr) const { delete[] arr_ptr; }
	};
}

#endif // _DEFAULT_DELETER_H_
