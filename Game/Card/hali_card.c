#include "hali_card.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "windows.h"

/**
 * 目前版本不考虑 联机 ，仅设置本地 选择是否地主身份
 */

enum Direction_index {
	GET_LEFT,
	GET_RIGHT,
};

enum CARDS_Color { // 花色
	COLOR_RED_HEART, // 红心
	COLOR_PLUM_FLOWER, // 梅花
	COLOR_BLOCK,	// 方块
	COLOR_SPADES,   // 黑桃
};

enum CARDS_Value {
	VALUE_TWO = 0,
	VALUE_THREE = 1,
	VALUE_FOUR = 2,
	VALUE_FIVE = 3,
	VALUE_SIX = 4,
	VALUE_SENVEN = 5,
	VALUE_EIGHT = 6,
	VALUE_NINE = 7,
	VALUE_TEN = 8,
	VALUE_J = 9,
	VALUE_Q = 10,
	VALUE_K = 11,
	VALUE_A = 12,
	VALUE_RED_JOKER = 13, // 小王
	VALUE_BLACK_JOKER = 14, // 大王
};

enum USED_TYPE {
	ALREADY_ASSIGNED = 1,
	ALREADY_USED = 2,
};

struct info_before_game {
	int people_nums;
	int decks_of_cards;
};

struct info_card_face {
	enum CARDS_Color color;
	enum CARDS_Value value;

	int used; // 是否已经是使用过的牌  1:已分配  2：已出
	int master_index; // 这张牌属于谁 （也就是发牌的时候这张牌发给了谁）
	int flags; // 标记这张牌是 分给 地主的额外牌
};

enum info_identity {
	PALY_LANDLORDS, // 地主
	PLAY_PEASANTS, // 农民
};

/**
 * 牌的index是按照从 2->3->10->J->Q->K->A->小王->大王
 * 花色是 红心、梅花、方块、黑桃
 */

struct info_player {
	int *all_cards_index; // 分发到手上的所有牌

	enum info_identity identity;
};

typedef struct hali_card {
	int cards_nums;

	struct info_before_game info_b;
	struct info_card_face *c_face;

	struct info_player *player;
}__attribute__((__packed__)) hali_card_t;
hali_card_t *g_card = NULL;


#define ONE_DECKS_OF_CARDS_NUMS	54
#define NO_CARDS_COLOR			-1
#define FLAGS_NUM 				3 // 留置牌数
#define DEFAULT_BREAK_POINT		8 // 这个值越复杂，牌就越是难知道是如何分配的

char str_color[10] = {0};
int flags_array[FLAGS_NUM] = {0};
int break_point_array[DEFAULT_BREAK_POINT] = {0};
int bubble_sort_array[DEFAULT_BREAK_POINT] = {0};

static void welcome_display(void)
{
	system("cls");
	printf("******\r\n");
	printf("欢迎进入 斗地主卡牌游戏\r\n");
	printf("******\r\n\r\n");
	printf("输入任意确认继续...\r\n");
	getchar();
}

static void prompt_display(void)
{
	system("cls");
	printf("******\r\n");
	printf("进入游戏前，请告诉我两点信息:\r\n");
	printf("1.游戏总人数(包含您)?\t\t2.一共需要几副牌?\r\n");
	printf("******\r\n\r\n");
	printf("输入任意确认继续...\r\n");
	getchar();
}

static void interaction_info_before_game(void)
{
	system("cls");
	printf("******\r\n");

	printf("请问游戏总人数一共有多少(包含您)?\r\n");
	printf("请输入:");
	fflush(stdin);
	scanf("%d", &(g_card->info_b.people_nums));
	getchar();
	printf("已确认设置游戏总人数为:%d\r\n", g_card->info_b.people_nums);
	
	printf("请问游戏一共使用几副牌?\r\n");
	printf("请输入:");
	fflush(stdin);
	scanf("%d", &(g_card->info_b.decks_of_cards));
	getchar();
	if (g_card->info_b.decks_of_cards <= 0) {
		printf("用户选择了 %d 副牌，非法，游戏结束");
		exit(-2);
	}
	printf("已确认设置游戏使用 %d 副牌\r\n", g_card->info_b.decks_of_cards);

	printf("******\r\n\r\n");
	printf("输入任意确认继续...\r\n");
	getchar();
}

static void hali_printf(int num, char str_print[])
{
	int i = 0;
	system("cls");
	for (i = 0; i < num; i++) {
		printf("%s", str_print);
	}
	Sleep(60);
}

static void game_start_anmi(void)
{
	system("cls");
	int i = 0;
	for (int i = 0; i < 10; i++) {
		hali_printf(i, "*");
	}
	hali_printf(1, "游");
	hali_printf(1, "游戏");
	hali_printf(1, "游戏开");
	hali_printf(1, "游戏开始\r\n");

	printf("输入任意确认继续...\r\n");
	getchar();
}

static int get_value_byindex(int i) // enum CARDS_Value
{	
	i = i % ONE_DECKS_OF_CARDS_NUMS;
	if (i >= 0 && i < 4) {
		return VALUE_TWO;
	} else if (i >= 4 && i < 8) {
		return VALUE_THREE;
	} else if (i >= 8 && i < 12) {
		return VALUE_FOUR;
	} else if (i >= 12 && i < 16) {
		return VALUE_FIVE;
	} else if (i >= 16 && i < 20) {
		return VALUE_SIX;
	} else if (i >= 20 && i < 24) {
		return VALUE_SENVEN;
	} else if (i >= 24 && i < 28) {
		return VALUE_EIGHT;
	} else if (i >= 28 && i < 32) {
		return VALUE_NINE;
	} else if (i >= 32 && i < 36) {
		return VALUE_TEN;
	} else if (i >= 36 && i < 40) {
		return VALUE_J;
	} else if (i >= 40 && i < 44) {
		return VALUE_Q;
	} else if (i >= 44 && i < 48) {
		return VALUE_K;
	} else if (i >= 48 && i < 52) {
		return VALUE_A;
	} else if (i == 52) {
		return VALUE_RED_JOKER;
	} else if (i == 53) {
		return VALUE_BLACK_JOKER;
	}
}

static int get_color_byindex(int i) // enum CARDS_Color
{
	i = i % ONE_DECKS_OF_CARDS_NUMS;

	if (i == 52 || i == 53) {
		return NO_CARDS_COLOR;  // 大王小王没有花色
	}
	static int j = 0;

	if (j == 0) {
		j = (++j) % 4;
		return COLOR_RED_HEART;
	} else if (j == 1) {
		j = (++j) % 4;
		return COLOR_PLUM_FLOWER;
	} else if (j == 2) {
		j = (++j) % 4;
		return COLOR_BLOCK;
	} else if (j == 3) {
		j = (++j) % 4;
		return COLOR_SPADES;
	}
}

static void cards_face_ensure(void)
{
	int i = 0;

	printf("洗牌中\r\n");
	// init every cards
	for (i = 0; i < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS; i++) {
		g_card->c_face[i].value = get_value_byindex(i);
		g_card->c_face[i].color = get_color_byindex(i);
		// printf("value is %d,color is %d\r\n", g_card->c_face[i].value, g_card->c_face[i].color);
	}
	printf("已经洗好牌了\r\n");
	printf("按任意键继续...\r\n");
	getchar();

}

static void cards_shuffle(void)
{
	g_card->cards_nums = g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS;
	g_card->c_face = malloc(sizeof(struct info_card_face) * g_card->cards_nums);
	if (g_card->c_face == NULL) {
		printf("malloc failed, please check room\r\n");
		exit(-1);
	}

	// 给每一张牌定face 
	cards_face_ensure();
}


static void g_structure_init(void)
{
	g_card = malloc(sizeof(hali_card_t));
	if (!g_card) {
		printf("can not malloc room,please check\r\n");
		exit(-1);
	}
	memset(g_card, 0, sizeof(hali_card_t));
}

static void three_seconds_countdown(void)
{
	printf("3 秒\r");
	Sleep(1200);
	printf("2 秒\r");
	Sleep(1200);
	printf("1 秒\r");
	Sleep(1200);
	system("cls");
}

static void player_init(void)
{
	if (g_card->player) {
		free(g_card->player);
	}
	g_card->player = malloc(sizeof(struct info_player) * g_card->info_b.people_nums);

	if (g_card->player == NULL) {
		printf("malloc failed,please check.\r\n");
		exit(-2);
	}
}

static int landlords_choose(void) // 决定地主身份
{
	system("cls");
	printf("******\r\n");
	printf("开始抢地主...、\r\n");
	int i = 0, yes_ = 0;
	char answer_str[10];
	int dice[10] = {0}, max_dice = 0, max_index = 0;
	int nums_want_landlords_bot = 0;

	player_init();

	if (0) {
game_again:	
		printf("游戏继续\r\n");
	}
	nums_want_landlords_bot = rand() % g_card->info_b.people_nums;
	if (nums_want_landlords_bot > 0) {
		printf("已有 %d 人需要抢地主\r\n", nums_want_landlords_bot);
	} else {
		printf("其余人不抢地主\r\n");
	}
	printf("请问您需要抢地主吗？\r\n");

	three_seconds_countdown();
	printf("yes(是) or no(不是)？\r\n");
	printf("您的回答是:");

	fflush(stdin);
	scanf("%s", answer_str);
	getchar();

	if (strcasecmp("yes", answer_str) == 0 || strcasecmp("是", answer_str) == 0) {
		yes_ = 1;
		nums_want_landlords_bot++;
	}

	if (nums_want_landlords_bot == 0) {
		printf("本局游戏没有人想抢地主，重新开始\r\n");
		goto game_again;
	}

	if (nums_want_landlords_bot == 1) {
		printf("本局游戏只有一人抢地主\r\n");
		if (yes_ == 1) {
			printf("只有您抢地主，系统判定您已为地主了\r\n");
			g_card->player[g_card->info_b.people_nums - 1].identity = PALY_LANDLORDS;
		} else { // 说明唯一的一个这个抢地主的是别人
			int temp = rand() % g_card->info_b.people_nums;
			if (temp != 0) {
				printf("只有玩家%d号抢地主，他已经是地主了\r\n", temp);
				g_card->player[temp].identity = PALY_LANDLORDS;
			} else {
				printf("只有玩家%d号抢地主，他已经是地主了\r\n", temp + 1);
				g_card->player[temp + 1].identity = PALY_LANDLORDS;
			}
		}
	} else {
		printf("系统开始投掷骰子决定谁为地主(1.谁的点数大 2.后掷大于前掷)\r\n");
		for (i = 0; i < nums_want_landlords_bot; i++) {
			if (i != (nums_want_landlords_bot - 1)) { // 人机先抛掷骰子
				dice[i] = 1 + rand() % 6;
				printf("玩家%d号掷出了%d\r\n", i + 1, dice[i]);
			} else if (yes_ == 1) {
				printf("请您掷出点数，按任意键开始\r\n");
				getchar();
				printf("%d\r", 1 + rand() % 6);
				Sleep(400);
				printf("%d\r", 1 + rand() % 6);
				Sleep(400);
				printf("%d\r", 1 + rand() % 6);
				Sleep(400);
				printf("%d\r", 1 + rand() % 6);
				Sleep(400);
				printf("%d\r", 1 + rand() % 6);
				Sleep(500);
				printf("%d\r", 1 + rand() % 6);
				Sleep(600);
				printf("%d\r", 1 + rand() % 6);
				Sleep(700);
				printf("%d\r", 1 + rand() % 6);
				Sleep(750);
				int temp = 1 + rand() % 6;
				printf("%d\r", temp);
				dice[i] = temp;
				printf("\r\n");
				printf("您掷出了%d\r\n", dice[i]);
			}
			if (dice[i] >= max_dice) {
				max_dice = dice[i];
				max_index = i;
			}
		}

		// 先将真人玩家身份确认
		if (max_index == (nums_want_landlords_bot - 1)) {
			printf("您赢了，系统决定您为地主\r\n");
			g_card->player[g_card->info_b.people_nums - 1].identity = PALY_LANDLORDS;
		} else {
			printf("您输了，系统决定第%d位玩家为地主，您的身份为农民\r\n", max_index + 1);
			g_card->player[max_index].identity = PALY_LANDLORDS;
		}
	}

	for (i = 0; i < g_card->info_b.people_nums; i++) {
		if (g_card->player[i].identity != PALY_LANDLORDS) {
			g_card->player[i].identity = PLAY_PEASANTS;
		}
	}

	printf("按任意键继续\r\n");
	fflush(stdin);
	getchar();
	// 身份确认已完成
}

static int break_point_add_to_array(int value_index) // 1：有  0：没有
{
	static int nums = 0;
	int i = 0;
	if (nums < DEFAULT_BREAK_POINT) { // 说明还需要放入
		for (i = 0; i < DEFAULT_BREAK_POINT; i++) {
			if (break_point_array[i] == value_index) { // 已经放入过这个下标 （NOTE 默认下标0都是不行的）
				return 1; 
			}
		}

		for (i = 0; i < DEFAULT_BREAK_POINT; i++) { // 将内容放入数组
			if (break_point_array[i] == 0) {
				break_point_array[i] = value_index;
				nums++;
				return 0;
			}
		}
	}
}

static int flags_add_to_array(int value_index) // 1：有  0：没有
{
	static int nums = 0;
	int i = 0;
	if (nums < FLAGS_NUM) { // 放入逻辑
		for (i = 0; i < FLAGS_NUM; i++) {
			if (flags_array[i] == value_index) { // 已经放入过这个下标 （NOTE 默认下标0都是不行的）
				return 1; 
			}
		}

		// 能到这里说明 这个index还没有在这个里面
		for (i = 0; i < FLAGS_NUM; i++) { // 将内容放入数组
			if (flags_array[i] == 0) {
				flags_array[i] = value_index;
				nums++;
				return 0;
			}
		}
	} else { // 判断是否已存在逻辑
		for (i = 0; i < FLAGS_NUM; i++) {
			if (flags_array[i] == value_index) { // 已经放入过这个下标 （NOTE 默认下标0都是不行的）
				return 1; 
			}
		}
		return 0;
	}
}

static int player_rand(void) // 顺序返回 下标  （随机位置开始 然后一轮询）
{
	static int return_index = 0, return_index_first = 0;
	static int already_access_times = 0;

	already_access_times++;
	if (already_access_times == g_card->info_b.people_nums) {
		// printf("准备下一轮回\r\n");
		already_access_times = 0; // 进来一轮了回复一下
	}

	if (already_access_times == 1) { // 第一次 先定初始值
		return_index = rand() % g_card->info_b.people_nums; // 定一个开始位置 下标
		return_index_first = return_index;
	} else {
		if (++return_index < g_card->info_b.people_nums) { // 先往右

		} else if (--return_index_first >= 0) { // 再往左
			return return_index_first;
		}
	}

	// printf("return_index is %d\r\n", return_index);
	return return_index;
}

void bubble_sort_func(int array[], int size)
{
	int i = 0, j = 0;
	int temp = 0;

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1; j++) {
			if (array[j] > array[j+1]) {
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

static void get_sort_init(void)
{
	memcpy(bubble_sort_array, break_point_array, DEFAULT_BREAK_POINT*sizeof(int));
	bubble_sort_func(bubble_sort_array, DEFAULT_BREAK_POINT);
}

static int get_sort_index_value(int value, enum Direction_index dir)
{
	// printf("value is %d\r\n", value);
	int i = 0;
	int find_index = 0;

	// 找到这个值对应的下标
	for (i = 0; i < DEFAULT_BREAK_POINT; i++) {
		// printf("bubble_sort_array[%d] is %d\r\n", i, bubble_sort_array[i]);
		if (bubble_sort_array[i] == value) { // 找到了
			find_index = i;
			break;
		}
	}
	if (i == DEFAULT_BREAK_POINT) { // 说明根本没有找到
		printf("find something error\r\n");
		exit(-2);
	}

	if (dir == GET_LEFT) { // 是需要获取左边的index
		if (value == bubble_sort_array[0]) {
			return 0;
		} else {
			find_index--;
		}
	} else if (dir == GET_RIGHT) { // 是需要获取右边的index
		if (value == bubble_sort_array[DEFAULT_BREAK_POINT-1]) {
			return g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS - 1;
		} else {
			find_index++;
		}
	} else {
		printf("something error \r\n");
		exit(-2);
	}

	if (find_index < 0) {
		find_index = 0;
	} else if (find_index == DEFAULT_BREAK_POINT) {
		find_index = DEFAULT_BREAK_POINT - 1;
	}

	return bubble_sort_array[find_index];
}

static int get_landlords_index(void)
{
	int i = 0;
	for (i = 0; i < g_card->info_b.people_nums; i++) {
		// printf("第%d位玩家身份是:%d\r\n", i+1, g_card->player[i].identity);
		if (g_card->player[i].identity == PALY_LANDLORDS) {
			return i;
		}
	}

	if (i == g_card->info_b.people_nums) {
		printf("something error\r\n");
		exit(-2);
	}
}

static char* color_chinese_print(enum CARDS_Color color)
{
	if (color == COLOR_RED_HEART) { // 红心
		return "红心";
	} else if (color == COLOR_PLUM_FLOWER) { // 梅花
		return "梅花";
	} else if (color == COLOR_BLOCK) {  // 方块
		return "方块";
	} else if (color == COLOR_SPADES) {  // 黑桃
 		return "黑桃";
	} else {
		// printf("大王或小王牌\r\n");
		return "王牌";
	}
}

static char* value_chinese_print(enum CARDS_Value value)
{
	memset(str_color, 0, sizeof(str_color));
	if (value >= 0 && value <= 8) {
		value += 2;
		snprintf(str_color, sizeof(str_color), "%d", value);
		return str_color;
	} else if (value == VALUE_J) {
		return "J";
	} else if (value == VALUE_Q) {
		return "Q";
	} else if (value == VALUE_K) {
		return "K";
	} else if (value == VALUE_A) {
		return "A";
	} else if (value == VALUE_RED_JOKER) {
		return "小王";
	} else if (value == VALUE_BLACK_JOKER) {
		return "大王";
	} else {
		printf("something error\r\n");
		exit(-3);
	}
}

static void get_card_info_by_index(int index) // 打印牌的 info
{
	printf("花色:%s, 数值:%s\r\n", color_chinese_print(g_card->c_face[index].color),value_chinese_print(g_card->c_face[index].value));
}

static void dealing_cards(void) // 开始发牌
{
	// TODO 开始为每一位玩家发牌
	int i = 0, flags_num = FLAGS_NUM;
	int flags_temp_index = 0;
	int break_point = DEFAULT_BREAK_POINT;
	int break_temp = 0;

	printf("开始发牌，请稍等\r\n");
	memset(flags_array, 0, FLAGS_NUM);
	for (i = 0; i < flags_num;) { // NOTE 找到 FLAGS_NUM 牌定为 地主额外牌
		flags_temp_index = rand() % (g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS);
		// printf("得到随机数:%d\r\n", flags_temp_index);
		if (!flags_add_to_array(flags_temp_index)) {
			g_card->c_face[flags_temp_index].flags = 1;
			// printf("%d号牌定为额外地主牌\r\n", flags_temp_index);
			i++;
		}
	}

	/**
	 * 发牌思维
	 * 先 随机出几个 中断顺序点
	 * 然后从中断顺序点
	 */
	// 先将牌的中断点确认清除
	memset(break_point_array, 0, DEFAULT_BREAK_POINT);
	for (i = 0; i < break_point; ) {
		break_temp = rand() % (g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS);
		if (!break_point_add_to_array(break_temp)) {
			// printf("设置中断点下标:%d\r\n", break_temp);
			i++;
		}
	}

	get_sort_init();

	int jj = 0;
	// 开始发牌
	for (i = 0; i < break_point; ) {
		int break_temp_index = rand() % break_point;
		if (break_point_array[break_temp_index] != -1) { // 说明这个中断点还没有使用过
			if (break_point_array[break_temp_index] > 0) { // 有左边(左包含)
				for (jj = break_point_array[break_temp_index]; jj >= get_sort_index_value(break_point_array[break_temp_index], GET_LEFT); jj--) { // 左边牌逐个标记
					if (!flags_add_to_array(jj)) { // 该张牌不是地主牌
						if (g_card->c_face[jj].used != ALREADY_ASSIGNED) {
							g_card->c_face[jj].master_index = player_rand();
							g_card->c_face[jj].used = ALREADY_ASSIGNED;
							// printf("%d号牌分发给了第%d号玩家\r\n", jj, g_card->c_face[jj].master_index + 1);
						}
					}
				}
			}
			if (break_point_array[break_temp_index] < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS) { // 有右边
				for (jj = get_sort_index_value(break_point_array[break_temp_index], GET_RIGHT); jj >= break_point_array[break_temp_index]; jj--) { // 左边牌逐个标记 NOTE 这里可以优化
					if (!flags_add_to_array(jj)) { // 该张牌不是地主牌
						if (g_card->c_face[jj].used != ALREADY_ASSIGNED) { 
							g_card->c_face[jj].master_index = player_rand();
							g_card->c_face[jj].used = ALREADY_ASSIGNED;
							// printf("%d号牌分发给了第%d号玩家\r\n", jj, g_card->c_face[jj].master_index + 1);
						}	
					}
				}
			}
			i++;
			break_point_array[break_temp_index] = -1; // 先标记 不再为中断点 下面执行操作 // 先左后右
		}
	}
	printf("牌已经分发完毕\r\n");

	// 普通牌已经分发完毕，补全地主该多拥有的 FLAGS_NUM 张牌
	int except_cards[FLAGS_NUM + 1] = {0};
	i = 0;
	for (jj = 0; jj < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS; jj++) {
		if (flags_add_to_array(jj)) {
			printf("第%d张地主额外牌下标为%d\r\n", i+1, jj);
			except_cards[i++] = jj;
			g_card->c_face[jj].master_index = get_landlords_index();
			g_card->c_face[jj].used = ALREADY_ASSIGNED;
			if (i == FLAGS_NUM) {
				break;
			}
		}
	}

	printf("\r\n***_____***\r\n");
	printf("地主额外牌为:\r\n");
	for (jj = 0; jj < FLAGS_NUM;) {
		get_card_info_by_index(except_cards[jj++]);
	}
	printf("***_____***\r\n");

	printf("按任意键继续\r\n");
	getchar();
}

static void rand_init(void)
{
	srand((unsigned)time(NULL)); // 设定当前时间为随机种子
}

static void player_cards_display(void)
{
	int i= 0, j = 0;

	for (i = 0; i < g_card->info_b.people_nums; i++) {
		printf("*********************\r\n");
		printf("第%d位玩家的手牌如下:\r\n", i+1);
		for (j = 0; j < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS; j++) {
			if (g_card->c_face[j].master_index == i && g_card->c_face[j].used == ALREADY_ASSIGNED) {
				get_card_info_by_index(j);
			}
		}
		printf("*********************\r\n");
	}
}

static void player_cards_display_by_index(int index)
{
	int j = 0;

	printf("*********************\r\n");
	for (j = 0; j < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS; j++) {
		if (g_card->c_face[j].master_index == index && g_card->c_face[j].used == ALREADY_ASSIGNED) {
			get_card_info_by_index(j);
		}
	}
	printf("*********************\r\n");
}

static void admin_look(void) // 游戏开始
{
	char answer_str[10] = {0};
	printf("请问您是管理员吗？\r\n");
	printf("yes(是) or no(不是)?\r\n");
	printf("请输入:");

	fflush(stdin);
	scanf("%s", answer_str);
	if (strcasecmp(answer_str,"yes") == 0 || strcasecmp(answer_str,"是") == 0) {
		getchar();
		memset(answer_str, 0, sizeof(answer_str));
		printf("请输入管理员密码:");
		scanf("%s", answer_str);
		getchar();
		if (strcasecmp(answer_str, ADMIN_PASSWORD) == 0) {
			player_cards_display();
		} else {
			printf("password is error,system ensure you are not admin\r\n");
		}
	} else { // 认为自己不是管理员
		printf("好的，游戏继续");
	}

	printf("按任意键继续\r\n");
	getchar();
}

static int get_rotation_index(void)
{
	static int flag = 0;
	static int last_index = 0;
	if (flag == 0) { // 第一次进入 那就是默认 地主先出牌的 函数直接返回地主
		flag = 1;
		last_index = get_landlords_index();
	} else { /// 开始轮询
		if (++last_index < g_card->info_b.people_nums) {

		} else {
			last_index = 0;
		}
	}

	return last_index;
}

static char* get_identity_by_index(int index)
{
	int identity = g_card->player[index].identity;

	if (identity == PALY_LANDLORDS) {
		return "地主";
	} else if (identity == PLAY_PEASANTS) {
		return "农民";
	} else {
		printf("something error\r\n");
		exit(-3);
	}
}

static int check_game_over_by_index(int index)
{
	int j = 0;
	int leave_cards_num = 0; // 手上剩余牌数

	for (j = 0; j < g_card->info_b.decks_of_cards * ONE_DECKS_OF_CARDS_NUMS; j++) {
		if (g_card->c_face[j].master_index == index && g_card->c_face[j].used == ALREADY_ASSIGNED) { // 是他的牌 且 还没有使用掉
			leave_cards_num++;
		}
	}

	return leave_cards_num;
}

/**
 * 界面给出较为详细的下标类似内容 (用户只需要给出下标组合就行)
 * 游戏玩法总结
 * 地主先出牌
 * 组合牌: 王炸 > 四同牌炸 > 其余()
 * 单牌: 2 > A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 
 */

// struct cards_turn_info {
// 	int last_turn_cards_index_array[ONCE_PLAY_CARDS_MAX_NUM]; // 上一回合对方出的牌的信息 (index)
// 	int oneself_prepare_paly_cards_index_array[ONCE_PLAY_CARDS_MAX_NUM]; // 自己回合自己打算出的牌的信息
// };

static void game_begin(void)
{
	int game_over = 0;
	int rotation_index = 0; /* 当前轮到谁 出牌 */

	// struct cards_turn_info trun_info;

	system("cls");
	printf("************************************************\r\n");
	printf("游戏开始,地主先出牌\r\n");
	do {
		rotation_index = get_rotation_index();

		printf("*********************\r\n");
		printf("上一次出牌信息:暂无\r\n"); // TODO
		printf("您是玩家 %d 号, 您的身份:%s\r\n", rotation_index + 1, get_identity_by_index(rotation_index));
		printf("您的手牌剩余如下:\r\n");
		player_cards_display_by_index(rotation_index);

		// TODO 出牌

		if (check_game_over_by_index(rotation_index) == 0) {
			game_over = 1;
		}

		printf("按任意键继续\r\n");
		getchar();
		system("cls");
	}while(!game_over);
}

int main(void)
{
	system("chcp 65001");
	rand_init();
	g_structure_init();

	// printf("当前 time(NULL) 返回值：%ld\n", time(NULL));
	// printf("当前 time(NULL) 返回值：%ld\n", time(NULL));
	// Sleep(1000);
	// printf("当前 time(NULL) 返回值：%ld\n", time(NULL));
	// getchar();

	do {
		welcome_display();
		prompt_display();
		interaction_info_before_game();

		game_start_anmi();

		cards_shuffle();
		
		landlords_choose();
		dealing_cards();

		admin_look();
		game_begin();

	} while(1);

	return 0;
}