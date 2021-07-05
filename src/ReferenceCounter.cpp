#include "ReferenceCounter.h"
#include <assert.h>
#include <iostream>


namespace FeatureExtractor {
	ReferenceCounter::ReferenceCounter()
		: reference_count(0)
	{
	}


	void ReferenceCounter::register_reference()
	{
		reference_count++;
	}

	void ReferenceCounter::deregister_reference()
	{
		assert(reference_count > 0  && "Deregistering reference failed: no more registered references left!");

		// If no more references, commit suicide (hahaha)
		if (!(reference_count--)){
			std::cout << "refCounter: delete: " << reference_count << "." << std::endl;
			delete this;
		}
		//reference_count--;
		//std::cout << "refCounter: decremented: " << reference_count << "." << std::endl;
		//if(reference_count <= 0){
		//	//std::cout << "deleting reference" << std::endl;
		//	std::cout << "refCounter: delete" << std::endl;
		//	delete this;
		//}
	}
}
