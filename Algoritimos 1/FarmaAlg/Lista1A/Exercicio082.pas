program Exercicio082;

var segundos, horas, min: longint;

begin
  read(segundos);
  horas := segundos div 3600;
  segundos := segundos mod 3600;
  min := segundos div 60;
  segundos := segundos mod 60;
  writeln(horas,':',min,':',segundos);
end.