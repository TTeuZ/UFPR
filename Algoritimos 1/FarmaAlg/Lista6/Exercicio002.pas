program Exercicio002;

var n: longint;

function eh_binario (n: longint): boolean;
var numeroDeCasas, divisor, i: integer;
    n_interagivel, n_res: longint;
    resultado: Boolean;
begin
  n_interagivel := n; n_res := n; numeroDeCasas := 0; resultado := true;
  while n_interagivel > 0 do begin
    n_interagivel := n_interagivel div 10;
    numeroDeCasas := numeroDeCasas + 1;
  end;

  while numeroDeCasas <> 0 do begin
    n := n_res;
    divisor := 1;
    for i := 1 to numeroDeCasas do begin
      divisor := divisor * 10;
    end;
    n := n mod divisor;
    n := n div (divisor div 10);

    if (n > 1) then
      resultado := false;
    
    numeroDeCasas := numeroDeCasas -1;
  end;
  eh_binario := resultado;
end;

begin
    read (n);
    if eh_binario (n) then
        writeln ('sim')
    else
        writeln ('nao');
end.