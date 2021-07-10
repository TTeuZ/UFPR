program Primos;

var ehPrimo: Boolean;
    primo, divisor: integer;

begin
  read(primo);
  ehPrimo := false;

  while not ehPrimo do begin
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
  writeln(primo);
end.
