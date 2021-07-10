program Exercicio041;

var n, soma, count, n1, n2, nx: longint;

begin
  read(n);

  count := 0;

  n1 := 0;
  nx := 1;
  n2 := 1;
  soma := 0;

  while count <> n do
    begin
      soma := soma + n1;

      n1 := nx;
      nx := n2;
      n2 := n1 + n2;

      count := count + 1;
    end;
  writeln(soma);
end.