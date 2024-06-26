#include <print>
#include "business_logic.hpp"
using namespace std;
using namespace simulation;

void printManager(MainObjManager& objManager)
{
	println("{{");
	//Customer
	for(auto itr { objManager.cbegin<Customer>() };
		itr != objManager.cend<Customer>();
		++itr)
	{
		const auto& p { itr->second };
		println("\tCustomer {}, factor time {}, maxWaiting time {}",
				p->get_id().get_id_number(), p->get_time_factor(), p->get_max_waiting_time());
	}
	//Barber
	for(auto itr { objManager.cbegin<Barber>() };
	itr != objManager.cend<Barber>();
	++itr)
	{
		const auto& p { itr->second };
		println("\tBarber {}, factor time {}, level {}",
				p->get_id().get_id_number(), p->get_time_factor(), static_cast<int>(p->get_level()));
	}
	//Chair
	for(auto itr { objManager.cbegin<Chair>() };
	itr != objManager.cend<Chair>();
	++itr)
	{
		const auto& p { itr->second };
		println("\tChair {}", p->get_id().get_id_number());
	}
	
	println("}}");
}

int main_loop(MainObjManager& objManager, MainEventManager& eventManager)
{
	while(!eventManager.empty())
	{
		printManager(objManager);
		eventManager.execve();
	}
	return 0;
}
