program Exercicio03;

var numero, primo, big_primo, count, big_count, divisor, i, resultado: integer;
    ehPrimo: Boolean;

begin
  read(numero);
  primo := 2; big_primo := 0; big_count := 0;

  while numero <> 1 do begin
    count := 0; ehPrimo := false;

    while (numero mod primo = 0) do begin  // calcula a quantidade de vezes que o n1 e divisivel pelo primo
      numero := numero div primo;
      count := count + 1;
    end;

    if count > big_primo then begin
      big_count := count;
      big_primo := primo;
    end;

    while not ehPrimo do begin  // codigo para encontrar o proximo primo
      divisor := 2;
      primo := primo + 1;
      while divisor < primo do begin
      if primo mod divisor = 0 then begin
        ehPrimo := false;
        divisor := primo;
      end
      else
        ehPrimo := true;
        divisor := divisor + 1;
      end;
    end;
  end;

  resultado := 1;
  for i := 1 to big_count do begin
    resultado := resultado * big_primo;
  end;
  writeln(resultado);
end.