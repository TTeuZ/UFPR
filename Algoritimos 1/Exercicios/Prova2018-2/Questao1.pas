program Questao1;
type vetor = array[0..200] of integer;
var vet: vetor;
    tamanho, smallest, bigest, sum, sum_f: integer;
    is_balanceada: Boolean;

procedure ordena_vet(var vet: vetor; n: integer);
var j, aux: integer;
begin
  j := 1;
  while j <= n - 1 do begin
    if (vet[j] > vet[j+1]) then begin
      aux := vet[j+1];
      vet[j+1] := vet[j];
      vet[j] := aux;
    end;
    if (vet[j-1] > vet[j]) then begin
      aux := vet[j];
      vet[j] := vet[j-1];
      vet[j-1] := aux;
      j := j - 1;
    end else 
      j := j + 1;
  end;
end;

function fill_array(var vet: vetor): integer;
var count, valor: integer;
begin
  read(valor); count := 0;
  while valor <> 0 do begin
    vet[count] := valor;
    count := count + 1;
    read(valor);
  end;
  count := count - 1;
  ordena_vet(vet, count);
  fill_array := count;
end;

function get_bigest(var vet: vetor; tamanho: integer): integer;
var count, resultado: integer;
begin
  count := 1; resultado := vet[0];
  while count <= tamanho do begin
    if resultado < vet[count] then
      resultado := vet[count];
    count := count + 1;
  end;
  get_bigest := resultado;
end;

function get_smallest(var vet: vetor; tamanho: integer): integer;
var count, resultado: integer;
begin
  count := 1; resultado := vet[0];
  while count <= tamanho do begin
    if resultado > vet[count] then
      resultado := vet[count];
    count := count + 1;
  end;
  get_smallest := resultado;
end;

function busca_binaria(var vet: vetor; valor, tamanho: integer): integer;
var inicio, fim, meio: integer;
begin
  inicio := 1; fim := tamanho;
  meio := (inicio + fim) div 2;
  while (vet[meio] <> valor) and (fim >= inicio) do begin
    if vet[meio] > valor then
      fim := meio - 1
    else
      inicio := meio + 1;
    meio := (inicio + fim) div 2;
  end;
  if vet[meio] = valor then
    busca_binaria := meio
  else
    busca_binaria := 1000;
end;

procedure remove_from_array(var vet: vetor; number: integer; var tamanho: integer);
var pos_number, i: integer;
begin
  pos_number := busca_binaria(vet, number, tamanho);
  for i := pos_number to tamanho-1 do begin
    vet[i] := vet[i+1];
  end;
  tamanho := tamanho - 1;
end;

begin
  tamanho := fill_array(vet); is_balanceada := true;
  bigest := get_bigest(vet, tamanho);
  smallest := get_smallest(vet, tamanho);
  remove_from_array(vet, smallest, tamanho);
  remove_from_array(vet, bigest, tamanho);
  sum_f := bigest + smallest;

  while tamanho > 0 do begin
    bigest := get_bigest(vet, tamanho);
    smallest := get_smallest(vet, tamanho);
    remove_from_array(vet, smallest, tamanho);
    remove_from_array(vet, bigest, tamanho);
    sum := bigest + smallest;
    if sum <> sum_f then
      is_balanceada := false;
  end;

  if is_balanceada then
    writeln('Sim, eh balanceada.')
  else
    Writeln('Nao eh balanceada.')
end.