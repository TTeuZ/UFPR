program Exercicio047;

var resultado, i: longint;

begin
  i := 1;

  while i <= 50 do
    begin
    resultado := resultado + (i*i);
    i := i+1;
    end;
    writeln(resultado);
end. 