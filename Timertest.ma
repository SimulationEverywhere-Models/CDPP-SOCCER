[top]
components : tk@Timekeeper
in : c_start_game
out : c_end_game c_start_period
Link : c_start_game start_game@tk
Link : end_game@tk c_end_game
Link : start_period@tk c_start_period

