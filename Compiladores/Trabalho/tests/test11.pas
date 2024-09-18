program comandoWhile (input, output);
var a: integer;
begin
    a := 0;

    while (not (a >= 5)) do
    begin
        write (a);
        a := a + 1;
    end;
end.