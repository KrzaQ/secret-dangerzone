#ifndef IOUTILS_H
#define IOUTILS_H

#include <functional>
#include <iosfwd>
#include <iostream>
#include <map>
#include <memory>
#include <limits>
#include <string>
#include <utility>

namespace kq{

namespace detail{
template<typename Func>
class ExceptionWrapper
{
public:
	template<typename T,
			 typename U = typename std::enable_if<
				 !std::is_same<
					 typename std::decay<T>::type,
					 ExceptionWrapper
				>::value,
			 void>::type
			>
	ExceptionWrapper(T&& t): f(std::forward<T>(t)){}

	ExceptionWrapper(ExceptionWrapper const&) = default;
	ExceptionWrapper(ExceptionWrapper &&) = default;

	void operator()() const {
		try{
			f();
		}catch(std::exception const& e){
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

private:
	Func f;
};
}

template<typename T>
auto makeExceptionWrapper(T&& t){
	return detail::ExceptionWrapper<typename std::decay<T>::type>(std::forward<T>(t));
}

class Menu
{
public:
	Menu():
		options_{{0,{"exit",[this]{exit();}}}}{}

	enum class LoopStrategy{
		Infinite,
		NoLoop
	};

	template<typename T>
	void addOption(int no, std::string const& name, T&& o){
		options_[no] = std::make_pair(name, std::forward<T>(o));
	}

	template<typename T>
	void addOption(std::string const& name, T&& o){
		int no = options_.size() ? options_.rbegin()->first + 1 : 1;
		options_[no] = std::make_pair(name, std::forward<T>(o));
	}

	template<typename T>
	static T get(std::string const& name = {}){
		T ret;
		if(name.size()) std::cout << "Please enter the value of " << name << ":" << std::endl;
		while(!(std::cin >> ret)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Please enter a valid value:" << std::endl;
		}
		return ret;
	}

	void operator()() const;

	void setLoopStrategy(LoopStrategy ls) { loopStrategy_ = ls; }

	void exit(){
		setLoopStrategy(LoopStrategy::NoLoop);
	}

private:
	LoopStrategy loopStrategy_ = LoopStrategy::NoLoop;
	std::map<int, std::pair<std::string,std::function<void()>>> options_;
};

}

#endif // IOUTILS_H
