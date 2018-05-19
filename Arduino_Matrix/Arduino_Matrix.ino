/****************arduino板载点阵板******************
 * by 未见
 * 2018/05/19
 * 测试 Ver 0.1.1
 * 
 * -------------------PIN Map---------------------
 * COL            	C1   C2  C3  C4  C5	C6	C7	C8
 * HARDWARE_PIN		13	3	4	10	6	11	15	16
 * ARDUINO_PIN		6	12	13	3	15	4	8	9
 * 
 * ROW				R1	R2	R3	R4	R5	R6	R7	R8
 * HARDWARE_PIN		9	14	8	12	1	7	2	5
 * ARDUINO_PIN		2	7	17	5	10	16	11	14
 * -----------------------------------------------
 * 
 * ***********************************************/

uint8_t COL[] = {6, 12, 13, 3, 15, 4, 8, 9};
uint8_t ROW[] = {2, 7, 17, 5, 10, 16, 11, 14};
uint8_t MAP0[][8] = {	
						0,0,0,0,0,0,0,0,
						0,1,1,0,0,1,1,0,
						0,1,1,0,0,1,1,0,
						0,0,0,0,0,0,0,0,
						0,1,0,0,0,0,1,0,
						0,1,0,0,0,0,1,0,
						0,0,1,1,1,1,0,0,
						0,0,0,1,1,0,0,0,};

uint8_t MAP1[][8] = {	
						0,0,0,0,0,0,0,0,
						0,1,1,0,0,1,1,0,
						0,1,1,0,0,1,1,0,
						0,0,0,0,0,0,0,0,
						1,0,0,0,0,0,0,1,
						0,1,1,1,1,1,1,0,
						0,0,1,0,0,1,0,0,
						0,0,0,1,1,0,0,0,};

uint8_t MAP2[] = {0x00,0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,};

uint8_t MAP3[] = {0xE7,0xC3,0xA5,0x18,0x18,0xA5,0xC3,0xE7,};


void setup(void)
{
	for (uint8_t i = 0; i <= 17; i++)
	{
		pinMode(i, OUTPUT);
	}
}



/******************
 * 清理屏幕残影
 *****************/
void Clear_Screen(void)
{
	for (uint8_t k = 0; k <= 7; k++)
	{

		digitalWrite(ROW[k], HIGH);
		digitalWrite(COL[k], LOW);
	}
}

/******************
 * 显示函数
 * 根据字库的不同,显示函数分两种,一种是二维数组的方式,比较直观，一个数据对应一个点，
 * 一种是每行一个数据，一次刷一行显示。
 * Display(字符数组'兼容两种字库存储方式的数组',显示时间'默认1s')
 * 
 *****************/
void Display(uint8_t MAP[][8], unsigned long Set_Time = 1000)
{
	unsigned long Old_Time = millis();
	do
	{
		for (uint8_t i = 0; i <= 7; i++)
		{
			Clear_Screen();
			digitalWrite(COL[i], HIGH);
			for (uint8_t j = 0; j <= 7; j++)
			{
				digitalWrite(ROW[j], !(MAP[i][j]));
			}
			delay(2); //这里延时一下效果会好点,不然可能会出现亮度不一致;
		}
	} while (millis() - Old_Time < Set_Time);
	Old_Time = millis();
	Clear_Screen();
}

void Display(uint8_t MAP[], unsigned long Set_Time = 1000)
{
	unsigned long Old_Time = millis();
	do
	{
		for (uint8_t i = 0; i <= 7; i++)
		{
			Clear_Screen();
			digitalWrite(COL[i], HIGH);
			for (uint8_t j = 0; j <= 7; j++)
			{
				/****************************
				 * 这里的注释掉的代码是可以用point to point代码，就是代码里在什么位置的店，
				 * 对应屏幕上就是什么点,很奇怪这样的实现方式是吧，因为数组在内存的存放的方式
				 * 的问题，导致存进去point to point 点的数据,会错误的像是在屏幕上;
				 * 例如0XA5,它是以45670123的方式存储的,因此会导致出错,采用的纠正方式是,把行数据做
 				 * 判断然后移位操作,具体实现见代码(很简单,给自己简单备注下,了解一下数组的存值方式)。
				 * but 重点来了,我用取模软件取出来的值,用直接按位取来刷屏,居然显示的是正常的.
				 * 所以下面保留了两种刷屏方式,如果下面那句不对,可以试试取消掉下面得双斜线部分,并且
				 * 把下面那句注释掉。				 * 
				 * **************************/
				// if (j <= 3)
				// {
				// 	digitalWrite(ROW[j + 4], !((MAP[i] << j) & 0X80));
				// }
				// else
				// {
				// 	digitalWrite(ROW[j - 4], !((MAP[i] << j) & 0X80));
				// }
					digitalWrite(ROW[j], !((MAP[i] << j) & 0X80));
			}
			delay(2); //这里延时一下效果会好点,不然可能会出现亮度不一致;
		}
	} while (millis() - Old_Time < Set_Time);
	Old_Time = millis();
	Clear_Screen();
}

void loop(void)
{
	Display(MAP0, 1000);
	Display(MAP1, 1000);
	Display(MAP2, 1000);
	Display(MAP3, 2000);
}