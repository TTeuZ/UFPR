program Exercicio046;

var nota, media: real;
    peso, todosOsPesos: integer;

begin
  read(nota, peso);

  while (nota <> 0) and (peso <> 0) do begin
    media := media + (nota * peso);
    todosOsPesos := todosOsPesos + peso;
    read(nota, peso);
  end;

  media := media / todosOsPesos;
  writeln(media:0:2);
end.