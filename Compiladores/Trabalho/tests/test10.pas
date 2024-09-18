program comandoWhile (input, output);
var a, b: integer;
begin
    a := 0;
    while (a < 3) do
    begin
        b := 0;
        while (b < 3) do
        begin
            write (a, b);
            b := b + 1;
        end;
        a := a + 1;
    end;
end.