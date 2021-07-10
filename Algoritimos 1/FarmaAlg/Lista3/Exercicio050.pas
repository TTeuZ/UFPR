program Exercicio050;

var dividendo, divisor, quant: integer;
    continua: boolean;
begin
  read(dividendo, divisor);
  quant := 0;
  continua := true;

  while (continua) do begin
    if (dividendo mod divisor = 0) then
      quant := quant + 1
    else
      continua := false;

    dividendo := dividendo div divisor;
  end;
  writeln(quant);
end.