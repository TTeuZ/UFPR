program Exercicio089;

var valor, imposto, distribuidor: Double;

begin
  read(valor);
  distribuidor := (valor*0.28);
  imposto := valor*0.45;
  writeln(trunc(valor+imposto+distribuidor));
end.
