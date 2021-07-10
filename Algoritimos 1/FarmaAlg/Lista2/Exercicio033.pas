program Exercicio033;

var numeroDeLados, medidaDoLado, equacao: integer;
    tipo: string;

begin
  read(numeroDeLados, medidaDoLado);

  case numeroDeLados of
    3: begin
      tipo := 'TRIANGULO';
      equacao := 3 * medidaDoLado;
    end;
    4: begin
      tipo := 'QUADRADO';
      equacao := medidaDoLado * medidaDoLado;
    end;
    5: begin
      tipo := 'PENTAGONO';
      equacao := 0;
    end;
    else begin
      if (numeroDeLados < 3) or (numeroDeLados > 5) then
        tipo := 'ERRO';
        equacao := 0;
      end;
    end;

    write(tipo);
    if (equacao <> 0) then
      writeln(' ', equacao)
end.