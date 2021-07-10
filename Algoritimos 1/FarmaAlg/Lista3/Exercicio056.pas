program Exercicio056;

var n, m, soma: integer;

begin
  read(n, m);
  if n mod 2 = 0 then
    n := n + 2;

  while n < m do begin
    if n mod 2 = 1 then begin
      soma := soma + (n + 1);
      n := n + 3;
    end
    else begin
      soma := soma + (n);
      n := n + 2;
    end;
  end;
  writeln(soma);
end.