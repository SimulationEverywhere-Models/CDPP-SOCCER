[top]
components : bp@BallPlay
in : c_start_period c_score c_end_game
out : c_game_on c_game_score
Link : c_start_period start_period@bp
Link : c_score score@bp
Link : c_end_game end_game@bp
Link : game_on@bp c_game_on
Link : game_score@bp c_game_score

