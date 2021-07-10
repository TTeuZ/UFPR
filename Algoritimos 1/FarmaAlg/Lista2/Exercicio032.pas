program Exercicio032;

var codigo: integer;
    salario, aumento: real;

begin
  read(salario, codigo);

  case (codigo) of
    101: begin
      aumento := salario * 0.1;
    end;
    102: begin
      aumento := salario * 0.2;
    end;
    103: begin
      aumento := salario * 0.3;
    end;
    else aumento := salario * 0.4;
    end;

    writeln(salario:0:2);
    writeln((salario + aumento):0:2);
    writeln(aumento:0:2);
end.