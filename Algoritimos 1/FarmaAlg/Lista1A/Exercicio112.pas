program Exercicio112;

var numero,parOuImpar: Integer;

begin
  Read(numero);
  parOuImpar := numero mod 2;

  If parOuImpar = 1 then
    writeln('IMPAR')
  else 
    writeln('PAR')
    end.
end.