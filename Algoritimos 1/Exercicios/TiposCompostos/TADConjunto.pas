program TADConjunto; // tipo abstrato de dados(TAD) TAD = tipos + funçoes
// ------------------------------ TAD Conjunto --------------------------------- //
type conjunto = record
        tam: longint;
        proximo: longint;
        v: array [0..100] of longint;
    end;
var c: conjunto;

// funçoes tecnicas, utilizadas para lidar com o conjunto //
procedure inicializar_Conjunto (var c: conjunto); // inicia um conjunto vazio
begin
  c.tam := 0;
end;

procedure ler (var c: conjunto; tam: longint);
var i, num: longint;
begin
  inicializar_conjunto(c);
  for i := 1 to tam do begin
    read(num);
    inserir_Conjunto(num, c);
  end;
end;

function retirar_um_elemento (var c: conjunto); // retira um elemento aleatorio (no caso o ultimo)
begin
  retirar_um_elemento := c.v[c.tam];
  c.tam := c.tam -1;
end;

procedure iniciar_proximo (var c: conjunto); // inicia um contator que sera usado na função de incrementar proximo
begin
  c.proximo := 1;
end;

function incrementar_proximo (var c: conjunto; var x: longint): Boolean; // incrementa o contador e retorna x por referencia. retorna falso se acabou o conjunto
begin
  if c.proximo <= c.tam then begin
    x := c.v[c.proximo];
    c.proximo := c.proximo + 1;
    incrementar_proximo := true;
  end else
    iniciar_proximo := false;
end;

function busca_binaria (x: longint; c: conjunto): longint;
var ini, fim, meio: longint;
begin
  ini := 1;
  fim := c.tam;
  meio := (ini + fim) div 2;

  while (ini <= fim) and (x <> c.v[meio]) do begin
    if x < c.v=meio then
      fim := meio - 1
    else 
      ini := meio + 1;
    meio := (ini + fim) div 2;
  end;
  if fim < ini then
    busca_binaria := 0
  else  
    busca_binaria := meio;
end;

// funçoes tecnicas, utilizadas para lidar com o conjunto //

function conjunto_vazio (c: conjunto): boolean;
begin
  conjunto_vazio := c.tam = 0;
end;

function cardinalidade (c: conjunto): longint;
begin
  cardinalidade := c.tam;
end;

procedure inserir_conjunto (x: LongInt; var c: conjunto);
var i: LongInt;
begin
  if not pertence (x,c) then begin
    c.v[0] := x;
    i := c.tam;
    while x < c.v[i] do begin
      c.v[i+1] := c.v[i];
      i := i + 1;
    end;
    c.v[i+1] := x;
    c.tam := c.tam + 1;
  end;
end;

procedure remover_conjunto (x: longint; var c: conjunto);
var i, indice: LongInt;
begin
  indice := busca_binaria(x,c);
  if indice <> 0 then begin
    for i := indice to c.tam-1 do
      c.v[i] := c.v[i+1];
    c.tam := c.tam - 1;
  end;
end;

function uniao (c1, c2: conjunto): conjunto;
var i,j,k,l : LongInt; uni: conjunto;
begin
  inicializar_conjunto(uni);
  i := 1; j := 1; k := 0;
  while (i <= c1.tam) and (j <= c2.tam) do begin
    k := k + 1;
    if c1.v[i] < c2.v[j] then begin
      uni.v := c1.v[i];
      i := i + 1;
    end else if c1.v[i] > c2.v[j] then begin
      uni.v[k] := c2.v[j];
      j := j + 1;
    end else begin
      uni.v[k] := c1.v[i];
      i := i + 1; j := j + 1;
    end;
  end;
  for l := i to c1.tam do begin
    k := k + 1; 
    uni.v[k] := c1.v[l];
  end;
  for l := j to c2.tam do begin
    k := k + 1; 
    uni.v[k] := c2.v[l];
  end;
  uni.tam := k;
  uniao := uni;
end;

function interseccao (c1, c2: conjunto): conjunto;
var i, j, k: longint; intersec: conjunto;
begin
inicializar_conjunto(intersec);
i := 1; j := 1; k := 0;
while (i <= c1.tam) and (j <= c2.tam) do
  if c1.v[i] < c2.v[j] then
    i := i + 1
  else begin
    if c1.v[i] > c2.v[j] then
      j := j + 1
    else begin
      k := k + 1;
      intersec.v[k] := c1.v[i];
      i := i + 1; j := j + 1;
    end;
  end;
  intersec.tam := k;
  interseccao := intersec;
end;

function diferenca (c1, c2: conjunto): conjunto;
var i, j, k: longint; dif: conjunto;
begin
  inicializar_conjunto(dif);
  i := 1; j := 1; k := 0;
  while (i <= c1.tam) and (j <= c2.tam) do begin
    if c1.v[i] < c2.v[j] then begin
      k := k + 1;
      dif.v[k] := v1.v[i];
      i := i + 1;
    end else if c1.v[i] > c2.v[j] then begin
      j := j + 1;
    end else begin
      i := i + 1;
      j := j + 1;
    end;
    for j := i to c1.tam do begin
      k := k + 1;
      dif.v[k] := c1.v[j];
    end;
    dif.tam := k;
  end;
  diferenca := dif;
end;

function pertence (x: longint; c: conjunto): boolean;
begin
  pertence := busca_binaria (x, c) <> 0;
end;

function sao_iguais (c1, c2: conjunto): boolean;
var i: longint;
begin
  if c1.tam <> c2.tam then
    sao_iguais := False
  else begin
    i := 1;
    while (i <= c1.tam) and (c1.v[i] = c2.v[i]) do 
      i := i + 1;
    if i < c1.tam then sao_iguais := False
    else sao_iguais := true;
  end;
end;

function contido (c1, c2: conjunto): boolean;
var i, j: longint; ok: boolean;
begin
  if c1.tam > c2.tam then
    contido := false
  else begin
    contido := false; ok := true; i := 1; j := 1;
    while (i <= c1.tam) and (j <= c2.tam) and ok do 
      if c1.v[i] < c2.v[j] then
        ok := false
      else if c1.v[i] > c2.v[j] then
        ok := False
      else begin
        i := i + 1; j := j + 1;
      end;
    if ok and (i > c1.tam) then
      contido := true;
  end;
end;

function copiar_cunjunto (c1: conjunto): conjunto;
var i: longint; c2: conjunto;
begin
  inicializar_conjunto(c2);
  c2.tam := c1.tam;
  for i := 0 to c1.tam do
    c2.v[i] := c1.v[i];
  copiar_cunjunto := c2;
end;

begin
  writeln('cabo');
end.