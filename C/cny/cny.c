
/*
参考链接：https://tool.gaodun.com/rmb.html

人民币金额用到的中文大写汉字如下：

零、壹、贰、叁、肆、伍、陆、柒、捌、玖、拾、佰、仟、万、亿。

人民币常识

人民币（缩写为RMB）是我国大陆地区的法定货币，尽管每个人几乎天天都要接触到人民币或者支票，但是人民币大写如何写是困扰很多人的问题。
尽管生活中看起来极其熟悉而又简单的东西，但发现其实并不会写。
人民币在ISO 4217简称为CNY（China Yuan），常用简写为RMB（Ren Min Bi）；人民币货币的符号是“ ￥”（'Y'+'='），读音为“YUAN”。
人民币按照材料的自然属性划分，有金属币（亦称硬币）、 纸币（亦称钞票）。
无论纸币、硬币均等价流通，至今已发行了五套人民币。

人民币大写规范详细介绍

银行、单位和个人填写的各种票据和结算凭证是办理支付结算和现金收付的重要依据，直接关系到支付结算的准确、及时和安全。
票据和结算凭证是银行、单位和个人凭以记载账务的会计凭证，是记载经济业务和明确经济责任的一种书面证明。
因此，填写票据和结算凭证必须做到标准化、规范化、要素齐全、数字正确、字迹清晰、不错漏、不潦草、防止涂改。 
中文大写金额数字应用正楷或行书填写，如壹、贰、叁、肆、伍、陆、柒、捌、玖、拾、佰、仟、万、亿、元、角、分、零、整(正)等字样，
不得用一、二(两)、三、四、五、六、七、八、九、十、毛、另(或0)填写，不得自造简化字。
如果金额数字书写中使用繁体字，如贰、陆、亿、万、圆的，也应受理。

人民币大写的正确写法还应注意以下几项：

一、中文大写金额数字到“元”为止的，在“元”之后、应写“整”(或“正”)字；在“角”之后，可以不写“整”(或“正”)字；大写金额数字有“分”的，“分”后面不写“整”(或“正”)字。

二、中文大写金额数字前应标明“人民币”字样，大写金额数字应紧接“人民币”字样填写，不得留有空白。
	大写金额数字前未印“人民币”字样的，应加填“人民币”三字，在票据和结算凭证大写金额栏内不得预印固定的“仟、佰、拾、万、仟、佰、拾、元、角、分”字样。

三、阿拉伯数字小写金额数字中有“0”时，中文大写应按照汉语语言规律、金额数字构成和防止涂改的要求进行书写。举例如下： 
	1、阿拉伯数字中间有“0”时，中文大写要写“零”字，如￥1409.50应写成人民币壹仟肆佰零玖元伍角； 
	2、阿拉伯数字中间连续有几个“0”时、中文大写金额中间可以只写一个“零”字，如￥6007.14应写成人民币陆仟零柒元壹角肆分。 
	3、阿拉伯金额数字万位和元位是“0”，或者数字中间连续有几个“0”，万位、元位也是“0”但千位、角位不是“0”时，
		中文大写金额中可以只写一个零字，也可以不写“零”字，
		如￥1680.32应写成人民币壹仟陆佰捌拾元零叁角贰分，或者写成人民币壹仟陆佰捌拾元叁角贰分。
		又如￥107000.53应写成人民币壹拾万柒仟元零伍角叁分，或者写成人民币壹拾万零柒仟元伍角叁分。 
	4、阿拉伯金额数字角位是“0”而分位不是“0”时，中文大写金额“元”后面应写“零”字，
		如￥16409.02应写成人民币壹万陆仟肆佰零玖元零贰分，
		又如￥325.04应写成人民币叁佰贰拾伍元零肆分。

四、阿拉伯小写金额数字前面均应填写人民币符号“￥”，阿拉伯小写金额数字要认真填写，不得连写分辨不清。

五、票据的出票日期必须使用中文大写，为防止变造票据的出票日期，在填写月、日时、月为壹、贰和壹拾的，日为壹至玖和壹拾、贰拾和叁拾的，应在其前加“零”，
	日为拾壹至拾玖的应在其前加“壹”，如1月15日应写成零壹月壹拾伍日，再如10月20日应写成零壹拾月零贰拾日。

六、票据出票日期使用小写填写的，银行不予受理；大写日期未按要求规范填写的，银行可予受理，但由此造成损失的由出票人自行承担。
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>

static const char* digits[] = {
	"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖",
};

// 一万以下
char* cny_under_10k(uint64_t y)
{	
	static const char* units[] = {
		NULL, "拾", "佰", "仟",
	};

	char buf[1024] = { 0 };
	for (int n = 3; n > 0; n--) {
		int unit = 1;
		for (int i = 0; i < n; i++) {
			unit *= 10;
		}
		if (y / unit) {
			strcat(buf, digits[y / unit]);
			strcat(buf, units[n]);
		} else {
			strcat(buf, digits[0]);
		}
		y %= unit;
	}

	strcat(buf, digits[y]);

	// 移除末尾的零
	char* z = buf + strlen(buf) - strlen("零");
	while (memcmp(z, "零", strlen("零")) == 0) {
		*z = '\0';
		z -= strlen("零");
	}

	char* s = malloc(strlen(buf) + 1);
	if (s == NULL) return NULL;
	strcpy(s, buf);
	return s;
}

// 一亿以下
char* cny_under_1yi(uint64_t y)
{
	char buf[1024] = { 0 };
	if (y > 10000ul) {
		char* s = cny_under_10k(y / 10000ul);
		strcat(buf, s);
		free(s);
		strcat(buf, "万");
		y %= 10000ul;
	}

	char* s = cny_under_10k(y);
	if (strlen(buf)) {
		strcat(buf, s);
		free(s);
		s = malloc(strlen(buf) + 1);
		if (s == NULL) return NULL;
		strcpy(s, buf);
	}
	return s;
}

char* cny_f(uint32_t y, int keep_0_jiao)
{
	char buf[1024] = { 0 };
	if (y / 10) {
		strcat(buf, digits[y / 10]);
		strcat(buf, "角");
		y %= 10;
	} else if (keep_0_jiao) {
		strcat(buf, "零");
	}
	if (y) {
		strcat(buf, digits[y]);
		strcat(buf, "分");
	}
	char* s = malloc(strlen(buf) + 1);
	if (s == NULL) return NULL;
	strcpy(s, buf);
	return s;
}

// 人民币大写转换
// y 元
// f 分
// max 1844 67440737 09551615
// caller free
char* cny(uint64_t y, uint32_t f)
{
	if (f >= 100) {
		return NULL;
	}
	char buf[4096] = { 0 };

	if (y == 0 && f == 0) {
		strcpy(buf, "零元整");
		goto end;
	} else if (y == 0) {
		goto begin_f;
	}

	if (y > 10000000000000000ul) { // 1亿亿
		char* yys = cny_under_1yi(y / 10000000000000000ul);
		strcpy(buf, yys);
		free(yys);
		strcat(buf, "亿亿");
		y %= 10000000000000000ul;
	}

	if (y > 100000000ul) { // 多少亿
		char* ys = cny_under_1yi(y / 100000000ul);
		strncat(buf, ys, strlen(ys));
		free(ys);
		strcat(buf, "亿");
		y %= 100000000ul;
	}

	char* s = cny_under_1yi(y);
	strcat(buf, s);
	free(s);
	strcat(buf, "元");

	if (f == 0) {
		strcat(buf, "整");
	} else {
begin_f:
		s = cny_f(f, strlen(buf));
		strcat(buf, s);
		free(s);
		if (y == 0) {
			goto end;
		}
	}

	// 移除开头的零
	char* next = buf;
	while (memcmp(next, "零", strlen("零")) == 0) {
		next += strlen("零");
	}
	if (next != buf) {
		memmove(buf, next, strlen(next) + 1);
	}

	// 移除重复的零
	char* z = strstr(buf, "零");
	while (z) {
		char* next = z + strlen("零");
		char* pos = next;
		while (memcmp(next, "零", strlen("零")) == 0) {
			next += strlen("零");
		}
		if (next != pos) {
			memmove(pos, next, strlen(next) + 1);
		}
		z = strstr(next, "零");
	}

	// 移除拾后的零
	char* shi = strstr(buf, "拾");
	while (shi) {
		char* next = shi + strlen("零");
		char* pos = next;
		if (memcmp(next, "零", strlen("零")) == 0) {
			next += strlen("零");
			memmove(pos, next, strlen(next) + 1);
		}
		shi = strstr(next, "拾");
	}

end:
	s = malloc(strlen(buf) + 1);
	if (s == NULL) return NULL;
	strcpy(s, buf);
	return s;
}

void usage(char* exe)
{
	fprintf(stderr, "usage: %s cny\ncny must in [0.00, %" PRIu64 ".99]\n", exe, UINT64_MAX);
	exit(1);
}

int read_cny(char* s, uint64_t* py, uint32_t* pf)
{
	uint64_t y = 0;
	uint32_t f = 0;
	int dots = 0;

	while (*s) {
		if (!isdigit(*s) && *s != '.') {
			return 0;
		}
		if (*s == '.') {
			if (dots == 0) {
				dots = 1;
				s++;
				continue;
			} else {
				return 0;
			}
		}
		if (dots == 0) { // y
			if (y > UINT64_MAX / 10) {
				return 0;
			}
			y *= 10;
			if (y > UINT64_MAX - (*s - '0')) {
				return 0;
			}
			y += *s - '0';
		} else { // f
			if (f > 9) {
				return 0;
			}
			f *= 10;
			if (f > 99u - (*s - '0')) {
				return 0;
			}
			f += *s - '0';
		}
		s++;
	}

	*py = y;
	*pf = f;
	return 1;
}

int read_cny_from_stdin(uint64_t* py, uint32_t* pf)
{
	char c;
	uint64_t y = 0;
	uint32_t f = 0;
	int dots = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\r' || c == '\n') break;
		if (!isdigit(c) && c != '.') {
			return 0;
		}
		if (c == '.') {
			if (dots == 0) {
				dots = 1;
				continue;
			} else {
				return 0;
			}
		}
		if (dots == 0) { // y
			if (y > UINT64_MAX / 10) {
				return 0;
			}
			y *= 10;
			if (y > UINT64_MAX - (c - '0')) {
				return 0;
			}
			y += c - '0';
		} else { // f
			if (f > 9) {
				return 0;
			}
			f *= 10;
			if (f > 99u - (c - '0')) {
				return 0;
			}
			f += c - '0';
		}
	}

	*py = y;
	*pf = f;
	return 1;
}

void test(uint64_t y, int32_t f, const char* str)
{
	printf("testing %" PRIu64 ".%02" PRId32 "...", y, f);
	char* s = cny(y, f);
	if (strcmp(s, str) == 0) { printf("OK\n"); }
	else { printf("\nERROR, should be %s\n", str); }
	free(s);
}

void do_test()
{
	/*assert(strcmp(cny(0, 0), "零元整") == 0); 
	assert(strcmp(cny(0, 3), "叁分") == 0);
	assert(strcmp(cny(0, 53), "伍角叁分") == 0);
	assert(strcmp(cny(1409, 50), "壹仟肆佰零玖元伍角") == 0);
	assert(strcmp(cny(6007, 14), "陆仟零柒元壹角肆分") == 0);
	assert(strcmp(cny(1680, 32), "壹仟陆佰捌拾元叁角贰分") == 0);
	assert(strcmp(cny(107000, 53), "壹拾万柒仟元伍角叁分") == 0);
	assert(strcmp(cny(16409, 2), "壹万陆仟肆佰零玖元零贰分") == 0);
	assert(strcmp(cny(325, 4), "叁佰贰拾伍元零肆分") == 0);
	assert(strcmp(cny(3210, 0), "叁仟贰佰壹拾元整") == 0);
	assert(strcmp(cny(3010, 0), "叁仟零壹拾元整") == 0);
	assert(strcmp(cny(10000001, 89), "壹仟万零壹元捌角玖分") == 0);
	assert(strcmp(cny(1234567890, 89), "壹拾贰亿叁仟肆佰伍拾陆万柒仟捌佰玖拾元捌角玖分") == 0);
	assert(strcmp(cny(3709551615, 0), "叁拾柒亿零玖佰伍拾伍万壹仟陆佰壹拾伍元整") == 0);*/

	test(0, 0, "零元整");
	test(0, 3, "叁分");
	test(0, 53, "伍角叁分");
	test(1409, 50, "壹仟肆佰零玖元伍角");
	test(6007, 14, "陆仟零柒元壹角肆分");
	test(1680, 32, "壹仟陆佰捌拾元叁角贰分");
	test(107000, 53, "壹拾万柒仟元伍角叁分");
	test(16409, 2, "壹万陆仟肆佰零玖元零贰分");
	test(325, 4, "叁佰贰拾伍元零肆分");
	test(3210, 0, "叁仟贰佰壹拾元整");
	test(3010, 0, "叁仟零壹拾元整");
	test(10000001, 89, "壹仟万零壹元捌角玖分");
	test(1234567890, 89, "壹拾贰亿叁仟肆佰伍拾陆万柒仟捌佰玖拾元捌角玖分");
	test(3709551615, 0, "叁拾柒亿零玖佰伍拾伍万壹仟陆佰壹拾伍元整");
}

int main(int argc, char** argv)
{
	/*printf("%s\n", cny(UINT64_MAX, 0));
	printf("%s\n", cny(1234567890, 5));
	printf("%s\n", cny(0, 0));
	printf("%s\n", cny(0, 5));*/

	//do_test();

	uint64_t y = 0;
	uint32_t f = 0;

	if (argc == 1) {
		if (!read_cny_from_stdin(&y, &f)) {
			usage(argv[0]);
			return 0;
		}
	} else if (argc == 2) {
		if (!read_cny(argv[1], &y, &f)) {
			usage(argv[0]);
			return 0;
		}
	} else {
		usage(argv[0]);
		return 0;
	}

	printf("%s\n", cny(y, f));

	return 0;	
}