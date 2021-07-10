program Exercicio061;

var n, primeiro, segundo: integer;

begin
  read(n);
  primeiro := 1;
  segundo := n -1;

  while primeiro < n do begin
    if (primeiro + segundo = n) then
      writeln(primeiro, ' ', segundo);

    primeiro := primeiro + 1;
    segundo := segundo - 1;
  end;
end.