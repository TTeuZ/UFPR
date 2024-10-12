program proc (input, output);
var a: integer;
    procedure q;
        begin end;

    procedure p(var a, b: integer; c, d: integer; var e, f: integer);
        var x, y: integer;
        begin 
            q;
        end;

begin
    a:= 0;

    p(a, a, 1, 1, a, 1);
end.