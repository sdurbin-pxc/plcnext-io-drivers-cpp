#include <string>
#include "AXLVariant.h"
#include "AXC2152.h"
#include <vector>
using namespace std;


namespace PLCnext
{

	class AXLModuleConfig
	{
	public:

	private:
		unsigned int type;
		string orderNumber;
		vector<Variant> settings;


	};



}