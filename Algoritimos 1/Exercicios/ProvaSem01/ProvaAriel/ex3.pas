program ex3;
    var columns, lines, paX, paY, pbX, pbY, meetX, meetY, paLeftX, paLeftY, pbLeftX, pbLeftY, meetStep, paStep, pbStep: longint;
        moves, counter, a, b: integer;
        didNotMeet, paLeft, pbLeft: boolean;
begin
    (*
        1 - Norte;
        2 - Sul;
        3 - Leste;
        4 - Oeste;
    *)
    read(columns, lines);
    read(moves);
    counter:= 0;
    paX:= 1;
    paY:= 1;
    pbX:= columns;
    pbY:= lines;
    didNotMeet:= true;
    paLeft:= false;
    pbLeft:= false;

    while counter < moves do
    begin
        read(a, b);

        if a = 1 then
            paY:= paY + 1
        else if a = 2 then
            paY:= paY - 1
        else if a = 3 then
            paX:= paX + 1
        else if a = 4 then
            paX:= paX - 1;

        if b = 1 then
            pbY:= pbY + 1
        else if b = 2 then
            pbY:= pbY - 1
        else if b = 3 then
            pbX:= pbX + 1
        else if b = 4 then
            pbX:= pbX - 1;

        counter:= counter + 1;
        if(paX = pbX) and (paY = pbY) then
        begin
            didNotMeet:= false;
            meetX:= paX;
            meetY:= paY;
            meetStep:= counter;
        end;
        if ((paX = 0) or (paY = 0) or (paX > columns) or (paY > lines)) then
        begin
            if not paLeft then
            begin
                paLeft:= true;
                paLeftX:= paX;
                paLeftY:= paY;
                paStep:= counter;
            end;
        end;
        if ((pbX = 0) or (pbY = 0) or (pbX > columns) or (pbY > lines)) and not paLeft then
        begin
            if not pbLeft then
            begin
                pbLeft:= true;
                pbLeftX:= paX;
                pbLeftY:= paY;
                pbStep:= counter;
            end;
        end;
    end;

    if not didNotMeet then
        writeln('Encontraram-se na posicao (', meetX, ', ', meetY, ') no passo ', meetStep)
    else 
    begin
        if paLeft then
            writeln('PA saiu na posicao (', paLeftX, ', ', paLeftY, ') no passo ', paStep);
        if pbLeft then
            writeln('PB saiu na posicao (', pbLeftX, ', ', pbLeftY, ') no passo ', pbStep);
    end;
    if not paLeft and not pbLeft and didNotMeet then
        writeln('Nao se encontraram');
end.