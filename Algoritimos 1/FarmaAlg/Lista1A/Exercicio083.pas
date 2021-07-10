program Exercicio083;

var idadeEmDias, dias, meses, anos: integer;

begin
  read(idadeEmDias);
  anos := idadeEmDias div 365;
  idadeEmDias := idadeEmDias - anos*365;
  meses := idadeEmDias div 30;
  idadeEmDias := idadeEmDias - meses*30;
  dias := idadeEmDias;
  Writeln(anos,' ', meses ,' ',dias,' ');
end.