# streaming

## INSTRUÇÕES PARA COMPILAR E EXECUTAR O PROGRAMA DE STREAMING DE VÍDEOS EM C

## 1. SALVAR O ARQUIVO DO PROGRAMA
Salve o código-fonte com o nome: streaming.c

## 2. COMPILAR O PROGRAMA
gcc streaming.c -o streaming

## 3. EXECUTAR O PROGRAMA
./streaming

## 4. USAR O MENU DO PROGRAMA
### Você verá um menu com as seguintes opções:

====== MENU STREAMING ======

1 - Cadastrar Vídeo

2 - Cadastrar Usuário

3 - Listar Usuários com Vídeos Favoritados

4 - Atualizar Vídeo

5 - Remover Vídeo

0 - Sair

# 5. EXEMPLO DE USO

## CADASTRAR VÍDEO
Escolha a opção 1.
Digite o ID do vídeo (ex: 1)
Digite o título do vídeo (ex: Matrix)

## CADASTRAR USUÁRIO
Escolha a opção 2.
Digite o ID do usuário (ex: 101)
Digite o nome do usuário (ex: Ana)
Digite a quantidade de vídeos favoritos (ex: 1)
Digite os IDs dos vídeos favoritados (ex: 1)

## LISTAR USUÁRIOS COM VÍDEOS FAVORITADOS
Escolha a opção 3.
O programa exibirá:
Usuário: Ana
Vídeos Favoritados:
 - Matrix

## ATUALIZAR VÍDEO
Escolha a opção 4.
Digite o ID do vídeo a ser atualizado.
Digite o novo título.

## REMOVER VÍDEO
Escolha a opção 5.
Digite o ID do vídeo que deseja remover.

## SAIR DO PROGRAMA
Escolha a opção 0.

## 6. OBSERVAÇÕES
- Os arquivos binários criados são:
    - videos.bin: armazena os vídeos
    - usuarios.bin: armazena os usuários
- Ao remover um vídeo, um arquivo temporário será criado e o original será substituído.
- Este programa pode ser compilado em qualquer ambiente com suporte a C (Linux, Windows com MinGW, WSL, etc.)

## FIM DAS INSTRUÇÕES
