program Subsequencias;
type vetor = array[1..100] of longint;
var n, pos, tam_sub: longint;
    vet: vetor;

procedure preenche_array (n: longint; var vet: vetor);
var count, valor: longint;
begin
  count := 1;
  while count <= n do begin
    read(valor);
    vet[count] := valor;
    count := count + 1;
  end;
end;

function is_equal (var sub1, sub2: vetor; tam_sub, posicao: integer): integer;
var count: integer;
    yes: Boolean;
begin
  count := 1; yes := true;
  while count <= tam_sub do begin
    if (sub1[count] <> sub2[count]) then
      yes := false;
    count := count + 1;
  end;
  if yes then
    is_equal := posicao
  else
    is_equal := 0;
end;

function has_sub (var vet: vetor; tam_vetor, tam_sub: longint): integer;
var sub1, sub2: vetor;
    posicao, posicao_final, count, count_sub1, count_sub2, tamanho, res_count: integer;
begin
  posicao := 1; posicao_final := 0;
  while (posicao <= (tam_vetor - tam_sub)) and (posicao_final = 0) do begin
    count := posicao; tamanho := tam_sub; count_sub1 := 1;
    while count_sub1 <= tam_sub do begin
      sub1[count_sub1] := vet[count];
      count := count + 1;
      count_sub1 := count_sub1 + 1;
    end;
    res_count := count;
    while (tamanho <= tam_vetor) and (posicao_final = 0) do begin
      tamanho := tamanho + tam_sub;
      count_sub2 := 1;
      while count_sub2 <= tam_sub do begin
        sub2[count_sub2] := vet[count];
        count := count + 1;
        count_sub2 := count_sub2 + 1;
      end;
      res_count := res_count + 1;
      count := res_count;

      posicao_final := is_equal(sub1, sub2, tam_sub, posicao);
    end;
    posicao := posicao + 1;
  end;
  has_sub := posicao_final;
end;

begin
  read(n);
  preenche_array(n, vet);

  pos := 0;
  tam_sub := n div 2;

  while (pos = 0) and (tam_sub >= 2) do begin
    pos := has_sub(vet, n, tam_sub);
    tam_sub := tam_sub - 1;
  end;

  if pos > 0 then
    writeln(pos, ' ', tam_sub + 1)
  else
    writeln('nenhuma')
end.