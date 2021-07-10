program Exercicio099;

var anos, meses, dias, resultado: integer;

begin
  read(anos);
  read(meses);
  read(dias);

  resultado := (anos*365) + (meses*30) + dias;
  writeln(resultado);
end.