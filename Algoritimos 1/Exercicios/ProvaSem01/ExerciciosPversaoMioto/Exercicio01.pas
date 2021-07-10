program Exercicio01;

var numero, a_numero, e_numero, mul, count, sum: LongInt;
    divi : real;
begin
  read(numero);
  count := 1; sum := numero;

  while numero <> 10000 do begin
    a_numero := numero;
    read(numero);
    e_numero := numero;

    count := count + 1;
    sum := sum + numero;

    divi := a_numero / 2;
    mul := a_numero * 2;

    if (e_numero = divi) or (e_numero = mul) then
      numero := 10000;
  end;

  writeln(count, ' ', sum, ' ', a_numero, ' ', e_numero);
end.