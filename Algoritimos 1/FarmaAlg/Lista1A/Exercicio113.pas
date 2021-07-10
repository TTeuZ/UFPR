program Exercicio113;

var salario, prestacao: integer;
    porcent: Real;
begin
  read(salario, prestacao);
  porcent := salario * 0.30;
  if prestacao > porcent then
    writeln('NAO')
  else
    writeln('SIM')
end.