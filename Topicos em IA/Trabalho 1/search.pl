:- consult('helpers/utils.pl').
:- consult('kb/kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the main functions of the game

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Do the next move in the maze
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
move([H|T], N, Map, Path) :-
    nth0(0, H, Next_I), nth0(1, H, Next_J),
    pit_index(Next_I, Next_J, N, Index), N_Index is -Index,
    (
        ask_kb(N_Index) ->
        search(Next_I, Next_J, N, Map, Path), !,
        move(T, N, Map, Path)
    ;
        move(T, N, Map, Path)
    ).

move([], N, Map, Path).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Remove possible moves that are already in the path
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
remove_moves_already_in_path([H|T], Path, Filtered) :-
    member(H, Path), !,
    remove_moves_already_in_path(T, Path, Filtered).

remove_moves_already_in_path([H|T], Path, [H|Filtered]) :-
    \+ member(H, Path),
    remove_moves_already_in_path(T, Path, Filtered).

remove_moves_already_in_path([], _, []).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Possible moves from actual location
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
center_moves(I, J, N, Moves) :-
    I1 is I-1, I2 is I+1, J1 is J-1, J2 is J+1,
    Moves = [[I1, J], [I2, J], [I, J1], [I, J2]].


border_moves(I, J, N, top, Moves) :-
    J1 is J-1, J2 is J+1, I1 is I+1,
    Moves = [[I, J1], [I, J2], [I1, J]].

border_moves(I, J, N, left, Moves) :-
    J1 is J+1, I1 is I-1, I2 is I+1,
    Moves = [[I, J1], [I1, J], [I2, J]].

border_moves(I, J, N, bottom, Moves) :-
    J1 is J-1, J2 is J+1, I1 is I-1,
    Moves = [[I, J1], [I, J2], [I1, J]].

border_moves(I, J, N, right, Moves) :-
    J1 is J-1, I1 is I-1, I2 is I+1,
    Moves = [[I, J1], [I1, J], [I2, J]].


corner_moves(I, J, N, top_left, Moves) :-
    J1 is J+1, I1 is I+1,
    Moves = [[I, J1], [I1, J]].

corner_moves(I, J, N, top_right, Moves) :-
    J1 is J-1, I1 is I+1,
    Moves = [[I, J1], [I1, J]].

corner_moves(I, J, N, bottom_left, Moves) :-
    J1 is J+1, I1 is I-1,
    Moves = [[I, J1], [I1, J]].

corner_moves(I, J, N, bottom_right, Moves) :-
    J1 is J-1, I1 is I-1,
    Moves = [[I, J1], [I1, J]].


next_moves(I, J, N, Map, Path) :-
    (
        in_corner(I, J, N, Corner) ->
        corner_moves(I, J, N, Corner, Temp_Moves),
        remove_moves_already_in_path(Temp_Moves, Path, Moves),
        move(Moves, N, Map, Path)
    ;
        in_border(I, J, N, Border) ->
        border_moves(I, J, N, Border, Temp_Moves),
        remove_moves_already_in_path(Temp_Moves, Path, Moves),
        move(Moves, N, Map, Path)
    ;
        in_center(I, J, N) ->
        center_moves(I, J, N, Temp_Moves),
        remove_moves_already_in_path(Temp_Moves, Path, Moves),
        move(Moves, N, Map, Path)
    ).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Main function for the agent.
% Do the map search looking for a safe path to gold.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
search(I, J, N, Map, Path) :- 
    nb_getval(status, Status), Status = 'playing',
    get_element(I, J, N, Map, Element),
    (
        Element = 3 ->
        write('You won!'), nl(),
        append(Path, [[I, J]], New_Path),
        nb_setval(path, New_Path),
        nb_setval(status, won)
    ;
        Element = 2 ->
        write('You Lose T-T'), nl(),
        nb_setval(path, []),
        nb_setval(status, lose)
    ;
        Element = 1 ->
        breeze_index(I, J, N, Index),
        tell_kb([[Index]]),
        append(Path, [[I, J]], New_Path),
        next_moves(I, J, N, Map, New_Path)
    ;
        Element = 0 ->
        breeze_index(I, J, N, Index),
        N_Index is -Index,
        tell_kb([[N_Index]]),
        append(Path, [[I, J]], New_Path),
        next_moves(I, J, N, Map, New_Path)
    ).

% Base cases
search(I, J, N, Map, Path) :-
    nb_getval(status, Status), Status = won.

search(I, J, N, Map, Path) :-
    nb_getval(status, Status), Status = lose.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


write_path :-
    nb_getval(path, Path),
    write(Path).