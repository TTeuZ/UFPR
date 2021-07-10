program Exercicio019;

var n1, n2, n3, nf: Real;
    faltas: integer;

begin
  read(n1, n2, n3, faltas);

  if faltas >= 10 then
    writeln('NAO')
  else
    begin
      nf := (n1 + n2 + n3) / 3;
      if nf < 4.0 then
        writeln('NAO')
      else
        begin
          if nf < 7.0 then
            writeln('TALVEZ')
          else
            writeln('SIM')
        end;
    end;
end.