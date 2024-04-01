:- consult('kb.pl').
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

% Main function
% N -> Map size
% Map -> Map structure
wumpus(N, Map) :-
    % fill_up_kb(0, 0, N, [], KB),
    search(0, 0, N, KB, Map, [[0, 0]], Path, Status),
    write(KB), nl(),
    write(Path).