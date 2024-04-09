:- consult('kb/kb.pl').
:- consult('kb/fill_up_kb.pl').
:- consult('search.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Main script to run the Wumpus world AI game.

% For the map:
% 0 -> Empty
% 1 -> Breeze
% 2 -> Pit
% 3 -> Gold

% Call example
% wumpus(3, [[0, 0, 0]
%            [1, 0, 1]
%            [2, 1, 3]])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


wumpus(N, Map) :-
    init_kb,
    fill_up_kb(0, 0, N),
    search(0, 0, N, Map, [], Status),
    write_path.