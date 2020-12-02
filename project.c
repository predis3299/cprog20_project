#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20
typedef struct node {
	char name[SIZE];
	char singer[SIZE];
	char album[SIZE];
	int title;
	int listen;
	int heart;
	struct node *next;
} music;

void add_music() {
	char name[SIZE], singer[SIZE], album[SIZE];
	FILE *fp = NULL;
	fp = fopen("musics.txt", "a");

	while(1) {
		printf("추가할 노래의 정보를 입력하세요\n");
		printf("입력을 그만하려면 -1을 입력하세요\n");
		printf("제목 : ");
		scanf("%s", name); getchar();
		if(strcmp(name, "-1") == 0) break;
		printf("가수 : ");
		scanf("%s", singer); getchar();
		if(strcmp(singer, "-1") == 0) break;
		printf("앨범 : ");
		scanf("%s", album); getchar();
		if(strcmp(album, "-1") == 0) break;
		fprintf(fp, "%s %s %s %d %d %d\n", name, singer, album, 0, 0, 0);
	}
	fclose(fp);
}

void search_music_name(char *name, music *list_head) {
	music *tmp;
	while(tmp != NULL) {
		if(strcmp(tmp->name, name) == 0) break;
		tmp = tmp->next;
	}
	if(tmp == NULL) {
		printf("없음\n");
		return;
	}
	else printf("제목 : %s %s %s %d %d %d\n", tmp->name, tmp->singer, tmp->album, tmp->title, tmp->listen, tmp->heart);
}

void search_music_singer(char *singer, music *list_head) {
	music *tmp, *tmp2, *prenode, *rmnode;
	while(strcmp(list_head->singer, singer) != 0) {
		rmnode = list_head;
		list_head = list_head->next;
		free(rmnode);
	}
	tmp = list_head;
	tmp2 = list_head;
	prenode = tmp;
	tmp = tmp->next;
	while(tmp != NULL) {
		if(strcmp(tmp->singer, singer) != 0) {
			rmnode = tmp;
			prenode->next = tmp->next;
			tmp = tmp->next;
			free(rmnode);
			continue;
		}
		prenode = tmp;
		tmp = tmp->next;
	}
	int i = 0;
	while(tmp2 != NULL) {
		printf("가수 검색 : %d. %s %s %s %d %d %d\n", i, tmp2->name, tmp2->singer, tmp2->album, tmp2->title, tmp2->listen, tmp2->heart);
		tmp2 = tmp2->next;
		i++;
	}
}

void search_music_album(char *album, music *list_head) {
	music *tmp, *tmp2, *prenode, *rmnode;
	while(strcmp(list_head->album, album) != 0) {
		rmnode = list_head;
		list_head = list_head->next;
		free(rmnode);
	}
	tmp = list_head;
	tmp2 = list_head;
	prenode = tmp;
	tmp = tmp->next;
	while(tmp != NULL) {
		if(strcmp(tmp->album, album) != 0) {
			rmnode = tmp;
			prenode->next = tmp->next;
			tmp = tmp->next;
			free(rmnode);
		}
	}
	while(tmp2) {
		printf("앨범 : %s %s %s %d %d %d\n", tmp2->name, tmp2->singer, tmp2->album, tmp2->title, tmp2->listen, tmp2->heart);
	}
}

void print_nodes(music *list_head) {
	music *tmp = list_head;
	while(tmp != NULL) {
		printf("%s %s %s %d %d %d\n", tmp->name, tmp->singer, tmp->album, tmp->title, tmp->listen, tmp->heart);
		tmp = tmp->next;
	}
}

void search_music_album();
void search_music_listen();
void search_music_heart();

void search_music() {
	char name[SIZE], singer[SIZE], album[SIZE];
	FILE *fp = NULL;
	music *new_node, *tmp_node;
	music *list_head = NULL;

	fp = fopen("musics.txt", "r");
	while(!feof(fp)) {
		new_node = (music*) malloc (sizeof(music));
		fscanf(fp, "%s %s %s %d %d %d\n", new_node->name, new_node->singer, new_node->album, &new_node->title, &new_node->listen, &new_node->heart);
		if(new_node->title == 0) {
			new_node->next = list_head;
			list_head = new_node;
		}
	}
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)) {
		new_node = (music*) malloc (sizeof(music));
		fscanf(fp, "%s %s %s %d %d %d\n", new_node->name, new_node->singer, new_node->album, &new_node->title, &new_node->listen, &new_node->heart);
		if(new_node->title == 1) {
			new_node->next = list_head;
			list_head = new_node;
		}
	}
	fclose(fp);

//	print_nodes(list_head);
/*
	char singer[SIZE];
	printf("singer : ");
	scanf("%s", singer); getchar();
	search_music_singer(singer, list_head);
*/
	int menu;
	printf("===============\n");
	printf("1. 제목으로 검색\n");
	printf("2. 가수 이름으로 검색\n");
	printf("3. 앨범 이름으로 검색\n");
	printf("4. 많이 들은 노래\n");
	printf("5. 좋아요 누른 노래\n");
	printf("===============\n");
	printf("메뉴 : ");
	scanf("%d", &menu); getchar();

	switch(menu) {
		case 1:
			printf("제목 : ");
			scanf("%s", name); getchar();
			search_music_name(name, list_head);
			break;
		case 2:
			printf("가수 : ");
			scanf("%s", singer); getchar();
			search_music_singer(singer, list_head);
			break;
		case 3:
			printf("앨범 : ");
			scanf("%s", album); getchar();
			search_music_album(album, list_head);
			break;
/*		case 4:
			search_music_listen();
			break;
		case 5:
			search_music_heart();
			break;
		default:
			printf("wrong!\n");
			break;*/
	}
}

/*
void search_music_name(struct music m[]) {
	char name[SIZE];
	struct music n_m[arr_SIZE];

	printf("노래 제목 : ");
	scanf("%s", &name); getchar();
*/

int main() {
	int menu;
	printf("================\n");
	printf("0. 프로그램 종료\n");
	printf("1. 노래 추가\n");
	printf("2. 노래 검색\n");
	printf("3. 노래 삭제\n");
	printf("4. 카운트\n");
	printf("================\n");
	printf("메뉴 : ");
	scanf("%d", &menu); getchar();

	switch(menu) {
		case 0:
			return 0;
		case 1:
			add_music();
			break;
		case 2:
			search_music();	
			break;
		//case 3:
		//case 4:
	}


	return 0;
}
