program Questao1;
type vetor = array[-1..100] of integer;
var vet, vet_final: vetor;
    tamanho, tamanho_sub1, tamanho_sub2, tamanho_final, pos_final, count:integer;

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

procedure fill_sub(var vet, vet_sub: vetor; pos, tamanho: integer);
var count, count_sub: integer;
begin
  count := pos; count_sub := 0;
  while count_sub <= tamanho do begin
    vet_sub[count_sub] := vet[count];
    count := count + 1;
    count_sub:= count_sub + 1;
  end;
end;

function find_sub(var vet: vetor; pos, tamanho: integer): integer;
var valor, count, count2, count_final: integer;
    stop: Boolean;
begin
  valor := vet[pos]; count := (pos + 1); stop := true; count_final := 0;
  while (count <= tamanho) and stop do begin
    if (valor = vet[count]) and stop then begin
      count2 := (count + 1);
      while stop do begin
        if valor = vet[count2] then begin
          count := count + 1;
          count_final := count_final + 1;
        end else
          stop := false;
        count2 := count2 + 1;
      end;
    end;
    count := count + 1;
    count_final := count_final + 1;
  end;
  if stop then
    find_sub := 1000
  else 
    find_sub := (count_final);
end;

procedure compare_subs(tamanho_sub2, pos_sub1, pos_sub2: integer; var tamanho_sub1, pos_final, tamanho_final: integer);
begin
   if tamanho_sub1 > tamanho_sub2 then begin
    tamanho_final := tamanho_sub2;
    pos_final := pos_sub2;
  end else begin
    tamanho_final := tamanho_sub1;
  end;
  tamanho_sub1 := tamanho_final;
  pos_sub1 := pos_final;
end;

procedure remove_sub (var vet, vet_sub: vetor; var pos_sub, tamanho_sub, tamanho: integer);
var count, i: integer;
begin
  count := 0;
  while count <= tamanho_sub do begin
    for i := (pos_sub) to (tamanho - 1) do begin
      vet[i] := vet[i+1];
    end;
    tamanho := tamanho - 1;
    count := count + 1;
    pos_sub := pos_sub + 1;
  end;
end;

procedure print_array (var vet: vetor; tamanho: integer);
var i: integer;
begin
  for i := 0 to tamanho do begin
    write(vet[i], ' ');
  end;
  WriteLn(' ');
end;

begin
  tamanho := fill_array(vet); count := 2;

  tamanho_sub1 := find_sub(vet, 0 ,tamanho);
  tamanho_sub2 := find_sub(vet, 1 ,tamanho);
  compare_subs(tamanho_sub2, 0, 1, tamanho_sub1, pos_final, tamanho_final);

  while count <= tamanho do begin
    tamanho_sub2 := find_sub(vet, count ,tamanho);
    compare_subs(tamanho_sub2, 0, count, tamanho_sub1, pos_final, tamanho_final);
    count := count + 1;
  end;
  fill_sub(vet, vet_final, pos_final, tamanho_final);
  remove_sub(vet, vet_final, pos_final, tamanho_final, tamanho);
  
  print_array(vet, tamanho);
end.