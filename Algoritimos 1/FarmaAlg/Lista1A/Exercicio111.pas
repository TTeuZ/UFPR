program Exercicio111;

var numero: longint;

begin
  read(numero);
  if (numero mod 3 = 0) and (numero mod 7 = 0) then
    writeln('SIM')
  else
    writeln('NAO')
end.