program Exercicio015;

var numero, mul, mulRes, divisor: longint;
    numeroDeCasas, soma, i: integer;

begin
  read(numero);
  mul := numero * 37;
  mulRes := mul; numeroDeCasas := 0;

  while mul > 0 do begin
    mul := mul div 10;
    numeroDeCasas := numeroDeCasas + 1;
  end;

  while numeroDeCasas <> 0 do begin
    mul := mulRes;
    divisor := 1;
    for i := 1 to numeroDeCasas do begin
      divisor := divisor * 10;
    end;
    mul := mul mod divisor;
    mul := mul div (divisor div 10);

    soma := soma + mul;

    mul := mulRes;
    numeroDeCasas := numeroDeCasas - 1;
  end;

  if soma = numero then
    writeln('SIM')
  else
    writeln('NAO')
end.