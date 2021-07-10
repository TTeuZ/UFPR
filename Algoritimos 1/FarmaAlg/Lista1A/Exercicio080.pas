program Exercicio080;

var x, y, resultado: real;

begin
  read(x);
  read(y);
  resultado := (x/y) + (y/x);
  writeln(resultado:1:3);
end.