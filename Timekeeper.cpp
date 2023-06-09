/*******************************************************************
*
*  Description:  Timekeeper atomic model
*
*                This is the implementation of the timing mechanism for
*                the soccer model.  A typical game of soccer includes two
*                periods of 45 minutes each.  This model tracks periods and
*                when it is time for a new period or the end of a game.
*
*                The model has one input and two outputs:
*
*                <start_game>: this input starts the game.
*
*                <start_period>: this output is activated whenever it is time
*                                for a new period.  The period number (0 or 1)
*                                is the value sent to the output.
*
*                <end_game>: this output is sent when two periods have elapsed.
*
*  Author:       Kevin Lam, student #215552
*                kevlam@vv.carleton.ca
*
*  Submitted:    October 18, 2002
*
*******************************************************************/


/** include files **/
#include "Timekeeper.h"// class definition for Timekeeper
#include "message.h"    // class ExternalMessage, InternalMessage

/** public functions **/

/*******************************************************************
* Function Name: Timekeeper constructor
* Description: This routine constructs the Timekeeper model
********************************************************************/
Timekeeper::Timekeeper( const string &name )
: Atomic( name )
, start_game( addInputPort( "start_game" ) )
, start_period( addOutputPort( "start_period" ) )
, end_game( addOutputPort( "end_game" ) )
, period_interval( 0, 45, 0, 0 )
{
}

/*******************************************************************
* Function Name: Timekeeper init function
* Description: This routine is invoked when the simulator starts.  It
* initializes some variables and does nothing else.  The model does not
* begin doing any useful work until "start" is received.
********************************************************************/
Model &Timekeeper::initFunction()
{
	Period = 0;
	game_started = false;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This routine handles external events coming from the
* input port.  The start_game signal can only be given once; afterward it
* is ignored.
********************************************************************/
Model &Timekeeper::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == start_game )
   {
		// can only start a game once!
      if (game_started == false)
      {
      	game_started = true;
			holdIn( passive, Time::Zero );
      }
   }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function increments the period count and
*              sets the timer interval for the next period.
********************************************************************/
Model &Timekeeper::internalFunction( const InternalMessage & )
{

		// schedule another call to output function when the next period starts
   	if (Period++ < 3)
      {
		   holdIn( passive, period_interval);
      }


	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This routine outputs <start_period> or <end_game>
*              depending on the current period count.
********************************************************************/
Model &Timekeeper::outputFunction( const InternalMessage &msg )
{
   if (Period >= 2)
	{
     	sendOutput( msg.time(), end_game, 1 ) ;
      passivate();
   }
	else
   {
      sendOutput( msg.time(), start_period, Period ) ;
   }

	return *this ;
}
