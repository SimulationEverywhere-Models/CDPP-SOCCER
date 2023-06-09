[top]
components : tk@Timekeeper bp@BallPlay
in : c_start_game c_score
out : c_start_period c_game_score c_game_on c_end_game

Link : c_score score@bp
Link : end_game@tk end_game@bp
Link : game_on@bp c_game_on
Link : game_score@bp c_game_score
Link : c_start_game start_game@tk
Link : end_game@tk c_end_game
Link : start_period@tk c_start_period
Link : start_period@tk start_period@bp

