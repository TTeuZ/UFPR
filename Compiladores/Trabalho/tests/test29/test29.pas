program proc (input, output);
var a, b: integer;
    function f(n:integer; var k:integer): integer;
        begin 
            f := n + k;
        end;
    
    function f2(x:integer): integer;
        begin
            f2 := 2 * x;
        end;

begin
    b := 10;
    a := f(f2(f2(2)), b);
    write(a, b);
end.