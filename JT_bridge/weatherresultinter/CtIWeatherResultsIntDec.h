/*********************************************************************
** \file "_IWEATHERRESULTSDECHEADER.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#ifndef _IWEATHERRESULTSDECHEADER_H_
#define _IWEATHERRESULTSDECHEADER_H_

#if DtHLA 

//! \file _IWEATHERRESULTSDECHEADER.h
//! \brief This file provides a declaration of the class
//! CtIWeatherResultsIntDec.
#include "dllExport.h"
#include <vl/interDecoder.h>




class CtIWeatherResultsInteraction;

//! Instances of CtIWeatherResultsIntDec are used to decode
//! data from the network into CtIWeatherResultsInteraction
//! objects.
class MAKEXTEND_EXPORT CtIWeatherResultsIntDec : public DtInteractionDecoder
{
public:
   //! Constructor.
   CtIWeatherResultsIntDec(DtExerciseConn* exConn,
      DtInterClassDesc* classDesc);

   //! Destructor.
   virtual ~CtIWeatherResultsIntDec();

   //! Copy constructor.
   CtIWeatherResultsIntDec(const CtIWeatherResultsIntDec& orig);

   //! Assignment operator.
   CtIWeatherResultsIntDec& operator=(const CtIWeatherResultsIntDec& orig);

protected:
//! Decodes bagSum from params into inter.
   static void decodebagSum(
      CtIWeatherResultsInteraction* inter,
      const RTI::ParameterHandleValuePairSet& params,
      int pairSetIndex);//! Decodes bagNo from params into inter.
   static void decodebagNo(
      CtIWeatherResultsInteraction* inter,
      const RTI::ParameterHandleValuePairSet& params,
      int pairSetIndex);//! Decodes bagID from params into inter.
   static void decodebagID(
      CtIWeatherResultsInteraction* inter,
      const RTI::ParameterHandleValuePairSet& params,
      int pairSetIndex);//! Decodes bagSize from params into inter.
   static void decodebagSize(
      CtIWeatherResultsInteraction* inter,
      const RTI::ParameterHandleValuePairSet& params,
      int pairSetIndex);//! Decodes bagValue from params into inter.
   static void decodebagValue(
      CtIWeatherResultsInteraction* inter,
      const RTI::ParameterHandleValuePairSet& params,
      int pairSetIndex);
};



#endif   //DtHLA
#endif   //_IWEATHERRESULTSDECHEADER_H_
