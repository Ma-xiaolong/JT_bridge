/*********************************************************************
** \file "CtIWeatherResultsIntDec.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#if DtHLA 

#include "CtIWeatherResultsIntDec.h"
#include "CtIWeatherResultsInteraction.h"
#include <vl/hExerciseConn.h>

#include <vector>



CtIWeatherResultsIntDec::CtIWeatherResultsIntDec(
   DtExerciseConn* exConn,
   DtInterClassDesc* classDesc) : 
   DtInteractionDecoder(exConn, classDesc)
{
   addDecoder((char*)"bagSum",
      (DtParameterDecoder) decodebagSum);
   addDecoder((char*)"bagNo",
      (DtParameterDecoder) decodebagNo);
   addDecoder((char*)"bagID",
      (DtParameterDecoder) decodebagID);
   addDecoder((char*)"bagSize",
      (DtParameterDecoder) decodebagSize);
   addDecoder((char*)"bagValue",
      (DtParameterDecoder) decodebagValue);

}

CtIWeatherResultsIntDec::~CtIWeatherResultsIntDec()
{
}

CtIWeatherResultsIntDec::CtIWeatherResultsIntDec(const CtIWeatherResultsIntDec& orig) :
   DtInteractionDecoder(orig)
{
}

CtIWeatherResultsIntDec& CtIWeatherResultsIntDec::operator=(const CtIWeatherResultsIntDec& orig)
{
   // Guard against assignment to yourself.
   if (this == &orig)
   {
      return *this;
   }

   DtInteractionDecoder::operator=(orig);

   return *this;
}


void CtIWeatherResultsIntDec::decodebagSum(
   CtIWeatherResultsInteraction* inter,
   const RTI::ParameterHandleValuePairSet& params,
   int pairSetIndex)
{
	

 
    
	RTI::ULong length = params.getValueLength(pairSetIndex);
	if (length > sizeof(int))
   {
      DtWarn("Size of value decoded for parameter bagSum (%d)\n",length);
      DtWarn(" is larger than size of int (%d)\n", sizeof(int));
      return;
   }

   int netVal;
   params.getValue(pairSetIndex, (char*)&netVal, length);
   inter->setbagSum(netVal);
    
  
}

void CtIWeatherResultsIntDec::decodebagNo(
   CtIWeatherResultsInteraction* inter,
   const RTI::ParameterHandleValuePairSet& params,
   int pairSetIndex)
{
	

 
    
	RTI::ULong length = params.getValueLength(pairSetIndex);
	if (length > sizeof(int))
   {
      DtWarn("Size of value decoded for parameter bagNo (%d)\n",length);
      DtWarn(" is larger than size of int (%d)\n", sizeof(int));
      return;
   }

   int netVal;
   params.getValue(pairSetIndex, (char*)&netVal, length);
   inter->setbagNo(netVal);
    
  
}

void CtIWeatherResultsIntDec::decodebagID(
   CtIWeatherResultsInteraction* inter,
   const RTI::ParameterHandleValuePairSet& params,
   int pairSetIndex)
{
	

 
    
	RTI::ULong length = params.getValueLength(pairSetIndex);
	if (length > sizeof(int))
   {
      DtWarn("Size of value decoded for parameter bagID (%d)\n",length);
      DtWarn(" is larger than size of int (%d)\n", sizeof(int));
      return;
   }

   int netVal;
   params.getValue(pairSetIndex, (char*)&netVal, length);
   inter->setbagID(netVal);
    
  
}

void CtIWeatherResultsIntDec::decodebagSize(
   CtIWeatherResultsInteraction* inter,
   const RTI::ParameterHandleValuePairSet& params,
   int pairSetIndex)
{
	

 
    
	RTI::ULong length = params.getValueLength(pairSetIndex);
	if (length > sizeof(int))
   {
      DtWarn("Size of value decoded for parameter bagSize (%d)\n",length);
      DtWarn(" is larger than size of int (%d)\n", sizeof(int));
      return;
   }

   int netVal;
   params.getValue(pairSetIndex, (char*)&netVal, length);
   inter->setbagSize(netVal);
    
  
}

void CtIWeatherResultsIntDec::decodebagValue(
   CtIWeatherResultsInteraction* inter,
   const RTI::ParameterHandleValuePairSet& params,
   int pairSetIndex)
{
	

 
    
   RTI::ULong length = params.getValueLength(pairSetIndex);	
   char * pBuf = new char[length];
   params.getValue(pairSetIndex, (char*)pBuf, length);
   string netVal(pBuf,length);
   inter->setbagValue(netVal);
   delete[] pBuf;
    
  
}




#endif
