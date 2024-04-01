:- consult('utils.pl').
:- consult('kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the main functions of the game

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Get the map element given the position (I, J)
get_element(I, J, N, Map, Element):-
    nth0(I, Map, Row),
    nth0(J, Row, Element).

% -1 = Out of bonds
get_element(I, J, N, Map, -1).

% Main function for the agent.
% Do the map search looking for a safe path to gold.
search(I, J, N, KB, Map, Init_Path, End_Path, Status):- 
    get_element(I, J, N, Map, Element),
    (
        Element = 3 ->
        write('You won!'), nl(),
        Status = won
    ;
        Element = 2 ->
        write('You Lose T-T'), nl(),
        Status = lose
    ;
        Element = 1 ->
        breeze_index(I, J, N, Index),
        tell(KB, Index, New_KB),
        next_indexes(I, J, N, Next_I, Next_J), !,
        search(Next_I, Next_J, N, New_KB, Map, Init_Path, End_Path, Status)
    ;
        Element = 0 ->
        breeze_index(I, J, N, Index),
        tell(KB, -Index, New_KB),
        next_indexes(I, J, N, Next_I, Next_J), !,
        search(Next_I, Next_J, N, New_KB, Map, Init_Path, End_Path, Status)
    ).

% Base cases
search(I, J, N, KB, Map, Init_Path, End_Path, Status):-
    next_indexes(I, J, N, Next_I, Next_J), !,
    search(Next_I, Next_J, N, KB, Map, Init_Path, End_Path, Status).

search(I, J, N, KB, Map, Init_Path, Init_Path, won):-
    true.

search(I, J, N, KB, Map, Init_Path, Init_Path, lose):-
    fail.