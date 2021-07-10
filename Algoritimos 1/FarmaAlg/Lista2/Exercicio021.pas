program Exercicio021;

var numero: integer;

begin
  read(numero);
  if (numero mod 7 = 0) then
    if (numero mod 11 = 0) then
      writeln('Multiplo de 7 e de 11.')
    else
      writeln('Multiplo exclusivamente de 7.')
  else
    if (numero mod 11 = 0) then
      writeln('Multiplo exclusivamente de 11.')
    else
      writeln('Nao e multiplo nem de 7 nem de 11.')
end.