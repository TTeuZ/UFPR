program Exercicio013;

var i, j, k: longint;

begin
  read(i, j, k);
  if (j mod i = 0) and (k mod j = 0) then
    writeln(j + k + i)
  else if (i + 1 = j) and (j + 1 = k) then
    writeln(k, ' ', j, ' ', i)
  else begin
    writeln((i + j + k) div 3)
  end;
end.