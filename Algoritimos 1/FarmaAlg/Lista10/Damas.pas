program Damas;
type matriz = array[-3..100, -3..100] of integer; 
var m: matriz;

procedure ler_matriz (var w: matriz);
var i,j: integer;
begin
  for i := 1 to 8 do
    for j := 1 to 8 do
      read(w[i,j])
end;

function IntToStr(int: integer): string;
begin
  case int of
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
  end;
end;

function get_right(var m: matriz; linha, coluna: integer): boolean;
var vCasa_destino, vCasa_meio: integer;
begin
  vCasa_meio := m[linha+1, coluna+1]; vCasa_destino := m[linha+2, coluna+2];
  if vCasa_destino = 0 then begin
    if (vCasa_meio = -1 ) or (vCasa_meio = 0) then
      get_right := false
    else 
      get_right := true;
  end else 
    get_right := false;
end;

function get_left(var m: matriz; linha, coluna: integer): boolean;
var vCasa_destino, vCasa_meio: integer;
begin
  vCasa_meio := m[linha+1, coluna-1]; vCasa_destino := m[linha+2, coluna-2];
  if vCasa_destino = 0 then begin
    if (vCasa_meio = -1 ) or (vCasa_meio = 0) then
      get_left := false
    else 
      get_left := true;
  end else 
    get_left := false;
end;

function can_get(var m: matriz; linha, coluna: integer): string;
var linha_texto, coluna_texto: string;
    vCasa_atual: integer;
begin
  linha_texto := IntToStr(linha);
  coluna_texto := IntToStr(coluna);
  vCasa_atual := m[linha, coluna];
  if vCasa_atual = -1 then begin
    if (get_right(m, linha, coluna)) or (get_left(m, linha, coluna)) then
      can_get := linha_texto + '-' + coluna_texto
    else  
      can_get := '0';
  end else 
    can_get := '0';
end;

function walk_right(var m: matriz; linha, coluna: integer): boolean;
var vCasa_destino, vCasa_meio: integer;
begin
  if (coluna + 1 > 8) or (coluna + 2 > 8) then
    walk_right := false
  else begin
    vCasa_destino := m[linha+2, coluna+2]; vCasa_meio := m[linha+1, coluna+1];
    if vCasa_destino = 0 then begin
      if (vCasa_meio = -1 ) or (vCasa_meio = 1) then
        walk_right := false
      else 
        walk_right := true;
    end else 
      walk_right := false;
  end;
end;

function walk_left(var m: matriz; linha, coluna: integer): boolean;
var vCasa_destino, vCasa_meio: integer;
begin
  if (coluna - 2 < 0) or (coluna - 1 < 0) then
    walk_left := false
  else begin
    vCasa_destino := m[linha+2, coluna-2];  vCasa_meio := m[linha+1, coluna-1];
    if vCasa_destino = 0 then begin
      if (vCasa_meio = -1 ) or (vCasa_meio = 1) then
        walk_left := false
      else 
        walk_left := true;
    end else 
      walk_left := false;
  end;
end;

function can_walk(var m: matriz; linha, coluna: integer): string;
var linha_texto, coluna_texto: string;
    vCasa_atual: integer;
begin
  linha_texto := IntToStr(linha);
  coluna_texto := IntToStr(coluna);
  vCasa_atual := m[linha, coluna];
   if vCasa_atual = -1 then begin
     if (walk_right(m, linha, coluna)) or (walk_left(m, linha, coluna)) then
      can_walk := linha_texto + '-' + coluna_texto
    else  
      can_walk := '0';
   end else 
     can_walk := '0';
end;

procedure imprime_resposta (var m: matriz);
var linha, coluna: integer;
    resp_get, resp_walk, resp_stay, linha_texto, coluna_texto: string;
begin
  resp_get := 'tomar: '; resp_walk := 'mover: '; resp_stay := 'ficar: ';
  for linha := 1 to 8 do
    for coluna := 1 to 8 do begin
      if m[linha, coluna] = -1 then begin
        if can_get(m, linha, coluna) <> '0' then
          resp_get := resp_get + ' ' + can_get(m, linha, coluna)
        else if can_walk(m, linha, coluna) <> '0' then
          resp_walk := resp_walk + ' ' + can_walk(m, linha, coluna)
        else begin
          linha_texto := IntToStr(linha);
          coluna_texto := IntToStr(coluna);
          resp_stay := resp_stay + ' ' + linha_texto + '-' + coluna_texto;
        end;
      end;
    end;
  if resp_get = 'tomar: ' then
    resp_get := resp_get + '0';
  if resp_walk = 'tomar: ' then
    resp_walk := resp_walk + '0';
  if resp_stay = 'ficar: ' then
    resp_stay := resp_stay +  '0';
  
  WriteLn(resp_get);
  WriteLn(resp_walk);
  WriteLn(resp_stay);
end;

begin
  ler_matriz(m);
  imprime_resposta(m);
end.