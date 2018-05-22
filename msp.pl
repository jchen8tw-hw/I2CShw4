max_sum([],0,0).
max_sum([A|B],Cursum,Maxsum):-
    max_sum( B,Prev_cursum,Prev_maxsum),
    ( (Prev_cursum + A )> 0 -> Cursum is(Prev_cursum+A) ; (Prev_cursum + A ) =< 0 -> Cursum is 0),
    ( (Cursum) > Prev_maxsum -> Maxsum is Cursum ; (Cursum) =< Prev_maxsum ->  Maxsum is Prev_maxsum).
maxsum(L,M):-
    max_sum(L,K,M).    
