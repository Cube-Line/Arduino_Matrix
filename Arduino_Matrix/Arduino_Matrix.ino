/****************arduino板载点阵板******************
 * by 未见
 * 2018/05/18
 * 测试 Ver 0.1.0
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

uint8_t COL[] = {2, 7, 17, 5, 10, 16, 11, 14};
uint8_t ROW[] = {6, 12, 13, 3, 15, 4, 8, 9};
uint8_t MAP[][8] = {	0,0,0,1,1,0,0,0,
						0,0,1,0,0,1,0,0,
						0,1,0,0,0,0,1,0,
						1,0,0,1,1,0,0,1,
						1,0,0,1,1,0,0,1,
						0,1,0,0,0,0,1,0,
						0,0,1,0,0,1,0,0,
						0,0,0,1,1,0,0,0,};

void setup(void)
{
	for (int i = 0; i <= 17; i++)
	{
		pinMode(i, OUTPUT);
	}
}





/******************
 * 清理屏幕残影
 *****************/
void Clear_Screen(void)
{
	for (int k = 0; k <= 7; k++)
	{

		digitalWrite(COL[k], HIGH);
		digitalWrite(ROW[k], LOW);
	}
}




/******************
 * 显示函数
 *****************/
void Display(uint8_t)
{
	for (int i = 0; i <= 7; i++)
	{
		Clear_Screen();
		digitalWrite(ROW[i], HIGH);
		for (int j = 0; j <= 7; j++)
		{
			digitalWrite(COL[j], !MAP[i][j]);
		}
		delay(2);//这里延时一下效果会好点,不然可能会出现亮度不一致;
	}
}




void loop(void)
{
	Display(MAP);
}