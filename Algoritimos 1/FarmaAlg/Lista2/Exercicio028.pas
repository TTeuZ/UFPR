program Exercicio028;

var f: integer;
    c: real;
begin
  read(f);
  c := ((5*f) - 160) / 9;
  writeln(c:0:2);
  if c >= 100 then
    writeln('gasoso')
  else
    begin
      if c > 0 then
        writeln('liquido')
      else
        writeln('solido')
    end;
end.