program Exercicio030;

var codigo, quant: integer;
    valor: real;
begin
  read(codigo, quant);

  case codigo of
    1001: begin
      valor := quant*5.32;
      writeln(valor:0:2);
    end;
    1324: begin
      valor := quant*6.45;
      writeln(valor:0:2);
    end;
    6548: begin
      valor := quant*2.37;
      writeln(valor:0:2);
    end;
    987: begin
      valor := quant*5.32;
      writeln(valor:0:2);
    end;
    7623: begin
      valor := quant*6.45;
      writeln(valor:0:2);
    end;
    else writeln('ERRO')
  end;
end.