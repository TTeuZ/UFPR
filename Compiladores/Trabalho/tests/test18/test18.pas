program proc1 (input, output);
    var x, y: integer;
    procedure p;
        var z:integer;
    
        procedure q;
            begin end;
    
        procedure qq;
            var a: integer;
            begin
                q;
            end;

        begin
            q;
            qq;
        end;

    procedure batata;
    begin
        p;
        a := 1;
    end;
begin
    batata;
end.
