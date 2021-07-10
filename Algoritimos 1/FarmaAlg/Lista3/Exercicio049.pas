program Exercicio049;

var salario, min, s1, s2, s3, s4: real;
    quant: integer;

begin
  read(salario);
  s1 := 0;
  s2 := 0;
  s3 := 0;
  s4 := 0;
  min := 0;
  quant := 0;

  while(salario <> 0) do begin
    min := salario / 450.00;
    quant := quant + 1;

    if min > 20 then
      s1 := s1 + 1
    else begin
      if min >= 10 then
        s2 := s2 + 1
      else begin
        if min >= 4 then
          s3 := s3 + 1
        else begin
          if min >= 0 then
          s4 := s4 + 1
        end;
      end;
    end;
    read(salario);
  end;

  s1 := (100*s1) / quant;
  s2 := (100*s2) / quant;
  s3 := (100*s3) / quant;
  s4 := (100*s4) / quant;
  writeln(s4:0:2);
  writeln(s3:0:2);
  writeln(s2:0:2);
  writeln(s1:0:2);
end.