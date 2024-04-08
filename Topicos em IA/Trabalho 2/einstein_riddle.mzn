include "alldifferent.mzn";

% Quantity of options
int: Qty;

% Possible values
enum Nationalities;
enum Colors;
enum Pets;
enum Drinks;
enum Hobbies;

% Array of variables for each enum
array[1..Qty] of var Nationalities: nationalityVars;
array[1..Qty] of var Colors: colorVars;
array[1..Qty] of var Pets: petVars;
array[1..Qty] of var Drinks: drinkVars;
array[1..Qty] of var Hobbies: hobbyVars;

% Constraints to guarantee that all values are diferent
constraint all_different(nationalityVars);
constraint all_different(colorVars);
constraint all_different(petVars);
constraint all_different(drinkVars);
constraint all_different(hobbyVars);

% 1st phrase
constraint forall(i in 1..Qty) (
    (nationalityVars[i] = British) <-> (colorVars[i] = Red)
);

% 2nd phrase
constraint forall(i in 1..Qty) (
    (nationalityVars[i] = Swedish) <-> (petVars[i] = Dogs)
);

% 3rd phrase
constraint forall(i in 1..Qty) (
    (nationalityVars[i] = Danish) <-> (drinkVars[i] = Tea)
);

% 4th phrase
constraint forall(i in 1..Qty) (
    (nationalityVars[i] = German) <-> (hobbyVars[i] = Soccer)
);

% 5th phrase
constraint forall(i in 1..Qty) (
    (colorVars[i] = Green) <-> (drinkVars[i] = Coffee)
);

% 6th phrase
constraint forall(i in 1..Qty) (
    (hobbyVars[i] = Baseball) <-> (petVars[i] = Birds)
);

% 7th phrase
constraint (hobbyVars[1] = Basketball) <-> (petVars[2] = Cats);
constraint (hobbyVars[5] = Basketball) <-> (petVars[4] = Cats);
constraint forall(i in 1..Qty) (
    if i > 1 /\ i < Qty then
        ((hobbyVars[i] = Basketball) <-> (petVars[i+1] = Cats)) \/
        ((hobbyVars[i] = Basketball) <-> (petVars[i-1] = Cats))
    endif
);

% 8th phrase
constraint nationalityVars[1] = Norwegian;

% 9th phrase
constraint forall(i in 1..Qty) (
    (hobbyVars[i] = Violin) <-> (drinkVars[i] = Beer)
);

% 10th phrase
constraint forall(i in 1..Qty) (
    (colorVars[i] = Yellow) <-> (hobbyVars[i] = Piano)
);

% 11th phrase
constraint drinkVars[3] = Milk;

% 12th phrase
constraint (petVars[1] = Horse) <-> (hobbyVars[2] = Piano);
constraint (petVars[5] = Horse) <-> (hobbyVars[4] = Piano);
constraint forall(i in 1..Qty) (
    if i > 1 /\ i < Qty then
        ((petVars[i] = Horse) <-> (hobbyVars[i+1] = Piano)) \/
        ((petVars[i] = Horse) <-> (hobbyVars[i-1] = Piano))
    endif
);

% 13th phrase
constraint colorVars[5] != Green;
constraint forall(i in 1..Qty-1) (
    (colorVars[i] = Green) <-> (colorVars[i+1] = White)
);

% 14th phrase
% constraint (nationalityVars[1] = Norwegian) <-> (colorVars[2] = Blue);
% constraint (nationalityVars[5] = Norwegian) <-> (colorVars[4] = Blue);
% constraint forall(i in 1..Qty) (
%     if i > 1 /\ i < Qty then
%         ((nationalityVars[i] = Norwegian) <-> (colorVars[i+1] = Blue)) \/
%         ((nationalityVars[i] = Norwegian) <-> (colorVars[i-1] = Blue))
%     endif
% );
% It can be simplified to the sentence bellow because the Norwegian lives in the 1st house
constraint colorVars[2] = Blue;

% 15th phrase
constraint (hobbyVars[1] = Basketball) <-> (drinkVars[2] = Water);
constraint (hobbyVars[5] = Basketball) <-> (drinkVars[4] = Water);
constraint forall(i in 1..Qty) (
    if i > 1 /\ i < Qty then
        ((hobbyVars[i] = Basketball) <-> (drinkVars[i+1] = Water)) \/
        ((hobbyVars[i] = Basketball) <-> (drinkVars[i-1] = Water))
    endif
);

solve satisfy;

output [
        "\nHouse \(i):\n" ++
        "   - Nationality: \(show(nationalityVars[i])),\n" ++
        "   - Color: \(show(colorVars[i])),\n" ++
        "   - Pet: \(show(petVars[i])),\n" ++
        "   - Drink: \(show(drinkVars[i])),\n" ++
        "   - Hobby: \(show(hobbyVars[i]))"
        | i in 1..Qty
]