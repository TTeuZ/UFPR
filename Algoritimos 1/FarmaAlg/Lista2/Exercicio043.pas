program Exercicio043;

var n, count, soma, impar: integer;

begin
  read(n);

  count := 0;
  soma := 0;
  impar := 1;

  while count <> n do
    begin
      soma := soma + impar;
      impar := impar + 2;
      count := count + 1;
    end;

    writeln(soma);
end.