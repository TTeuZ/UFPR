program Exercicio087;

var comprimento, largura, area, potencia: Integer;

begin
  read(comprimento);
  read(largura);
  area := comprimento * largura;
  potencia := area * 18;
  writeln(area, ' ', potencia);
end.