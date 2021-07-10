program Exercicio116;

var numero: longint;

begin
  read(numero);
  if ((abs(numero mod 2) = 1) and (numero < -20)) or ((abs(numero mod 2) = 0) and (numero > 7)) then
    writeln('SIM')
  else
    writeln('NAO')
end.