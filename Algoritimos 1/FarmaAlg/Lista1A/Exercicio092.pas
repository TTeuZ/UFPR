program Exercicio092;

var p1, p2, p3, resultado: Integer;

begin
  read(p1);
  read(p2);
  read(p3);
  resultado := (p1 + (p2*2) + (p3*3)) div 6;
  writeln(resultado);
end.