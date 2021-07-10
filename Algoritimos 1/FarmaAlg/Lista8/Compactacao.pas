program compactacao;
type vetor = array[0..100] of integer;
var linha, valor, tamanho_vet1, tamanho_vet2, i: integer;
    vet1, vet2: vetor;

procedure veri_distinto(var vet1, vet2: vetor; valor, tamanho_vet1: integer; var tamanho_vet2: integer);
var i: integer;
    new: boolean;
begin
  new := true;
  for i := 0 to tamanho_vet2 - 1 do begin
    if valor = vet1[i] then
      new := false;
  end;
  if new then begin
    vet2[tamanho_vet2] := valor;
    tamanho_vet2 := tamanho_vet2 + 1;
  end;
end;

procedure print_arrays(var vet1, vet: vetor; tamanho_vet1, tamanho_vet2: integer);
var pos: integer;
begin
  write('O: ');
  for pos := 0 to tamanho_vet1 - 1 do begin
    write(vet1[pos], ' ');
  end;
  writeln(' ');
  write('C: ');
  for pos := 0 to tamanho_vet2 - 1 do begin
    write(vet2[pos], ' ');
  end;
  writeln(' ');
end;

procedure clean_vet(var vet1, vet2: vetor; var tamanho_vet1, tamanho_vet2: integer);
var i: integer;
begin
  for i := 0 to tamanho_vet1 do begin
    vet1[i] := 0;
  end;
  for i := 0 to tamanho_vet2 do begin
    vet2[i] := 0;
  end;
  tamanho_vet1 := 0; tamanho_vet2 := 0;
end;

begin
  read(tamanho_vet1);
  writeln(' ');
  while tamanho_vet1 <> 0 do begin
    i := 0;
      while i < tamanho_vet1 do begin
      read(valor);
      veri_distinto(vet1, vet2, valor, tamanho_vet1, tamanho_vet2);
      vet1[i] := valor;
      i := i + 1;
    end;
    print_arrays(vet1, vet2, tamanho_vet1, tamanho_vet2);
    clean_vet(vet1, vet2, tamanho_vet1, tamanho_vet2);
    read(tamanho_vet1);
  end;
end.