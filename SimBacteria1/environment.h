#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include <list>

namespace Life
{
	// Forward declarations.
	class Bacterium;

	class Environment
	{
	public:
		Environment(void);

		void Cycle(void);
		void ReportLong(void) const;
		void ReportShort(void) const;

	protected:

		unsigned long long clock = 0;
		std::list<Bacterium> bacteria;
	};

	enum class FissionPhase
	{
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};

	class Bacterium
	{
	public:
		Bacterium(void) = delete;
		explicit Bacterium(unsigned long long markerSrc);
		void Action(std::list<Bacterium> &newBorns);
		void Report(void) const;
	
		const long long &age = this->age_;						// Read-only access.
		const unsigned long long &marker = this->marker_;		// Read-only access.
		const FissionPhase &fissionPhase = this->fissionPhase_;	// Read-only access.
		
	protected:
		void Reproduce(std::list<Bacterium> &newBorns);

		long long age_ = 0;
		FissionPhase fissionPhase_ = FissionPhase::A;
		const unsigned long long marker_;
		bool isHealthy = true;
	};

	unsigned long long MakeNewMarker(unsigned long long seed);
}
#endif
