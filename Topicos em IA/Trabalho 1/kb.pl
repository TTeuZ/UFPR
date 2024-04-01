:- consult('utils.pl').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the Knowledge base generation and use.

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
    pit_index(I1, J, N, Pit1_Index),
    pit_index(I2, J, N, Pit2_Index),
    pit_index(I, J1, N, Pit3_Index),
    pit_index(I, J2, N, Pit4_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index, Pit4_Index],
            [-Pit1_Index, Breeze_Index],[-Pit2_Index, Breeze_Index],
            [-Pit3_Index, Breeze_Index],[-Pit4_Index, Breeze_Index]].


corner_rule(Breeze_Index, I, J, N, top_left, Rule) :-
    J1 is J+1, I1 is I+1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, top_right, Rule) :-
    J1 is J-1, I1 is I+1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, bottom_left, Rule) :-
    J1 is J+1, I1 is I-1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index]].

corner_rule(Breeze_Index, I, J, N, bottom_right, Rule) :-
    J1 is J-1, I1 is I-1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index]].


border_rule(Breeze_Index, I, J, N, top, Rule) :-
    J1 is J-1, J2 is J+1, I1 is I+1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I, J2, N, Pit2_Index),
    pit_index(I1, J, N, Pit3_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index],
            [-Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, left, Rule) :-
    J1 is J+1, I1 is I-1, I2 is I+1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    pit_index(I2, J, N, Pit3_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index],
            [-Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, bottom, Rule) :-
    J1 is J-1, J2 is J+1, I1 is I-1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I, J2, N, Pit2_Index),
    pit_index(I1, J, N, Pit3_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index],
            [-Pit3_Index, Breeze_Index]].

border_rule(Breeze_Index, I, J, N, right, Rule) :-
    J1 is J-1, I1 is I-1, I2 is I+1,
    pit_index(I, J1, N, Pit1_Index),
    pit_index(I1, J, N, Pit2_Index),
    pit_index(I2, J, N, Pit3_Index),
    Rule = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index],
            [-Pit1_Index, Breeze_Index], [-Pit2_Index, Breeze_Index],
            [-Pit3_Index, Breeze_Index]].


add_rules(I, J, N, Init_KB, End_KB) :-
    breeze_index(I, J, N, Breeze_Index),
    (
        in_corner(I, J, N, Corner) ->
        corner_rule(Breeze_Index, I, J, N, Corner, Rule),
        append(Init_KB, Rule, End_KB), !
    ;
        in_border(I, J, N, Border) ->
        border_rule(Breeze_Index, I, J, N, Border, Rule),
        append(Init_KB, Rule, End_KB), !
    ;
        is_inside_the_matrix(I, J, N) ->
        center_rule(Breeze_Index, I, J, N, Rule),
        append(Init_KB, Rule, End_KB), !
    ).

add_rules(I, J, N, Init_KB, Init_KB). % Base case.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fill up the KB with number values.
% Each value represents an index (either pit or breeze).
fill_up_kb(I, J, N, Init_KB, End_KB) :-
    add_rules(I, J, N, Init_KB, Temp_KB),
    next_indexes(I, J, N, Next_I, Next_J), !,
    fill_up_kb(Next_I, Next_J, N, Temp_KB, End_KB).

fill_up_kb(N, N, N, Init_KB, Init_KB). % Base case.

% Add a new clause to the KB
tell(KB, Index, New_KB):-
    Rule = [Index],
    append(KB, Rule, New_KB).
