program cmdIf (input, output);
var a: integer;       
begin
    read(a);
    if (a > 10) then
        write(1)
    else if (a > 5) then
        write(2)
    else
        write(3);            
end. 