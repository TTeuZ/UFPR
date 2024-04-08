% Calculate the next index in the iteration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
next_indexes(I, J, N, I, Next_J) :-
    J < N,
    Next_J is J+1.

next_indexes(I, J, N, Next_I, 0) :-
    I < N,
    Next_I is I+1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Calculate the index for the breezes in the KB.
% The first run is for the breezes index, so in a 2x2 map, for example, the index 0 to 3 are breezes.
breeze_index(I, J, N, Index) :-
    Index is I*N+J+1.


% Calculate the index for the pits in the KB.
% The second run is for the breezes index, so in a 2x2 map, for example, the index 4 to 7 are breezes.
pit_index(I, J, N, Index) :-
    Index is N*N+I*N+J+1.
