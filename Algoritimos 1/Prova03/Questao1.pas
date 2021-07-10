program questao1;
const MAX_lINHAS = 100; 
      MAX_COLUNAS = 100;
type imagem_pgm = record
  pixel : array[1..MAX_LINHAS ,1..MAX_COLUNAS] of integer;
  num_linhas, num_colunas, maximo : integer;
end;

var imagem: imagem_pgm;

function IntToStr(int: integer): string; // função improvisada para substiutir int por string, por conta de nao ter encontrado uma função do pascal que executa isso
begin
  case int of
    0: begin
      IntToStr := '0';
    end;
    1: begin
      IntToStr := '1';
    end;
    2: begin
      IntToStr := '2';
    end;
    3: begin
      IntToStr := '3';
    end;
    4: begin
      IntToStr := '4';
    end;
    5: begin
      IntToStr := '5';
    end;
    6: begin
      IntToStr := '6';
    end;
    7: begin
      IntToStr := '7';
    end;
    8: begin
      IntToStr := '8';
    end;
    9: begin
      IntToStr := '9';
    end;
    10: begin
      IntToStr := '10';
    end;
    11: begin
      IntToStr := '11';
    end;
    12: begin
      IntToStr := '12';
    end;
    13: begin
      IntToStr := '13';
    end;
    14: begin
      IntToStr := '14';
    end;
    15: begin
      IntToStr := '15';
    end;
  end;
end;

procedure ler_pgm (var I: imagem_pgm); //Função para ler o arquivo .pgm
var k, j: integer;
    s: string[2];
begin
  readln(s);
  if s = 'P2' then begin
    read(I.num_colunas, I.num_linhas);
    read(I.maximo);
    for k := 1 to I.num_linhas do 
      for j := 1 to I.num_colunas do
        read(I.pixel[k,j])
  end else writeln('Formato invalido');
end;

function pega_seg (var I: imagem_pgm; var  valor_atual, num_seg, k, j: integer): string;
var cLinha, cColuna, num_uns, num_zeros: integer;
    fim_seg : Boolean;
    resposta : string;
begin
  cLinha := k; cColuna := j+1; fim_seg := false; num_seg := num_seg + 1;
  if valor_atual = 1 then begin // verifica se esta iniciando em zero ou em 1, para adicionar corretamente o valor
    num_uns := 1;
    num_zeros := 0;
  end else begin
    num_uns := 0;
    num_zeros := 1;
  end;
  while (cLinha <= I.num_linhas) and not fim_seg do begin // lopping na matriz até finalizar a seguencia
    while (cColuna <= I.num_colunas) and not fim_seg do begin
      if valor_atual = 1 then begin
        if valor_atual = I.pixel[cLinha, cColuna] then
          num_uns := num_uns + 1
        else begin
          valor_atual := 0;
          num_zeros := num_zeros + 1;
        end;
      end else begin
        if valor_atual = I.pixel[cLinha, cColuna] then
          num_zeros := num_zeros + 1
        else
          fim_seg := true;
      end;
      cColuna := cColuna + 1;
    end;
    if cColuna >= I.num_colunas then // volta o valor da coluna para 1 se tiver passado o num_max de colunas
      cColuna := 1;
    cLinha := cLinha + 1;
  end;
  if cLinha > k then begin
     k := cLinha;
     j := cColuna;
  end
  else 
    j := cColuna;
  resposta := '[' + IntToStr(num_uns) + ' ' + IntToStr(num_zeros) + '] ';
  pega_seg := resposta;
end;

procedure compacta_pgm (var I: imagem_pgm);
var num_seg, valor_atual, k, j: integer;
    resposta :string;
begin
  resposta := ''; k := 1; j := 1; num_seg := 0;
  while k <= I.num_linhas do begin
    while j <= I.num_colunas do begin
      valor_atual := I.pixel[k,j];
      resposta := resposta + (pega_seg(I, valor_atual, num_seg, k, j)) // Chama a função que pega a proxima seguencia
    end;
    k := k + 1;
  end;
  writeln(num_seg);
  WriteLn(resposta);
end;

begin
  ler_pgm(imagem);
  compacta_pgm(imagem);
end.