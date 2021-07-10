program Exercicio038;

var idade: integer;

begin
  read(idade);

  if idade >= 18 then
    writeln('5')
  else begin
    if idade >= 14 then
      writeln('4')
    else begin
      if idade >= 11 then
        writeln('3')
      else begin
        if idade >= 8 then
          writeln('2')
        else begin
          if idade >= 5 then
            writeln('1')
        end;
      end;
    end;
  end;
end.