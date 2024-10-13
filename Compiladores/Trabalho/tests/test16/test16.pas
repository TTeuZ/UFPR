program proc1 (input, output);
    var x, y: integer;
    procedure p;
        var z:integer;
    
        procedure q;
            begin end;
    
        procedure qq;
            var x: integer;
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
    end;
begin
    batata;
end.
