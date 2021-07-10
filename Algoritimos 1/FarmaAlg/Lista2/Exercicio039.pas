program Exercicio039;

var n, rep, par: integer;
    multi: longint;
begin
  read(n);

  rep := 0;
  par := 2;
  multi := 1;

  while rep <> n do
    begin
      multi := multi * par;
      par := par + 2;
      rep := rep + 1;
    end;
  writeln(multi);
end.