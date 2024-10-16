:- consult('helpers/utils.pl').
:- consult('kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the Knowledge first fill up.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
center_rule(Breeze_Index, I, J, N, Rule) :-
    I1 is I-1, I2 is I+1, J1 is J-1, J2 is J+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I1, J, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I2, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    pit_index(I, J1, N, Pit3_Index), N_Pit3_Index is -Pit3_Index,
    pit_index(I, J2, N, Pit4_Index), N_Pit4_Index is -Pit4_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index, Pit4_Index],
            [N_Pit1_Index, Breeze_Index],[N_Pit2_Index, Breeze_Index],
            [N_Pit3_Index, Breeze_Index],[N_Pit4_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, top, Rule) :-
    J1 is J-1, J2 is J+1, I1 is I+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I, J2, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    pit_index(I1, J, N, Pit3_Index), N_Pit3_Index is -Pit3_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index],
            [N_Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, left, Rule) :-
    J1 is J+1, I1 is I-1, I2 is I+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    pit_index(I2, J, N, Pit3_Index), N_Pit3_Index is -Pit3_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index],
            [N_Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, bottom, Rule) :-
    J1 is J-1, J2 is J+1, I1 is I-1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I, J2, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    pit_index(I1, J, N, Pit3_Index), N_Pit3_Index is -Pit3_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index],
            [N_Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, right, Rule) :-
    J1 is J-1, I1 is I-1, I2 is I+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    pit_index(I2, J, N, Pit3_Index), N_Pit3_Index is -Pit3_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index],
            [N_Pit3_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, top_left, Rule) :-
    J1 is J+1, I1 is I+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, top_right, Rule) :-
    J1 is J-1, I1 is I+1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, bottom_left, Rule) :-
    J1 is J+1, I1 is I-1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, bottom_right, Rule) :-
    J1 is J-1, I1 is I-1,
    N_Breeze_Index is -Breeze_Index,
    pit_index(I, J1, N, Pit1_Index), N_Pit1_Index is -Pit1_Index,
    pit_index(I1, J, N, Pit2_Index), N_Pit2_Index is -Pit2_Index,
    Rule = [[N_Breeze_Index, Pit1_Index, Pit2_Index],
            [N_Pit1_Index, Breeze_Index], [N_Pit2_Index, Breeze_Index]].

add_rules(I, J, N) :-
    breeze_index(I, J, N, Breeze_Index),
    (
        in_corner(I, J, N, Corner) ->
        corner_rule(Breeze_Index, I, J, N, Corner, Rule),
        tell_kb(Rule), !
    ;
        in_border(I, J, N, Border) ->
        border_rule(Breeze_Index, I, J, N, Border, Rule),
        tell_kb(Rule), !
    ;
        in_center(I, J, N) ->
        center_rule(Breeze_Index, I, J, N, Rule),
        tell_kb(Rule), !
    ).

add_rules(I, J, N).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fill up the KB with the relation with pit or breeze indexes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fill_up_kb(I, J, N) :-
    add_rules(I, J, N),
    next_indexes(I, J, N, Next_I, Next_J), !,
    fill_up_kb(Next_I, Next_J, N).

fill_up_kb(N, N, N).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%