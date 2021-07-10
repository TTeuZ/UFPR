program Registros; // pode se criar um array de variaveis compostas(objetos)

type cliente = record // cria uma variavel composta por diversas outras variaveis, literalmente um objeto
        nome: string[50];
        fone: longint;
        endereco: string[100];
        sexo: char;
        idade: integer;
        rg: longint;
        cpf: string[20];
    end;
    bd = array[1..10] of cliente;

procedure imprime_cliente (c: cliente);
begin
  with c do begin // o comando with, faz automaticamente o c.nome, etc.
    writeln(nome);
    writeln(fone);
    writeln(endereco);
    writeln(sexo);
    writeln(idade);
    writeln(rg);
    writeln(cpf);
  end;
end;

// ---------------------------------------------- //
procedure troca (var v: bd; k,m: integer);
var aux: cliente;
begin
  with aux do begin
    nome := v[k].nome;
    fone := v[k].fone;
    endereço := v[k].endereço;
    idade := v[k].idade;
    rg := v[k].rg;
    cpf := v[k].cpf;
  end;
  with v[k] do begin
    nome := v[m].nome;
    fone := v[m].fone;
    endereço := v[m].endereço;
    idade := v[m].idade;
    rg := v[m].rg;
    cpf := v[m].cpf;
  end;
  with v[m] do begin
    nome := aux.nome;
    fone := aux.fone;
    endereço := aux.endereço;
    idade := aux.idade;
    rg := aux.rg;
    cpf := aux.cpf;
  end;
end;


procedure ordena_por_cpf (var v: bd; tam: integer);
var i, j, pos_menor: integer;
begin
  for i := 1 to tam-1 do begin
    pos_menor := i;
    for j := i+1 to tam do
      if v[j].cpf < v[pos_menos].cpf then
        pos_menor := j;
      troca (v, i, pos_menor);
  end;
end;

// ---------------------------------------------- //

begin
  writeln('cabo');
end.