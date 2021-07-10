program Exercicio024;

var nascimento, idade: integer;

begin
  read(nascimento);
  idade := (2020-nascimento);
  writeln(idade);
  if idade <= 16 then
    writeln('NAO')
  else
    writeln('SIM');
  if idade >= 18 then 
    writeln('SIM')
  else
    writeln('NAO')
end.