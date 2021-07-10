program Exercicio101;

var numero, centena, desena, unidade: integer;

begin
  read(numero);
  centena := numero mod 10;
  desena := numero div 10;
  desena := desena mod 10;
  unidade := numero div 100;
  writeln(centena,desena,unidade);
end.