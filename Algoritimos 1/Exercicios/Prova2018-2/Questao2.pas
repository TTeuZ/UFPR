program Questao2;
type vetor = array[0..100] of integer;
var vet_geral, vet_rep: vetor;
    tamanho, tamanho_geral, tamanho_rep: integer;

function fill_array(var vet: vetor): integer;
var count, valor, n: integer;
begin
  read(n);
  count := 0;
  while count < n do begin
    read(valor);
    vet[count] := valor;
    count := count + 1;
  end;
  count := count - 1;
  fill_array := count;
end;

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

procedure remove_from_array(var vet: vetor; pos_number: integer; var tamanho: integer);
var i: integer;
begin
  for i := pos_number to tamanho-1 do begin
    vet[i] := vet[i+1];
  end;
  tamanho := tamanho - 1;
end;

procedure remove_repetidos (var vet_geral, vet_rep: vetor; var tamanho, tamanho_geral, tamanho_rep: integer);
var number, count: integer;
begin
  tamanho_rep := 0; count := 0;
  while count <= tamanho do begin
    number := vet_geral[count]; tamanho_geral := count + 1;
    while tamanho_geral <= tamanho do begin
      if number = vet_geral[tamanho_geral] then begin
        vet_rep[tamanho_rep] := vet_geral[tamanho_geral];
        remove_from_array(vet_geral, tamanho_geral, tamanho);
        tamanho_rep := tamanho_rep + 1;
      end;
    tamanho_geral := tamanho_geral + 1;
    end;
    count := count + 1;
  end;
    tamanho_geral := tamanho;
    tamanho_rep := tamanho_rep - 1;
end;

procedure add_vet_geral (var vet_geral, vet_rep: vetor; var tamanho_geral, tamanho_rep: integer);
var count: integer;
begin
  count := 0; tamanho_geral := tamanho_geral + 1;
  while count <= tamanho_rep do begin
    vet_geral[tamanho_geral] := vet_rep[count];
    count := count + 1; tamanho_geral := tamanho_geral + 1;
  end;
end;

procedure print_array (var vet_geral: vetor; tamanho_geral: integer);
var i: integer;
begin
  for i := 0 to (tamanho_geral - 1) do begin
    write(vet_geral[i], ' ');
  end;
  WriteLn(' ');
end;

begin
  tamanho := fill_array(vet_geral);
  remove_repetidos(vet_geral, vet_rep, tamanho, tamanho_geral, tamanho_rep);
  ordena_vet(vet_rep, tamanho_rep);
  add_vet_geral(vet_geral, vet_rep, tamanho_geral, tamanho_rep);
  print_array(vet_geral, tamanho_geral);
end.