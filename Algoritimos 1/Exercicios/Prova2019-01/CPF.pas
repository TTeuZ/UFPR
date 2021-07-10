program CPF;
type vetor = array[0..100] of integer;
     vetorF = array[0..100] of int64;
var user_cpf: int64;
    tamanho, verificador, valido, count, i: integer;
    cpf_array: vetor;
    all_cpfs: vetorF;

// função que preenche um array com os valores oferecidos
procedure fill_array (var vet: vetorF; pos: integer; valor: int64);
begin
  vet[pos] := valor;
end;

//função que recebe um numero e preenche um array com os numeros, retornando o tamanho do array
function fill_array_with_digitos (var vet: vetor; numero: int64): integer;
var numero_res, divisor: int64;
    numeroDeCasas, i, count: int64;
begin
  numero_res := numero; count := 0; numeroDeCasas := 0;
  while numero > 0 do begin
    numero := numero div 10;
    numeroDeCasas := numeroDeCasas + 1;
  end;
  while numeroDeCasas <> 0 do begin
    numero := numero_res;
    divisor := 1;
    for i := 1 to numeroDeCasas do begin
      divisor := divisor * 10;
    end;
    numero := numero mod divisor;
    numero := numero div (divisor div 10);

    vet[count] := numero;

    numero := numero_res;
    count := count + 1;
    numeroDeCasas := numeroDeCasas - 1;
  end;
  fill_array_with_digitos := count - 1;
end;

function digito_verificador (var vet: vetor; tamanho: integer): integer;
var mul, multiplicador, resto: longint;
begin
  multiplicador := 2; mul := 0;
  while tamanho >= 0 do begin
    mul := mul + (vet[tamanho] * multiplicador);
    multiplicador := multiplicador + 1;
    tamanho := tamanho - 1;
  end;

  resto := Trunc(mul mod 11);

  if resto < 2 then
    digito_verificador := 0
  else
    digito_verificador := (11 - resto)
end;

begin
  read(user_cpf); count := 0;
  while (user_cpf <> 0) do begin
    tamanho := fill_array_with_digitos(cpf_array, user_cpf);
    verificador := digito_verificador(cpf_array, 8);
    if (verificador = cpf_array[9]) then begin
      verificador := digito_verificador(cpf_array, 9);
      if (verificador = cpf_array[10]) then begin
        valido := 1
      end else begin
        valido := 0;
      end;
    end else begin
      valido := 0;
    end;
    fill_array(all_cpfs, count, user_cpf);
    count := count + 1;
    fill_array(all_cpfs, count, valido);
    count := count + 1;
    read(user_cpf);
  end;
  count := count - 1;
  while count > -1 do begin
    write(all_cpfs[count - 1], ' ');
    if (all_cpfs[count] = 1) then
      writeln('valido')
    else
      WriteLn('invalido');
    count := count - 2;
  end;
end.