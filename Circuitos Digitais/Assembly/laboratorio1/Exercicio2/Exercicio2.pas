program exercicio2;
type 
    vetor = array[1..8] of integer;

var
    a, b, c: vetor;
    i: integer;

begin
    i := 1;
    while i <= 8 do
    begin
        a[i] := i;
        i := i + 1;
    end;

    i := 1;
    while i <= 8 do
    begin
        b[i] := i;
        i := i + 1;
    end; 

    i := 1;
    while i <= 8 do
    begin
        c[i] := a[i] + b[i];
        writeln(c[i]);
        i := i + 1;
    end; 
end.