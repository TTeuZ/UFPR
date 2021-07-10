program Vetores004;
type vetor = array[0..200] of integer;
var tamanho_vet1, tamanho_vet2, m, valor, i: integer;
    vet, vet_only: vetor;

procedure veri_distinto(var vet, vet_only: vetor; valor, tamanho_vet1: integer; var tamanho_vet2: integer);
var i: integer;
    new: boolean;
begin
  new := true;
  for i := 0 to tamanho_vet2 do begin
    if valor = vet[i] then
      new := false;
  end;
  if new then begin
    vet_only[tamanho_vet2] := valor;
    tamanho_vet2 := tamanho_vet2 + 1;
  end;
end;

procedure ocorrencia(var vet, vet_only: vetor; pos, tamanho_vet1: integer);
var count, valor, i: integer;
begin
  valor := vet_only[pos]; count := 0;
  for i := 0 to tamanho_vet1 - 1 do begin
    if valor = vet[i] then
      count := count + 1;
  end;
  if count = 1 then
    write(valor, ' ocorre ', count, ' vez')
  else
    write(valor, ' ocorre ', count, ' vezes');
  writeln(' ');
end;

begin
  read(tamanho_vet1);
  m := 0; tamanho_vet2 := 0;

  if tamanho_vet1 = 0 then
    writeln('vetor vazio')
  else begin
    while m < tamanho_vet1 do begin
      read(valor);
      veri_distinto(vet, vet_only, valor, tamanho_vet1, tamanho_vet2);
      vet[m] := valor;
      m := m + 1;
    end;

    if tamanho_vet2 = 1 then
      write('a sequencia tem ', tamanho_vet2, ' numero distinto: ')
    else
      write('a sequencia tem ', tamanho_vet2, ' numeros distintos: ');
    for i := 0 to tamanho_vet2 - 1 do begin
      write(vet_only[i], ' ')
    end;
    writeln(' ');

    for i := 0 to tamanho_vet2 - 1 do begin
      ocorrencia(vet, vet_only, i, tamanho_vet1);
    end;
  end;
end.