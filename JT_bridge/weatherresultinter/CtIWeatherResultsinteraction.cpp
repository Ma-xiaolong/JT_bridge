/*********************************************************************
** \file "CtIWeatherResultsinteraction.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#if DtHLA 
#include "CtIWeatherResultsinteraction.h"
#include<vlutil/vlPrintUtil.h>
#include <vl/exerciseConn.h>
#include <vl/hInterFactory.h>
#include "CtIWeatherResultsIntEnc.h"
#include "CtIWeatherResultsIntDec.h"


CtIWeatherResultsInteraction::CtIWeatherResultsInteraction() :
   DtInteractionWithEncDec()

{
}

CtIWeatherResultsInteraction::~CtIWeatherResultsInteraction()
{
}

CtIWeatherResultsInteraction::CtIWeatherResultsInteraction(
   const CtIWeatherResultsInteraction& orig) :
   DtInteractionWithEncDec(orig)

   ,mybagSum(orig.mybagSum)
   ,mybagNo(orig.mybagNo)
   ,mybagID(orig.mybagID)
   ,mybagSize(orig.mybagSize)
   ,mybagValue(orig.mybagValue)
{   

}

CtIWeatherResultsInteraction& CtIWeatherResultsInteraction::operator=(
   const CtIWeatherResultsInteraction& orig)
{
   // Guard against assignment to yourself.
   if (this == &orig)
   {
      return *this;
   }

   DtInteractionWithEncDec::operator=(orig);

   mybagSum = orig.mybagSum;

   mybagNo = orig.mybagNo;

   mybagID = orig.mybagID;

   mybagSize = orig.mybagSize;

   mybagValue = orig.mybagValue;


   return *this;
}

DtInteraction* CtIWeatherResultsInteraction::create()
{
   return new CtIWeatherResultsInteraction();
}

void CtIWeatherResultsInteraction::printData() const
{
  // printDataToStream(DtInfo);
}

void CtIWeatherResultsInteraction::printDataToStream(std::ostream& stream) const
{


   DtPrintAttribute(stream, "bagSum", mybagSum);

   DtPrintAttribute(stream, "bagNo", mybagNo);

   DtPrintAttribute(stream, "bagID", mybagID);

   DtPrintAttribute(stream, "bagSize", mybagSize);

   DtPrintAttribute(stream, "bagValue", mybagValue);

}

void CtIWeatherResultsInteraction::addCallback(DtExerciseConn* conn,
   CtIWeatherResultsInteractionCB cb, void* usr, DtDDMRegionSP region)
{
   conn->addInteractionCallbackByName("HLAinteractionRoot.IWeatherResults",
      (DtReceiveInteractionCb) cb, usr, region);
      
   conn->interactionFactory()->addCreator("HLAinteractionRoot.IWeatherResults",
      CtIWeatherResultsInteraction::create);
}

void CtIWeatherResultsInteraction::removeCallback(DtExerciseConn* conn,
   CtIWeatherResultsInteractionCB cb, void* usr, DtDDMRegionSP region)
{
   conn->removeInteractionCallbackByName("HLAinteractionRoot.IWeatherResults",
      (DtReceiveInteractionCb) cb, usr, region);
}

void CtIWeatherResultsInteraction::setbagSum(const int& val)
{
   mybagSum = val;
}

int CtIWeatherResultsInteraction::bagSum() const
{
   return mybagSum;
}

void CtIWeatherResultsInteraction::setbagNo(const int& val)
{
   mybagNo = val;
}

int CtIWeatherResultsInteraction::bagNo() const
{
   return mybagNo;
}

void CtIWeatherResultsInteraction::setbagID(const int& val)
{
   mybagID = val;
}

int CtIWeatherResultsInteraction::bagID() const
{
   return mybagID;
}

void CtIWeatherResultsInteraction::setbagSize(const int& val)
{
   mybagSize = val;
}

int CtIWeatherResultsInteraction::bagSize() const
{
   return mybagSize;
}

void CtIWeatherResultsInteraction::setbagValue(const string& val)
{
   mybagValue = val;
}

string CtIWeatherResultsInteraction::bagValue() const
{
   return mybagValue;
}


char* CtIWeatherResultsInteraction::interactionClassToUse(DtExerciseConn* exConn) const
{
  return "HLAinteractionRoot.IWeatherResults";
}

DtInteractionDecoder* CtIWeatherResultsInteraction::createDecoder(
   DtExerciseConn* exConn) const
{
   return new CtIWeatherResultsIntDec(exConn, classDesc());
}

DtInteractionEncoder* CtIWeatherResultsInteraction::createEncoder(
   DtExerciseConn* exConn) const
{
   return new CtIWeatherResultsIntEnc(exConn, classDesc());
}


#endif
