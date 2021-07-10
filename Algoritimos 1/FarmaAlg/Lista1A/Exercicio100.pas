program Exercicio100;

var numero, half: integer;

begin
  read(numero);
  half := (numero div 100) + (numero mod 100);
  if (half*half = numero) then
    writeln('SIM')
  else
   writeln('NAO')
end.