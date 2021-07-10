program Vetores006;
type vetor = array[0..200] of real;
var operacao, tamanho_array: integer;
    valor: real;
    vet: vetor;

function busca_binaria(var vet: vetor; valor: real; tamanho: integer): integer;
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

procedure imprime_array(var vet: vetor; tamanho: integer);
var i: integer;
begin
  if tamanho = 0 then
    writeln('vazio')
  else begin
    for i := 1 to tamanho do begin
    write(vet[i]:0:1, ' ');
  end;
  writeln(' ');
  end;
end;

procedure add_array(valor: real; var vet:vetor; var tamanho: integer);
var i: integer;
begin
  if tamanho < 200 then begin
    vet[0] := valor; i := tamanho;
    while valor < vet[i] do begin
      vet[i+1] := vet[i];
      i := i - 1;
    end;
    vet[i+1] := valor;
    tamanho := tamanho + 1;
    imprime_array(vet, tamanho);
  end else begin
    writeln('erro');
  end;
end;

procedure remove_array(valor: real; var vet:vetor; var tamanho: integer);
var pos, i: integer;
begin
  pos := busca_binaria(vet, valor, tamanho);

  if pos = 1000 then
    writeln('erro')
  else begin
    for i := pos to tamanho-1 do begin
    vet[i] := vet[i+1];
  end;
  tamanho := tamanho - 1;
  imprime_array(vet, tamanho);
  end;
end;

begin
  read(operacao);
  tamanho_array := 0;
  while operacao <> 0 do begin
    read(valor);
    case operacao of
      1: begin
        add_array(valor, vet, tamanho_array);
      end;
      2: begin
        remove_array(valor, vet, tamanho_array);
      end;
    end;
    read(operacao);
  end;
  imprime_array(vet, tamanho_array);
end.