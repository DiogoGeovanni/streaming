#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100
#define MAX_NOME 100
#define MAX_FAVORITOS 10

typedef struct {
    int id;
    char titulo[MAX_TITULO];
} Video;

typedef struct {
    int id;
    char nome[MAX_NOME];
    int favoritos[MAX_FAVORITOS];
    int qtd_favoritos;
} Usuario;

void cadastrar_video(Video v) {
    FILE *f = fopen("videos.bin", "ab");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de vídeos.\n");
        return;
    }
    fwrite(&v, sizeof(Video), 1, f);
    fclose(f);
}

void cadastrar_usuario(Usuario u) {
    FILE *f = fopen("usuarios.bin", "ab");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    fwrite(&u, sizeof(Usuario), 1, f);
    fclose(f);
}

void listar_usuarios_com_favoritos() {
    FILE *fu = fopen("usuarios.bin", "rb");
    FILE *fv = fopen("videos.bin", "rb");

    if (!fu || !fv) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Video videos[100];
    int total_videos = 0;

    while (fread(&videos[total_videos], sizeof(Video), 1, fv) == 1) {
        total_videos++;
    }

    Usuario u;
    while (fread(&u, sizeof(Usuario), 1, fu) == 1) {
        printf("Usuário: %s\n", u.nome);
        printf("Vídeos Favoritados:\n");
        for (int i = 0; i < u.qtd_favoritos; i++) {
            int id = u.favoritos[i];
            int encontrado = 0;
            for (int j = 0; j < total_videos; j++) {
                if (videos[j].id == id) {
                    printf("  - %s\n", videos[j].titulo);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("  - [Vídeo com ID %d não encontrado]\n", id);
            }
        }
        printf("\n");
    }

    fclose(fu);
    fclose(fv);
}

void atualizar_video(int id, Video novo_video) {
    FILE *f = fopen("videos.bin", "r+b");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de vídeos.\n");
        return;
    }

    Video v;
    while (fread(&v, sizeof(Video), 1, f) == 1) {
        if (v.id == id) {
            fseek(f, -sizeof(Video), SEEK_CUR);
            fwrite(&novo_video, sizeof(Video), 1, f);
            printf("Vídeo atualizado com sucesso.\n");
            fclose(f);
            return;
        }
    }

    printf("Vídeo com ID %d não encontrado.\n", id);
    fclose(f);
}

void remover_video(int id_remover) {
    FILE *f_antigo = fopen("videos.bin", "rb");
    FILE *f_novo = fopen("videos_tmp.bin", "wb");

    if (!f_antigo || !f_novo) {
        printf("Erro ao abrir arquivos para remoção.\n");
        return;
    }

    Video v;
    int encontrado = 0;
    while (fread(&v, sizeof(Video), 1, f_antigo) == 1) {
        if (v.id != id_remover) {
            fwrite(&v, sizeof(Video), 1, f_novo);
        } else {
            encontrado = 1;
        }
    }

    fclose(f_antigo);
    fclose(f_novo);

    if (encontrado) {
        remove("videos.bin");
        rename("videos_tmp.bin", "videos.bin");
        printf("Vídeo removido com sucesso.\n");
    } else {
        remove("videos_tmp.bin");
        printf("Vídeo com ID %d não encontrado.\n", id_remover);
    }
}

void menu() {
    int opcao;
    do {
        printf("\n====== MENU STREAMING ======\n");
        printf("1 - Cadastrar Vídeo\n");
        printf("2 - Cadastrar Usuário\n");
        printf("3 - Listar Usuários com Vídeos Favoritados\n");
        printf("4 - Atualizar Vídeo\n");
        printf("5 - Remover Vídeo\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Video v;
            printf("ID do vídeo: ");
            scanf("%d", &v.id);
            getchar(); // consumir \n
            printf("Título: ");
            fgets(v.titulo, MAX_TITULO, stdin);
            v.titulo[strcspn(v.titulo, "\n")] = '\0';
            cadastrar_video(v);
        } else if (opcao == 2) {
            Usuario u;
            printf("ID do usuário: ");
            scanf("%d", &u.id);
            getchar(); // consumir \n
            printf("Nome: ");
            fgets(u.nome, MAX_NOME, stdin);
            u.nome[strcspn(u.nome, "\n")] = '\0';
            printf("Quantidade de vídeos favoritos (máx %d): ", MAX_FAVORITOS);
            scanf("%d", &u.qtd_favoritos);
            if (u.qtd_favoritos > MAX_FAVORITOS) u.qtd_favoritos = MAX_FAVORITOS;
            for (int i = 0; i < u.qtd_favoritos; i++) {
                printf("ID do vídeo %d: ", i + 1);
                scanf("%d", &u.favoritos[i]);
            }
            cadastrar_usuario(u);
        } else if (opcao == 3) {
            listar_usuarios_com_favoritos();
        } else if (opcao == 4) {
            int id;
            Video novo;
            printf("ID do vídeo a atualizar: ");
            scanf("%d", &id);
            getchar();
            printf("Novo título: ");
            fgets(novo.titulo, MAX_TITULO, stdin);
            novo.titulo[strcspn(novo.titulo, "\n")] = '\0';
            novo.id = id;
            atualizar_video(id, novo);
        } else if (opcao == 5) {
            int id;
            printf("ID do vídeo a remover: ");
            scanf("%d", &id);
            remover_video(id);
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
