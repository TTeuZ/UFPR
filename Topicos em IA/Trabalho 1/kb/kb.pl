:- consult('helpers/sat.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the knowledge base functionalities.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bcp(_, [], []).

bcp(L, [C|Cs], Cs1) :-
    bcpl(L, C, []),!,
    bcp(L, Cs, Cs1).

bcp(L, [C|Cs], [C1|Cs1]) :-
    bcpl(L, C, C1),
    bcp(L, Cs, Cs1).

bcpl(L, C, C) :-
    not(member(L, C)),
    L1 is -L,
    not(member(L1, C)).

bcpl(L, C, []) :-
    member(L, C).

bcpl(L, C, C1) :-
    L1 is -L,
    member(L1, C),
    subtract(C, [L1], C1),
    not(C1 = []).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


init_kb :-
    nb_setval(kb, []).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tell_kb([[L]]) :- !,
    nb_getval(kb, KB),
    bcp(L, KB, KB1),
    nb_setval(kb, KB1).

tell_kb(LC) :-
    nb_getval(kb, KB),
    append(KB, LC, KB1),
    nb_setval(kb, KB1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ask_kb(L) :-
    nb_getval(kb, KB),
    L1 is -L,
    not(bcp(L1, KB, KB1)).
    
ask_kb(L) :-
    nb_getval(kb, KB),
    L1 is -L,
    bcp(L1, KB, KB1),
    not(sat(KB1,[],_)).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


write_kb :-
    nb_getval(kb, KB),
    write(KB).