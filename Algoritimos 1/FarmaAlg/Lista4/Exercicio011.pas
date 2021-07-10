program Exercicio011;

var numero, count: longint;
    ehPrimo : boolean;

begin
  read(numero);
  count := 2; ehPrimo := true;
  
  if numero = 0 then
    ehPrimo := false;

  while count < (numero div 2) do begin
    if numero mod count = 0 then
      ehPrimo := false;
    count := count + 1;
  end;

  if ehPrimo then
    writeln('SIM')
  else
    writeln('NAO')
end.