:- consult('kb/fill_up_kb.pl').
:- consult('search.pl').
:- consult('kb/kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Main script to run the Wumpus world AI game.

% About the map:
% 0 -> Empty
% 1 -> Breeze
% 2 -> Pit
% 3 -> Gold

% Run examples
% wumpus(3, [[0, 0, 0], [1, 0, 0], [2, 1, 3]]).
% wumpus(4, [[0, 0, 0, 0], [1, 0, 0, 0], [2, 1, 0, 0], [1, 0, 0, 3]]).
% wumpus(7, [[0, 0, 0, 1, 0, 0, 0], [0, 0, 1, 2, 1, 0, 0], [1, 0, 0, 1, 0, 0, 1], [2, 1, 0, 0, 0, 1, 2], [1, 0, 0, 1, 0, 0, 1], [0, 1, 1, 2, 1, 0, 0], [1, 2, 1, 3, 0, 0, 0]]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
write_path_in_detail([H|T]) :-
    write(' -> '), write(H), 
    write_path_in_detail(T).

write_path_in_detail([]).

write_path :-
    nb_getval(path, Path),
    write('Path'),
    write_path_in_detail(Path).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wumpus(N, Map) :-
    init_kb, nb_setval(status, playing), nb_setval(path, []),
    fill_up_kb(0, 0, N),
    search(0, 0, N, Map, []),
    write_path.