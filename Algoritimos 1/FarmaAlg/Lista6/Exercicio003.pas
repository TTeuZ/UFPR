program Exercicio003;
var n: longint;

function converte_em_decimal (n: Longint): LongInt;
var n_mod, n_div, n_reutilizavel, sum, baseDois: LongInt;
    potencia, i: Integer;
begin
    n_mod := 10; n_div := 1; sum := 0;  potencia := 0;

    while n_div <= n do begin
        n_reutilizavel := n; baseDois := 2;
        n_reutilizavel := n_reutilizavel mod n_mod;
        n_reutilizavel := n_reutilizavel div n_div;

        if potencia = 0 then
          baseDois := 1
        else begin
          for i := 1 to (potencia - 1) do begin
            baseDois := baseDois * 2;
          end;
        end;

        sum := sum + (n_reutilizavel * baseDois);

        n_mod := n_mod * 10;
        n_div := n_div * 10;
        potencia := potencia + 1;
    end;

    converte_em_decimal := sum;
end;
begin
    read (n);
    writeln (converte_em_decimal (n));
end.