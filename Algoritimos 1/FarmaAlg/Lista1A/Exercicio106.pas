program Exercicio106;

var numero: longint;

begin
  read(numero);
  if numero >= 0 then 
    writeln(numero*numero*numero)
  else
    writeln(numero*numero)
end.