program Exercicio02;

var n, n_inicial, divisor, primo: integer;
    ehPrimo, final: Boolean;


begin
  read(n);
  n_inicial := n;
  primo := 2;
  final := false;
  while not final do begin
    ehPrimo := false;
    while (n mod primo = 0) do begin
      n := n div primo;
      write(primo, ' x ');
      if (n = 1) then begin
        writeln('= ', n_inicial);
        final := true;
      end;
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
end.