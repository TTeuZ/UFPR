%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Script related to the Knowledge base generation and use.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fill up the KB with number values.
% Each value represents an index (either pit or breeze).
fill_up_kb(I, J, N, Init_KB, End_KB) :-
    add_rules(I, J, N, Init_KB, Temp_KB),
    next_indexes(I, J, N, Next_I, Next_J), !,
    fill_up_kb(Next_I, Next_J, N, Temp_KB, End_KB).

fill_up_kb(N, N, N, Init_KB, Init_KB). % Base case.


% Calculate the index for the breezes in the KB.
% The first run is for the breezes index, so in a 2x2 map, for example, the index 0 to 3 are breezes.
breeze_index(I, J, N, Index) :-
    Index is I*N+J+1.


% Calculate the index for the pits in the KB.
% The second run is for the breezes index, so in a 2x2 map, for example, the index 4 to 7 are breezes.
pit_index(I, J, N, Index) :-
    Index is N*N+I*N+J+1.


% Calculate the next index in the iteration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
next_indexes(I, J, N, I, Next_J) :-
    J < N-1,
    Next_J is J+1.

next_indexes(I, J, N, Next_I, 0) :-
    I < N-1,
    Next_I is I+1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Position helpers
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
in_corner(I, J, N, Corner) :-
    Temp is N-1,
    (
        I = 0, J = 0 ->
        Corner = 'top_left'
    ;
        I = 0, J = Temp ->
        Corner = 'top_rigt'
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
add_rules(I, J, N, Init_KB, End_KB) :-
    (
        in_corner(I, J, N, Corner) ->
        write('Corner '), write(Corner),
        corner_rule(I, J, Corner, Rule),
        append(Init_KB, [Rule], End_KB), !
    ;
        in_border(I, J, N, Border) ->
        write('Border '), write(Border),
        border_rule(I, J, Border, Rule),
        append(Init_KB, [Rule], End_KB), !
    ;
        write('center'),
        center_rule(I, J, Rule),
        append(Init_KB, [Rule], End_KB), !
    ),
    nl().

corner_rule(I, J, Corner, Rule) :-
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Add new rules to the KB
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% is_not_border(I, J, N) :-
%     I > 0,
%     J > 0,
%     I < N-1,
%     J < N-1.

% add_rules(I, J, N, Init_KB, End_KB) :-
%     is_not_border(I, J, N),
%     I1 is I-1,
%     I2 is I+1,
%     J1 is J-1,
%     J2 is J+1,
%     breeze_index(I, J, N, Breeze_Index),
%     pit_index(I1, J, N, Pit1_Index),
%     pit_index(I2, J, N, Pit2_Index),
%     pit_index(I, J1, N, Pit3_Index),
%     pit_index(I, J2, N, Pit4_Index),
%     Cs = [[-Breeze_Index, Pit1_Index, Pit2_Index, Pit3_Index, Pit4_Index],
%             [-Pit1_Index, Breeze_Index],[-Pit2_Index, Breeze_Index],
%             [-Pit3_Index, Breeze_Index],[-Pit4_Index, Breeze_Index]],
%     append(Init_KB, Cs, End_KB).

% add_rules(I, J, N, Init_KB, Init_KB). % Base case.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%