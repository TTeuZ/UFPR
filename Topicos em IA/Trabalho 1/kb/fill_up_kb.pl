:- consult('helpers/utils.pl').
:- consult('kb.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the Knowledge first fill up.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Position helpers
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
is_inside_the_matrix(I, J, N) :-
    I >= 0, I =< N-1,
    J >= 0, J =< N-1.


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
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Add new rules to the KB
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
        is_inside_the_matrix(I, J, N) ->
        center_rule(Breeze_Index, I, J, N, Rule),
        tell_kb(Rule), !
    ).

add_rules(I, J, N). % Base case.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fill up the KB with number values.
% Each value represents an index (either pit or breeze).
fill_up_kb(I, J, N) :-
    add_rules(I, J, N),
    next_indexes(I, J, N, Next_I, Next_J), !,
    fill_up_kb(Next_I, Next_J, N).

fill_up_kb(N, N, N). % Base case.