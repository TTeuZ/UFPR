program Exercicio007;
var n: longint;

procedure incrementa (var n: longint);
begin
  n := n + 1;
end;

begin
    n:= 1;
    while n <= 10 do
    begin
        writeln (n);
        incrementa (n);
    end;
end.