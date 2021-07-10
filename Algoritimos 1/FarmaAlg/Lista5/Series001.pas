program Series001;

var limitador, count, numerador, sinal: integer;
    soma: real;

begin
  read(limitador);
  count := 1; numerador := 1000; sinal := 1;

  while count <= limitador do begin
    soma := soma + (sinal * (numerador / count));
    numerador := numerador - 3;
    sinal := sinal * (-1);
    count := count + 1;
  end;
  writeln(soma:0:2);
end.