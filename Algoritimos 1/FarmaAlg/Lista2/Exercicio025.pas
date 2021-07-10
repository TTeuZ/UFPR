program Exercicio025;

var dia, mes, ano, idade: integer;

begin
  read(dia, mes, ano);
  idade := 2020 - ano;
  if mes >= 4 then
    if dia >= 29 then
      writeln(idade+1)
    else
      writeln(idade)
  else
    writeln(idade+1)
end.