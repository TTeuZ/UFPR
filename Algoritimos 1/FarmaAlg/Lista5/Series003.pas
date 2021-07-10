program Series003;

var count, denominador, numerador: integer;
    soma: real;
begin
  count := 1; denominador := 1; numerador := 1;
  while count <= 5 do begin
    soma := soma + (numerador / denominador);
    numerador := numerador + denominador;
    denominador := denominador + numerador;
    count := count + 1;
  end;
  writeln(soma:0:2);
end.