#include <format>
#include "base_utility.hpp"
#include "exception.hpp"

namespace simulation
{
using namespace std;

Tick::Tick(size_t h, size_t m, size_t s)
{
	check_valid(h, m, s);	
	Hms hms {.hour = h, .min = m, .sec = s};
	m_timestamp = hms2tick(hms);
	s_tick2hmsTable[m_timestamp] = hms;
}

bool Tick::operator==(const Tick& rhs)const noexcept
{
	return m_timestamp == rhs.m_timestamp;
}

auto Tick::operator<=>(const Tick& rhs)const noexcept
-> std::strong_ordering 
{
	return m_timestamp <=> rhs.m_timestamp;
}

void Tick::increament(size_t h, size_t m, size_t s)
{
	decltype(auto) thisHms { tick2hms() };
	Hms hms {
		.hour = thisHms.hour + h,
		.min = thisHms.min + m, 
		.sec = thisHms.sec + s,
	};

	m_timestamp = hms2tick(hms);
	s_tick2hmsTable[m_timestamp] = hms;
}

auto Tick::tick2hms() const -> const Hms&
{	
	auto itr { s_tick2hmsTable.find(m_timestamp) };
	if (itr == s_tick2hmsTable.end())
		throw std::logic_error { format("m_timestamp: {} cannot find hms in hashmap", m_timestamp) };
	
	return itr->second;
}

uint64_t Tick::hms2tick(const Hms& hms)
{
	return hms.sec | (hms.min << 6) | (hms.hour << 12 );
}

void Tick::check_valid(size_t h, size_t m, size_t s)
{
	if (h < 0 || h >= 24)
		throw InvalidTimepoint { format("input hours: {} invalid", h) };

	if (m < 0 || m >= 60)
		throw InvalidTimepoint { format("input minutes: {} invalid", m) };

	if (s < 0 || s >= 60)
		throw InvalidTimepoint { format("input second: {} invalid", s) };
}

}		//namespace simulation

