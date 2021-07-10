program Ocorrencias;
type vetor = array[0..100] of integer;
var m, n, count, quantidade, inicio, fim: integer;
    vetN, vetM: vetor;


function eh_iqual(var vetN, vetM: vetor; inicio, fim:integer): integer;
var i, j: integer;
    is_equal: Boolean;
begin
  is_equal := true; j := 0;
  for i := inicio to fim do begin
    if vetN[i] <> vetM[j] then
      is_equal := false;
    j := j + 1;
  end;
  if is_equal then
    eh_iqual := 1
  else
    eh_iqual := 0;
end;

begin
  read(n, m); 
  count := 0; quantidade := 0;
  while count < n do begin
    read(vetN[count]);
    count := count + 1;
  end;
  count := 0;
  while count < m do begin
    read(vetM[count]);
    count := count + 1;
  end;

  for count := 0 to n do begin
    inicio := count;
    fim := count + m - 1;
    quantidade := quantidade + eh_iqual(vetN, vetM, inicio, fim);
  end;
  writeln(quantidade);
end.