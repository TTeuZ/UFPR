program Exercicio035;

var salario, imposto: real;
    faixa: integer;
    
begin
  read(salario);

  if salario > 3582.00 then begin
    imposto := (salario * 0.275);
    faixa := 5;
  end
  else begin
    if salario > 2866.00 then begin
      imposto := (salario * 0.225);
      faixa := 4;
    end
    else begin
      if salario > 2150.00 then begin
        imposto := (salario * 0.15);
        faixa := 3;
      end
      else begin
        if salario > 1424.00 then begin
          imposto := (salario * 0.075);
          faixa := 2;
        end
        else begin
          imposto := 0.00;
          faixa := 1;
        end;
      end;
    end;
  end;

  if salario < 540.00 then
    writeln('NAO')
  else
    writeln(faixa, ' ', imposto:0:2)
end.