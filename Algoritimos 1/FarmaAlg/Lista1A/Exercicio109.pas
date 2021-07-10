program Exercicio109;

var numero: integer;

begin
  read(numero);

  if (30 > numero) and (numero > -15) then
    if numero < 0 then
      writeln(abs(numero))
    else
      writeln('-', numero)
  else
    writeln(numero)
end.