program Exercicio03;

var n, m, p: longint;
    linhaPA, linhaPB, colunaPA, colunaPB, linhaR, colunaR: integer;
    movimentoPA, movimentoPB: integer;
    count, countR: integer;
    estadoR: String;
    resposta: Boolean;

begin
  read(n, m);
  read(p);
  linhaPA := 1; colunaPA := 1; // inicializa o professor A
  linhaPB := n; colunaPB := m; // Inicializa o professor B
  resposta := false;
  count := 1;

  while count <= p do begin
    read(movimentoPA, movimentoPB); // leitura dos movimentos feitos pelos professores
    
    // opçoes de movimento do professor A
    if (movimentoPA = 1) then  // norte
      linhaPA := linhaPA + 1
    else if (movimentoPA = 2) then // sul
      linhaPA := linhaPA - 1
    else if (movimentoPA = 3) then  // leste
      colunaPA := colunaPA + 1
    else  //oeste
      colunaPA := colunaPA - 1;  

    if (movimentoPB = 1) then   // opçoes de movimento do professor B
      linhaPB := linhaPB + 1
    else if (movimentoPB = 2) then 
      linhaPB := linhaPB - 1
    else if (movimentoPB = 3) then 
      colunaPB := colunaPB + 1
    else begin
      colunaPB := colunaPB - 1;
    end;

    if count <= p then begin
      if (linhaPA <= 0) or (colunaPA <= 0) and not resposta then begin
        estadoR := 'PA saiu na posicao (';
        colunaR := colunaPA;
        linhaR := linhaPA;
        countR := count;
        resposta := true;
      end;
      if (linhaPB <= 0) or (colunaPB <= 0) and not resposta then begin
        estadoR := 'PB saiu na posicao (';
        colunaR := colunaPB;
        linhaR := linhaPB;
        countR := count;
        resposta := true;
      end;
      if (linhaPA = linhaPB) and (colunaPA = colunaPB) and not resposta then begin
        estadoR := 'Encontraram-se na posicao (';
        colunaR := colunaPA;
        linhaR := linhaPA;
        countR := count;
        resposta := true;
      end;
    end;

    count := count + 1;
  end;

  if not resposta then
    writeln('Nao se encontraram')
  else 
    writeln(estadoR, colunaR, ',', linhaR, ') no passo ', countR)
end.