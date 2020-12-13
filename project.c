#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 50
typedef struct node {
	char name[SIZE];
	char singer[SIZE];
	char album[SIZE];
	int title;
	int listen;
	int heart;
	struct node *next;
} music;

void add_music();

void search_music();
void search_music_key(char *key, music *head, music *(*pf)(char *, music *));
music *search_music_name(char *name, music *list_head);
music *search_music_singer(char *singer, music *list_head);
music *search_music_album(char *album, music *list_head);
music *search_music_heart(char *heart, music *list_head);

void select_music(music *list_head);
void press_heart(char *name, char *singer, char *album);
void listen_count(char *name, char *singer, char *album);
void remove_music(char *name, char *singer, char *album);

void my_chart();

void print_nodes(music *list_head);
void release_memory(music *list_head);
void save_nodes(music *list_head);
void print_nodes(music *list_head);
music *search_target(music *list_head, char *name, char *singer, char *album);
music *read_file();

void release_memory(music *list_head) {
	music *tmp;
	while(list_head != NULL) {
		tmp = list_head;
		list_head = list_head->next;
		free(tmp);
	}
}

void add_music() {
	char name[SIZE], singer[SIZE], album[SIZE];
	int title;
	FILE *fp = NULL;
	fp = fopen("musics.dat", "a");

	while(1) {
		printf("================\n");
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
		printf("타이틀곡(Y = 1, N = 0) : ");
		scanf("%d", &title); getchar();
		if(title == -1) break;
		fprintf(fp, "%s %s %s %d %d %d\n", name, singer, album, title, 0, 0);
	}
	fclose(fp);
}

music *search_target(music *list_head, char *name, char *singer, char *album) {
	music *tmp;
	tmp = list_head;

	while(tmp != NULL) {
	if((strcmp(tmp->name, name) == 0) && (strcmp(tmp->singer, singer) == 0) && (strcmp(tmp->album, album) == 0)) break;
	tmp = tmp->next;
	}

	return tmp;
}

void save_nodes(music *list_head) {
	music *tmp;
	tmp = list_head;
	FILE *fp = NULL;
	fp = fopen("musics.dat", "w");

	while(tmp != NULL) {
		fprintf(fp, "%s %s %s %d %d %d\n", tmp->name, tmp->singer, tmp->album, tmp->title, tmp->listen, tmp->heart);
		tmp = tmp->next;
	}
	fclose(fp);
}

music *read_file() {
	FILE *fp = NULL;
	music *new_node;
	music *list_head = NULL;

	fp = fopen("musics.dat", "r");
	while(!feof(fp)) {
		new_node = (music*) malloc (sizeof(music));
		fscanf(fp, "%s %s %s %d %d %d\n", new_node->name, new_node->singer, new_node->album, &new_node->title, &new_node->listen, &new_node->heart);
		new_node->next = list_head;
		list_head = new_node;
	}
	fclose(fp);
	return list_head;
}

void press_heart(char *name, char *singer, char *album) {
	music *tmp, *list_head;
	list_head = read_file();
	tmp = search_target(list_head, name, singer, album);

	int select;
	printf("================\n");
	if(tmp->heart == 0) {
		printf("현재 상태 : 하트를 누르지 않았습니다\n");
		printf("하트를 누르겠습니까? (Y = 1, N = 0) : ");
		scanf("%d", &select);
		if(select == 1) tmp->heart = 1;
	}
	else if(tmp->heart == 1) {
		printf("현재 상태 : 하트를 눌렀습니다\n");
		printf("하트를 취소하겠습니까? (Y = 1, N = 0) : ");
		scanf("%d", &select);
		if(select == 1) tmp->heart = 0;
	}

	save_nodes(list_head);
	release_memory(list_head);
}

void listen_count(char *name, char *singer, char *album) {
	music *tmp, *list_head;
	list_head = read_file();
	tmp = search_target(list_head, name, singer, album);
	
	int count;
	printf("================\n");
	printf("현재 들은 횟수 : %d\n", tmp->listen);
	printf("들은 횟수 추가: ");
	scanf("%d", &count); getchar();
	tmp->listen += count;

	save_nodes(list_head);
	release_memory(list_head);
}

void remove_music(char *name, char *singer, char *album) {
	int select;
	printf("정말 노래를 삭제하겠습니까? (Y = 1, N = 0) : ");
	scanf("%d", &select);
	if(select == 0) return;

	music *list_head, *tmp, *prenode, *rmnode;
	list_head = read_file();
	
	if((strcmp(list_head->name, name) == 0) && (strcmp(list_head->singer, singer) == 0) && (strcmp(list_head->album, album) == 0)) {
		rmnode = list_head;
		list_head = list_head->next;
		free(rmnode);
		save_nodes(list_head);
		release_memory(list_head);
		return;
	}

	tmp = list_head;
	prenode = tmp;
	tmp = tmp->next;
	while(tmp != NULL) {
		if((strcmp(tmp->name, name) == 0) && (strcmp(tmp->singer, singer) == 0) && (strcmp(tmp->album, album) == 0)) {
			rmnode = tmp;
			prenode->next = tmp->next;
			tmp = tmp->next;
			free(rmnode);
			break;
		}
		prenode = tmp;
		tmp = tmp->next;
	}

	save_nodes(list_head);
	release_memory(list_head);
}

void select_music(music *list_head) {
	int menu;
	music *tmp;
	tmp = list_head;

	printf("================\n");
	printf("노래 선택 : ");
	scanf("%d", &menu); getchar();

	for(int n = 0; n < menu-1; n++) tmp = tmp->next;

	printf("================\n");
	printf("선택된 노래 : %s - %s - %s\n", tmp->name, tmp->singer, tmp->album);

	char name[SIZE], singer[SIZE], album[SIZE];
	strcpy(name, tmp->name);
	strcpy(singer, tmp->singer);
	strcpy(album, tmp->album);

	release_memory(list_head);

	printf("기능 선택\n");
	printf("1. 하트 누르기/취소하기\n");
	printf("2. 들은 횟수 카운트\n");
	printf("3. 노래 삭제\n");
	printf("================\n");
	printf("선택 : ");
	scanf("%d", &menu); getchar();

	switch(menu) {
		case 1:
			press_heart(name, singer, album);
			break;
		case 2:
			listen_count(name, singer, album);
			break;
		case 3:
			remove_music(name, singer, album);
			break;
		default:
			break;
	}
}

void search_music_key(char *key, music *head, music *(*pf)(char*, music *)) {
	music *list_head;
	list_head = pf(key, head);
	select_music(list_head);
}

music *search_music_name(char *name, music *list_head) {
	music *tmp, *tmp2, *prenode, *rmnode;
	while(strcmp(list_head->name, name) != 0) {
		rmnode = list_head;
		list_head = list_head->next;
		free(rmnode);
	}
	tmp = list_head;
	tmp2 = list_head;
	prenode = tmp;
	tmp = tmp->next;
	while(tmp != NULL) {
		if(strcmp(tmp->name, name) != 0) {
			rmnode = tmp;
			prenode->next = tmp->next;
			tmp = tmp->next;
			free(rmnode);
			continue;
		}
		prenode = tmp;
		tmp = tmp->next;
	}
	printf("노래 제목으로 검색\n");
	printf("번호. 제목 - 가수 - 앨범\n");
	int i = 1;
	while(tmp2 != NULL) {
		printf("%d. %s - %s - %s", i, tmp2->name, tmp2->singer, tmp2->album);
		tmp2 = tmp2->next;
		i++;
	}
	return list_head;
}

music *search_music_singer(char *singer, music *list_head) {
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
	printf("가수 이름으로 검색\n");
	printf("번호. 제목 - 가수 - 앨범\n");
	int i = 1;
	while(tmp2 != NULL) {
		printf("%d. %s - %s - %s\n", i, tmp2->name, tmp2->singer, tmp2->album);
		tmp2 = tmp2->next;
		i++;
	}
	return list_head;
}

music *search_music_album(char *album, music *list_head) {
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
			continue;
		}
		prenode = tmp;
		tmp = tmp->next;
	}
	printf("앨범 이름으로 검색\n");
	printf("번호. 제목 - 가수 - 앨범\n");
	int i = 1;
	while(tmp2 != NULL) {
		printf("%d. %s - %s - %s\n", i, tmp2->name, tmp2->singer, tmp2->album);
		tmp2 = tmp2->next;
		i++;
	}
	return list_head;
}

music *search_music_heart(char *heart, music *list_head) {
	music *tmp, *tmp2, *prenode, *rmnode;
	while(list_head->heart != 1) {
		rmnode = list_head;
		list_head = list_head->next;
		free(rmnode);
	}
	tmp = list_head;
	tmp2 = list_head;
	prenode = tmp;
	tmp = tmp->next;
	while(tmp != NULL) {
		if(tmp->heart != 1) {
			rmnode = tmp;
			prenode->next = tmp->next;
			tmp = tmp->next;
			free(rmnode);
			continue;
		}
		prenode = tmp;
		tmp = tmp->next;
	}
	printf("하트 누른 노래 검색\n");
	printf("번호. 제목 - 가수 - 앨범\n");
	int i = 1;
	while(tmp2 != NULL) {
		printf("%d. %s - %s - %s\n", i, tmp2->name, tmp2->singer, tmp2->album);
		tmp2 = tmp2->next;
		i++;
	}
	return list_head;
}

void print_nodes(music *list_head) {
	music *tmp = list_head;
	while(tmp != NULL) {
		printf("%s %s %s %d %d %d\n", tmp->name, tmp->singer, tmp->album, tmp->title, tmp->listen, tmp->heart);
		tmp = tmp->next;
	}
}

void search_music() {
	char key[SIZE];
	FILE *fp = NULL;
	music *new_node, *tmp_node;
	music *list_head = NULL;

	fp = fopen("musics.dat", "r");
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

	int menu;
	printf("================\n");
	printf("1. 제목으로 검색\n");
	printf("2. 가수 이름으로 검색\n");
	printf("3. 앨범 이름으로 검색\n");
	printf("4. 좋아요 누른 노래\n");
	printf("================\n");
	printf("선택 : ");
	scanf("%d", &menu); getchar();

	switch(menu) {
		case 1:
			printf("제목 : ");
			scanf("%s", key); getchar();
			printf("================\n");
			search_music_key(key, list_head, search_music_name);
			break;
		case 2:
			printf("가수 : ");
			scanf("%s", key); getchar();
			printf("================\n");
			search_music_key(key, list_head, search_music_singer);
			break;
		case 3:
			printf("앨범 : ");
			scanf("%s", key); getchar();
			printf("================\n");
			search_music_key(key, list_head, search_music_album);
			break;
		case 4:
			strcpy(key, "0");
			printf("================\n");
			search_music_key(key, list_head, search_music_heart);
			break;
		default:
			printf("wrong!\n");
			break;
	}
}

void my_chart() {
	music *list_head, *tmp;
	list_head = read_file();
	int count = 0;
	int i = 100;

	while(count < 10) {
		tmp = list_head;
		while(tmp != NULL) {
			if(tmp->listen == i) {
				printf("%s %s %s %d\n", tmp->name, tmp->singer, tmp->album, tmp->listen);
				count++; break;
			}
			tmp = tmp->next;
		}
		i--;
	}
	release_memory(list_head);
}

int main() {
	int menu;
	printf("================\n");
	printf("0. 프로그램 종료\n");
	printf("1. 노래 추가\n");
	printf("2. 노래 검색\n");
	printf("3. MY 차트\n");
	printf("================\n");
	printf("선택 : ");
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
		case 3:
			my_chart();
			break;
	}
	return 0;
}
