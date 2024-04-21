%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to utils predicates

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Calculate the index for the breezes in the KB.
% In a 2x2 map, for example, the indexes 1 to 4 are breezes.
breeze_index(I, J, N, Index) :-
    Index is I*N+J+1.

% Calculate the index for the pits in the KB.
% In a 2x2 map, for example, the indexes 5 to 8 are pits.
pit_index(I, J, N, Index) :-
    Index is N*N+I*N+J+1.

% Get the map element given the position (I, J)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
get_element(I, J, N, Map, Element) :-
    nth0(I, Map, Row),
    nth0(J, Row, Element).

% -1 = Out of bonds
get_element(I, J, N, Map, -1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Calculate the next index in the iteration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
next_indexes(I, J, N, I, Next_J) :-
    J < N,
    Next_J is J+1.

next_indexes(I, J, N, Next_I, 0) :-
    I < N,
    Next_I is I+1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Position helpers
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
in_center(I, J, N) :-
    I >= 0, I =< N-1,
    J >= 0, J =< N-1.

in_border(I, J, N, Border) :-
    Temp is N-1,
    (
        I = 0, J > 0, J < Temp ->
        Border = 'top'
    ;
        J = Temp, I > 0, I < Temp ->
        Border = 'right'
    ;
        I = Temp, J > 0, J < Temp ->
        Border = 'bottom'
    ;
        J = 0, I > 0, I < Temp ->
        Border = 'left'
    ).

in_corner(I, J, N, Corner) :-
    Temp is N-1,
    (
        I = 0, J = 0 ->
        Corner = 'top_left'
    ;
        I = 0, J = Temp ->
        Corner = 'top_right'
    ;
        I = Temp, J = 0 ->
        Corner = 'bottom_left'
    ;
        I = Temp, J = Temp ->
        Corner = 'bottom_right'
    ).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%