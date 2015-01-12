#include <fstream>
#include <iomanip>
#include <sstream>

#include "menu.hpp"

namespace kq{

void Menu::operator()() const
{
	do{
		int selected;
		do{
			std::cout << "Options:" << std::endl;
			for(auto&& p : as_const(options_)){
				std::cout << std::setw(3) << p.first << " " << p.second.first <<
							 std::endl;
			}
			selected = Menu::get<int>(std::string("your selection"));
		}while(options_.find(selected) == end(options_));
		options_.at(selected).second();
	}while(loopStrategy_ == LoopStrategy::Infinite);
}

}
