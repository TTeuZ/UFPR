program ex2;
    var n1, n2: longint;
        doesFit: boolean;
begin
    read(n1, n2);
    doesFit:= true;

    while ((n1 > 0) and (n2 > 0)) and doesFit do
    begin
        if (n2 mod 10) <> (n1 mod 10) then
            doesFit:= false;

        n1:= n1 div 10;
        n2:= n2 div 10;
    end;

    if (n2 > 0) and (n1 = 0) then
        doesFit:= false;

    if doesFit then
        writeln('ENCAIXA')
    else
        writeln('NAO ENCAIXA');
    
end.