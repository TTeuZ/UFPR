Program Exercicio036;

var tipoDoAzulejo, areaAzulejada, areaDoAzulejo: longint;
    quantidadeDeAzulejos: real;

begin
  read(tipoDoAzulejo, areaAzulejada);

  case (tipoDoAzulejo) of
    1: begin
      areaDoAzulejo := 50 * 40;
      areaAzulejada := areaAzulejada * 1000;
      quantidadeDeAzulejos := areaAzulejada / areaDoAzulejo;
    end;
    2: begin
      areaDoAzulejo := 50 * 60;
      areaAzulejada := areaAzulejada * 1000;
      quantidadeDeAzulejos := areaAzulejada / areaDoAzulejo;
    end;
    3: begin
      areaDoAzulejo := 50 * 80;
      areaAzulejada := areaAzulejada * 1000;
      quantidadeDeAzulejos := areaAzulejada / areaDoAzulejo;
    end;
  end;

  writeln(quantidadeDeAzulejos:0:0, ' caixas');
end.