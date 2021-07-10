program Series005;

var numerador, n2, denominador, count: integer;
    soma : real;

begin
  count := 1; numerador := 1; denominador := 3;
  while count <= 10 do begin
    soma := soma + (numerador / denominador);
    n2 := numerador;
    numerador := denominador * 2;
    denominador := n2 * 2;
    count := count + 1;
  end;
  writeln(soma:0:2);
end.