:- consult('helpers/utils.pl').
:- consult('kb/kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the main functions of the game

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Get the map element given the position (I, J)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
get_element(I, J, N, Map, Element) :-
    nth0(I, Map, Row),
    nth0(J, Row, Element).

% -1 = Out of bonds
get_element(I, J, N, Map, -1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Main function for the agent.
% Do the map search looking for a safe path to gold.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
search(I, J, N, Map, Path, Status):- 
    get_element(I, J, N, Map, Element),
    (
        Element = 3 ->
        write('You won!'), nl(),
        append(Path, [[I, J]], New_Path),
        nb_setval(path, New_Path),
        Status = won
    ;
        Element = 2 ->
        write('You Lose T-T'), nl(),
        nb_setval(path, []),
        Status = lose
    ;
        Element = 1 ->
        breeze_index(I, J, N, Index),
        tell_kb([[Index]]),
        append(Path, [[I, J]], New_Path),
        next_indexes(I, J, N, Next_I, Next_J), !,
        search(Next_I, Next_J, N, Map, New_Path, Status)
    ;
        Element = 0 ->
        breeze_index(I, J, N, Index),
        N_Index is -Index,
        tell_kb([[N_Index]]),
        append(Path, [[I, J]], New_Path),
        next_indexes(I, J, N, Next_I, Next_J), !,
        search(Next_I, Next_J, N, Map, New_Path, Status)
    ).

% Base cases
search(I, J, N, Map, Path, Status) :-
    next_indexes(I, J, N, Next_I, Next_J), !,
    search(Next_I, Next_J, N, Map, Path, Status).

search(I, J, N, Map, Path, won):-
    true.

search(I, J, N, Map, Path, lose) :-
    fail.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


write_path :-
    nb_getval(path, Path),
    write(Path).