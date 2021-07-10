program Exercicio007;

var coluna, linha: integer;

begin
  read(linha, coluna);

  if linha mod 2 = 1 then begin
    if coluna mod 2 = 1 then
      writeln('BRANCA')
    else
      writeln('PRETA')
  end
  else begin
    if coluna mod 2 = 1 then
      writeln('PRETA')
    else
      writeln('BRANCA')
  end;
end.