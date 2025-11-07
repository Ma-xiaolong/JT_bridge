/*********************************************************************
** \file "CtIWeatherResultsIntEnc.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#if DtHLA 

#include "CtIWeatherResultsIntEnc.h"
//#include " "
#include "CtIWeatherResultsInteraction.h"
#include <vl/hExerciseConn.h>



CtIWeatherResultsIntEnc::CtIWeatherResultsIntEnc(DtExerciseConn* exConn,
   DtInterClassDesc* classDesc) : 
   DtInteractionEncoder(exConn, classDesc)
{
   addEncoder((char*)"bagSum",
      (DtParameterEncoder) encodebagSum);
   addEncoder((char*)"bagNo",
      (DtParameterEncoder) encodebagNo);
   addEncoder((char*)"bagID",
      (DtParameterEncoder) encodebagID);
   addEncoder((char*)"bagSize",
      (DtParameterEncoder) encodebagSize);
   addEncoder((char*)"bagValue",
      (DtParameterEncoder) encodebagValue);

}

CtIWeatherResultsIntEnc::~CtIWeatherResultsIntEnc()
{
}

CtIWeatherResultsIntEnc::CtIWeatherResultsIntEnc(const CtIWeatherResultsIntEnc& orig) :
   DtInteractionEncoder(orig)
{
}

CtIWeatherResultsIntEnc& CtIWeatherResultsIntEnc::operator=(const CtIWeatherResultsIntEnc& orig)
{
   // Guard against assignment to yourself.
   if (this == &orig)
   {
      return *this;
   }

   DtInteractionEncoder::operator=(orig);

   return *this;
}


void CtIWeatherResultsIntEnc::encodebagSum(const CtIWeatherResultsInteraction& inter,
   RTI::ParameterHandleValuePairSet* params,
   RTI::ParameterHandle paramHandle)
{
    
	int netVal;
    netVal = inter.bagSum();
    params->add(paramHandle, (char*)&netVal,sizeof(int));
    
  }

void CtIWeatherResultsIntEnc::encodebagNo(const CtIWeatherResultsInteraction& inter,
   RTI::ParameterHandleValuePairSet* params,
   RTI::ParameterHandle paramHandle)
{
    
	int netVal;
    netVal = inter.bagNo();
    params->add(paramHandle, (char*)&netVal,sizeof(int));
    
  }

void CtIWeatherResultsIntEnc::encodebagID(const CtIWeatherResultsInteraction& inter,
   RTI::ParameterHandleValuePairSet* params,
   RTI::ParameterHandle paramHandle)
{
    
	int netVal;
    netVal = inter.bagID();
    params->add(paramHandle, (char*)&netVal,sizeof(int));
    
  }

void CtIWeatherResultsIntEnc::encodebagSize(const CtIWeatherResultsInteraction& inter,
   RTI::ParameterHandleValuePairSet* params,
   RTI::ParameterHandle paramHandle)
{
    
	int netVal;
    netVal = inter.bagSize();
    params->add(paramHandle, (char*)&netVal,sizeof(int));
    
  }

void CtIWeatherResultsIntEnc::encodebagValue(const CtIWeatherResultsInteraction& inter,
   RTI::ParameterHandleValuePairSet* params,
   RTI::ParameterHandle paramHandle)
{
    
	std::string netVal;
    netVal = inter.bagValue();
    params->add(paramHandle, (char*)netVal.c_str(),netVal.size());
    
  }



#endif





