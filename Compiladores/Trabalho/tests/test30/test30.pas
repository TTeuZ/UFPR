program proc (input, output);
var a, b: integer;
    function f(n:integer; var k:integer): integer;
        begin 
            f := n + k;
        end;
    
    function fa(x:integer): integer;
        begin
            fa := 2 * x;
        end;

begin
    b := 10;
    a := fa(b, 10);
    write(a, b);
end.