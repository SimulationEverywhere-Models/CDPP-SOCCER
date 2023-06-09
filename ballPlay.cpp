/*******************************************************************
*
*  Description:  Ball_Play atomic model
*
*                This is the implementation of the kickoff and scoring
*                "modes" in a game of soccer.  This atomic model tracks
*                whether the game is in "kick off" or "ball in play" modes
*                and handles score events.
*
*                The model has three inputs and two outputs.  The inputs
*                represent signals from a referee overseeing the match.
*
*                <start_period>: this input indicates the start of a new period.
*
*                <score>: this input represents a score and can take
*                         possible values of 0 (home team) or 1 (visitor).
*
*                <end_game>: this input indicates the match is over.  When
*                            received, the final score is output.
*
*                <game_on>: this output is an indication that a kickoff has
*                           occurred and the ball is in play.
*
*                <game_score>: this output indicates the final score of the
*                              match.  It is always output twice sequentially,
*                              indicating Home and Visitor scores.
*
*  Author:       Kevin Lam, student #215552
*                kevlam@vv.carleton.ca
*
*  Submitted:    October 18, 2002
*
*******************************************************************/


/** include files **/
#include "ballPlay.h"// class definition for BallPlay
#include "message.h"    // class ExternalMessage, InternalMessage

/** public functions **/

/*******************************************************************
* Function Name: BallPlay constructor
* Description: This routine constructs the BallPlay model
********************************************************************/
BallPlay::BallPlay( const string &name )
: Atomic( name )
, start_period( addInputPort( "start_period" ) )
, end_game( addInputPort( "end_game" ) )
, score( addInputPort( "score" ) )
, game_on( addOutputPort( "game_on" ) )
, game_score( addOutputPort( "game_score" ) )
, one_minute( 0, 1, 0, 0 )
{
}

/*******************************************************************
* Function Name: ballPlay init function
* Description: This routine is invoked when the simulator starts.  It
* initializes some variables and does nothing else.  The model does not
* begin doing any useful work until "start" is received.
********************************************************************/
Model &BallPlay::initFunction()
{
	this->ScoreHome = 0;
   this->ScoreVisitor = 0;

  	this->GameState = STATE_KICKOFF;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This routine handles external events coming from any
* of the three input ports.
********************************************************************/
Model &BallPlay::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == start_period )
	   {
		if (GameState != STATE_GAME_OVER)
      {
		// Start the game with a kickoff.  Activate the internal
		// transition function in 1 minute to represent the kick.

		GameState = STATE_KICKOFF;
		holdIn( passive, one_minute );
      }
	   }

	else if( msg.port() == score )
	   {
		// must be in ball_in_play mode to be able to score.
	   if( (GameState == STATE_BALL_IN_PLAY) )
		   {
         // figure out who scored and increment the counter
			if( msg.value() == true )
				ScoreVisitor++;	// visitor team scored
			else
				ScoreHome++;      // home team scored

         GameState = STATE_KICKOFF ; 	// back to kickoff

			holdIn( passive, one_minute );
		   }
	   }
	else if( msg.port() == end_game )
	   {
         GameState = STATE_GAME_OVER ; 	// end game

			// force score output
			holdIn( passive, Time::Zero );
	   }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: If the game state is in kick-off mode, the internal
*              function will generate an event to cause the kick-off
*              and bring the ball into play.
********************************************************************/
Model &BallPlay::internalFunction( const InternalMessage & )
{
	if ( state() == passive )
	{
      if (GameState == STATE_KICKOFF)		// in kick off mode
      {
      	GameState = STATE_BALL_IN_PLAY;			// kick taken, game on
			// generate an output (game on)
		   holdIn( passive, Time::Zero );
	   }
   }
	else
	   // wait for the next external event
	   holdIn( active, Time::Inf );

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This routine outputs <game_score> or <game_on> as
*              appropriate.  The final score output is called twice, first
*              with the Home score and then the Visitor score.
********************************************************************/
Model &BallPlay::outputFunction( const InternalMessage &msg )
{
	// send <game_on> if we just kicked
	if (GameState == STATE_BALL_IN_PLAY)
	{
      	sendOutput( msg.time(), game_on, 1 ) ;
			passivate();
   }
	else if (GameState == STATE_GAME_OVER)
	{
      	sendOutput( msg.time(), game_score, ScoreHome ) ;
        	sendOutput( msg.time(), game_score, ScoreVisitor ) ;
			passivate();
   }

	return *this ;
}
