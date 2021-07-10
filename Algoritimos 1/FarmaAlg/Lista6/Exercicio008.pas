program Exercicio008;
var antigo, atual: real;

function aumento_percentual (antigo, atual: real): real;
begin
  aumento_percentual := (((atual * 100)/ antigo) / 100) - 1;
end;

begin
    read (antigo, atual);
    while (antigo <> 0) or (atual <> 0) do
    begin
        writeln (aumento_percentual (antigo, atual):0:2);
        read (antigo, atual);
    end;
end.