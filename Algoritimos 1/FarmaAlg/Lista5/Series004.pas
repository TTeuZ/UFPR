program Series004;

var count, numerador, denominador: integer;
    soma: real;
    indicador: Boolean;

begin
  count := 1; numerador := 1; denominador := 2; indicador := true;

  while count <= 10 do begin
    soma := soma + (numerador / denominador);
    if indicador then begin
      denominador := denominador + 1;
      numerador := denominador + 1;
      indicador := false;
    end
    else begin
      numerador := numerador + 1;
      denominador := numerador + 1;
      indicador := true;
    end;
    count := count + 1;
  end;
  writeln(soma:0:2);
end.