program proc (input, output);
var a, b: integer;
    function f(n, k:integer): integer;
        begin 
            f := n + k;
        end;
    
    function fa(x:integer): integer;
        begin
            fa := 2 * x;
        end;

begin
    b := 10;
    a := f(fa(fa(2)), 10 > 0);
    write(a, b);
end.