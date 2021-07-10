program MDC;

var n1, countn1, n2, countn2, countF, resultado, primo, divisor, mul, i: integer;
    ehPrimo: boolean;

begin
  read (n1, n2);
  resultado := 1; primo := 2;

  while (n1 <> 1) or (n2 <> 1) do begin
    countn1 := 0; countn2 := 0; ehPrimo := false; mul := 1;

    while (n1 mod primo = 0) do begin  // calcula a quantidade de vezes que o n1 e divisivel pelo primo
      n1 := n1 div primo;
      countn1 := countn1 + 1;
    end;
    while (n2 mod primo = 0) do begin // calcula a quantidade de vezes que o n2 e divisivel pelo primo
      n2 := n2 div primo;
      countn2 := countn2 + 1;
    end;
    
    if countn1 > countn2 then  // pega a menor quantidade de vezes (parte igual para os dois)
      countF := countn2
    else
      countF := countn1;

    for i := 1 to countF do begin // calcula o primo elevado a quantidade(countF)
      mul := mul * primo;
    end;

    resultado := resultado * (mul);  // armazena no resultado do mvc, a multiplicação pela proxima etapa

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
  WriteLn(resultado);
end.