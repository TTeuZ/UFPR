program Exercicio077;

var numero: integer;

begin
  read(numero);
  numero := numero div 100;
  numero := numero mod 10;
  writeln(numero);
end.