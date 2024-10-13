program cmdIf (input, output);
var a: integer;       
begin
    read(a);
    if (a > 10) then
        if (a < 20) then
            write(1)
        else
            write(2)
    else 
        write(0);           
end. 