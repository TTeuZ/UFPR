program Exercicio001;
var n,m: longint;

function contrario(n,m: LongInt): Boolean;
var n_vet, m_vet: array[1..10] of LongInt;
    n_mod, n_div, numero_reutilizavel: LongInt;
    posicao, count_n, count_m, i, j: integer;
    resposta: Boolean;
begin
  resposta := true;
// Preenchendo o vetor do primeiro numero e recebendo a quantidade de caracteres
  posicao := 1; count_n := 0; n_mod := 10; n_div := 1;
  while n_div <= n do begin
    numero_reutilizavel := n;
    numero_reutilizavel := numero_reutilizavel mod n_mod;
    numero_reutilizavel := numero_reutilizavel div n_div;
    n_vet[posicao] := numero_reutilizavel;
    count_n := count_n + 1;
    posicao := posicao + 1;
    n_mod := n_mod * 10;
    n_div := n_div * 10;
  end;

// Preenchendo o vetor do segundo numero e recebendo a quantidade de caracteres
  posicao := 1; count_m := 0; n_mod := 10; n_div := 1;
  while n_div <= m do begin
    numero_reutilizavel := m;
    numero_reutilizavel := numero_reutilizavel mod n_mod;
    numero_reutilizavel := numero_reutilizavel div n_div;
    m_vet[posicao] := numero_reutilizavel;
    count_m := count_m + 1;
    posicao := posicao + 1;
    n_mod := n_mod * 10;
    n_div := n_div * 10;
  end;

  if (count_n <> count_m) then begin
    resposta := false;
  end else begin
    j := 1;
    for i := count_n downto 1 do begin
      if (m_vet[j] = n_vet[i]) and resposta then
        resposta := true
      else
        resposta := false;

      j := j + 1;
    end;
  end;
  contrario := resposta;
end;

begin
read (n,m);
if contrario (n,m) then
  writeln (n,' eh o contrario de ',m)
else
  writeln (n,' nao eh o contrario de ',m);
end.