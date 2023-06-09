/*******************************************************************
*
*  Description:  Ball_Play atomic model
*
*  Author:       Kevin Lam, student #215552
*                kevlam@vv.carleton.ca
*
*  Submitted:    October 18, 2002
*
*******************************************************************/

#ifndef __BALLPLAY_H
#define __BALLPLAY_H

#include <list>
#include "atomic.h"     // class Atomic

// BallPlay class (represents the state of the game (kick-offs, regular play)
//                 and handles scoring)

class BallPlay : public Atomic
{
public:
	// Constructor
	BallPlay( const string &name = "BallPlay" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &start_period;
	const Port &end_game;
	const Port &score;

	// output port
	Port &game_on;
  	Port &game_score;

  	const Time one_minute;

   // scores
   int ScoreHome;
   int ScoreVisitor;

   // possible game states (0 = kick off, 1 = ball in play, 2 = game end)

   int GameState;

};	// class BallPlay

// globals
   const int STATE_KICKOFF = 0;
   const int STATE_BALL_IN_PLAY = 1;
   const int STATE_GAME_OVER = 3;


// ** inline ** //
inline
string BallPlay::className() const
{
	return "BallPlay";
}

#endif   //__BALLPLAY_H
