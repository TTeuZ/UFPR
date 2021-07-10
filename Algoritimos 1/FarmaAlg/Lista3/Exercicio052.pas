program Exercicio052;

var m, i, numero: integer;
    numeroArray: array[1..100] of integer;
begin
  read(m);
  for i := 1 to m do begin
    read(numero);
    numeroArray[i] := numero;
  end;

  i := 0;

  while i <> m do begin
    numero := numero + numeroArray[i];
    i := i + 1;
  end;
  numero := numero div m;
  writeln(numero);
end.