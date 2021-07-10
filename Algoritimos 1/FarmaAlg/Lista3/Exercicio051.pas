program Exercicio051;

var n: integer;
    resultado: longint;

begin
  read(n);
  resultado := 0;

  if n <= 0 then
    writeln('erro')
  else begin
    while n <> 0 do begin
      resultado := resultado + (n*n*n);
      n := n - 1;
    end;

    writeln(resultado);
  end;
end.