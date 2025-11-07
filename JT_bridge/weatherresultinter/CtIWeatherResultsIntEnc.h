/*********************************************************************
** \file "_IWEATHERRESULTSINTENC.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#ifndef _IWEATHERRESULTSINTENC_H_
#define _IWEATHERRESULTSINTENC_H_

#if DtHLA 

//! \file _IWEATHERRESULTSINTENC.h
//! \brief This file provides a declaration of the class
//! CtIWeatherResultsIntEnc.
#include "dllExport.h"
#include <vl\interEncoder.h>




class CtIWeatherResultsInteraction;

//! Instances of CtIWeatherResultsIntEnc are used to encode
//! data from CtIWeatherResultsInteraction objects into
//! network structures.
class MAKEXTEND_EXPORT CtIWeatherResultsIntEnc : public DtInteractionEncoder
{
public:
   //! Constructor.
   CtIWeatherResultsIntEnc(DtExerciseConn* exConn,
      DtInterClassDesc* classDesc);

   //! Destructor.
   virtual ~CtIWeatherResultsIntEnc();

   //! Copy constructor.
   CtIWeatherResultsIntEnc(const CtIWeatherResultsIntEnc& orig);

   //! Assignment operator.
   CtIWeatherResultsIntEnc& operator=(const CtIWeatherResultsIntEnc& orig);

protected:
//! Encodes bagSum from inter into params.
   static void encodebagSum(
      const CtIWeatherResultsInteraction& inter,
      RTI::ParameterHandleValuePairSet* params,
      RTI::ParameterHandle paramHandle);//! Encodes bagNo from inter into params.
   static void encodebagNo(
      const CtIWeatherResultsInteraction& inter,
      RTI::ParameterHandleValuePairSet* params,
      RTI::ParameterHandle paramHandle);//! Encodes bagID from inter into params.
   static void encodebagID(
      const CtIWeatherResultsInteraction& inter,
      RTI::ParameterHandleValuePairSet* params,
      RTI::ParameterHandle paramHandle);//! Encodes bagSize from inter into params.
   static void encodebagSize(
      const CtIWeatherResultsInteraction& inter,
      RTI::ParameterHandleValuePairSet* params,
      RTI::ParameterHandle paramHandle);//! Encodes bagValue from inter into params.
   static void encodebagValue(
      const CtIWeatherResultsInteraction& inter,
      RTI::ParameterHandleValuePairSet* params,
      RTI::ParameterHandle paramHandle);
};



#endif //DtHLA
#endif //_IWEATHERRESULTSINTENC_H_



