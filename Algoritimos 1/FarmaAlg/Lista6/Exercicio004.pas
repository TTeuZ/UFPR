program Exercicio004;

var i: longint;

function eh_primo (i: LongInt): Boolean;
var count: LongInt;
    ehPrimo: Boolean;
begin
  count := 2; ehPrimo := true;
  
  if i = 0 then
    ehPrimo := false;

  while count <= (i div 2) do begin
    if i mod count = 0 then
      ehPrimo := false;
    count := count + 1;
  end;

  eh_primo := ehPrimo;
end;

begin
    for i:= 1 to 10000 do
        if eh_primo (i) then
            writeln (i);
end.