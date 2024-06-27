#pragma once
#include "base_utility.hpp"

namespace simulation
{

class Customer
{
public:
	Customer(Level level, double timeFactor, size_t maxWaitingTime);
	virtual ~Customer() = default;

	[[nodiscard]]
	const Id<Customer>& get_id() const noexcept;

	[[nodiscard]]
	Level get_level() const noexcept;

	[[nodiscard]]
	double get_time_factor() const noexcept;

	[[nodiscard]]
	size_t get_max_waiting_time() const noexcept;

	[[nodiscard]]
	bool haircut_started() const noexcept;
	
	void start_cuting_hear() noexcept;

private:
	const Id<Customer> m_id;
	const Level m_level;
	const double m_timeFactor;	//消耗时间系数
	const size_t m_maxWaitingTime; //最长等待时间
	bool m_haircutStarted;
};

}	//namespace simulation
