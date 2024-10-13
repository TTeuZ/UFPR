program proc (input, output);
var a, b: integer;
    function f(n:integer; var k:integer): integer;
        begin 
            f := n + k;
        end;
begin
    b := 10;
    a := f(10, b);
    write(a, b);
end.