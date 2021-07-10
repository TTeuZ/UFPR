program Exercicio026;

var area: integer;

begin
  read(area);
  if area <= 3 then
    writeln('80')
  else
    begin
      if area <= 6 then
        writeln('100')
      else
      begin
        area := area - 6;
        area := 100+(area*15);
        writeln(area);
      end;
    end;
end.