#pragma once

#include <vector>
#include "AXLFunction.h"

using namespace std;

namespace PLCnext
{
	   

	class AXLFunctional
	{
	public:
		const vector<AXLFunction*>& getFunctions();
		AXLFunction* getFunction(string name);
		AXLFunction* getFunction(int id);
		//virtual bool executeFunction(int id, vector<AXLVariant> params) = 0;
		~AXLFunctional();
		void* context;
	protected:
		void addFunction(string name, string description, vector<AXLParameter*> params, function<AXLFunction::ReturnCode(vector<AXLVariant>& params)>, bool isConfig);
		vector<AXLFunction*> m_functions;
	};

}