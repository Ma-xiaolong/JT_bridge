/*********************************************************************
** \file "_IWEATHERRESULTSINTERACTION.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/

#ifndef _IWEATHERRESULTSINTERACTION_H_
#define _IWEATHERRESULTSINTERACTION_H_

#if DtHLA 

//! \file _IWEATHERRESULTSINTERACTION.h
//! \brief This file provides a declaration of the class
//! CtIWeatherResultsInteraction.
#include "dllExport.h"
#include <vl/hIntWEncDec.h>

#include <string>
using namespace std;
class DtExerciseConn;



class CtIWeatherResultsInteraction;

//! CtIWeatherResultsInteraction  callback function signature.
typedef void (*CtIWeatherResultsInteractionCB) (CtIWeatherResultsInteraction* inter, 
   void* usr);

//! Instances of CtIWeatherResultsInteraction are used to store state data for
//! <!FullClassName!> interactions.
class MAKEXTEND_EXPORT CtIWeatherResultsInteraction : public DtInteractionWithEncDec
{
public:

   //! Constructor.
   CtIWeatherResultsInteraction();

   //! Destructor.
   virtual ~CtIWeatherResultsInteraction();

   //! Copy constructor.
   CtIWeatherResultsInteraction(const CtIWeatherResultsInteraction& orig);

   //! Assignment operator.
   CtIWeatherResultsInteraction& operator=(const CtIWeatherResultsInteraction& orig);

   //! Print the interaction's data.
   virtual void printData() const;

   //! Print the interaction's data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
   

   //! Set the bagSum.
   virtual void setbagSum(
		const int& val);

   //! Get the bagSum."

	virtual  int bagSum() const;

   //! Set the bagNo.
   virtual void setbagNo(
		const int& val);

   //! Get the bagNo."

	virtual  int bagNo() const;

   //! Set the bagID.
   virtual void setbagID(
		const int& val);

   //! Get the bagID."

	virtual  int bagID() const;

   //! Set the bagSize.
   virtual void setbagSize(
		const int& val);

   //! Get the bagSize."

	virtual  int bagSize() const;

   //! Set the bagValue.
   virtual void setbagValue(
		const string& val);

   //! Get the bagValue."

	virtual  string bagValue() const;

      
   //! Name of the interaction. (Not necessarily the ClassName from the FOM.)
   virtual const char* name() const { return "CtIWeatherResultsInteraction"; }

public:

   //! Create a CtIWeatherResultsInteraction.
   //! Caller is responsible for deletion.
   static DtInteraction* create();

   //! Add (register)/Remove (deregister) function to be called when
   //! interaction occurs.
   static void addCallback(DtExerciseConn* conn,
      CtIWeatherResultsInteractionCB cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());
   static void removeCallback(DtExerciseConn* conn,
      CtIWeatherResultsInteractionCB cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());

protected:
   virtual char* interactionClassToUse(DtExerciseConn* exConn) const;

   virtual DtInteractionDecoder* createDecoder(DtExerciseConn* exConn) const;

   virtual DtInteractionEncoder* createEncoder(DtExerciseConn* exConn) const;
      
      
protected:

int mybagSum;

int mybagNo;

int mybagID;

int mybagSize;

string mybagValue;


};



#endif
#endif
 

