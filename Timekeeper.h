/*******************************************************************
*
*  Description:  Timekeeper atomic model
*
*  Author:       Kevin Lam, student #215552
*                kevlam@vv.carleton.ca
*
*  Submitted:    October 18, 2002
*
*******************************************************************/

#ifndef __TIMEKEEPER_H
#define __TIMEKEEPER_H

#include <list>
#include "atomic.h"     // class Atomic

// Timekeeper class

class Timekeeper : public Atomic
{
public:
	// Constructor
	Timekeeper( const string &name = "Timekeeper" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &start_game;

	// output port
	Port &start_period;
  	Port &end_game;

   int Period;
	bool game_started;

  	const Time period_interval;

};	// class Timekeeper

// ** inline ** //
inline
string Timekeeper::className() const
{
	return "Timekeeper";
}

#endif   //__TIMEKEEPER_H
