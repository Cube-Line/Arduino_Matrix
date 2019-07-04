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

#include <NeoPixelBus.h>

const uint16_t PixelCount = 256; //这里最少需要4个灯，过少可能会报错,是NeoPixel this example assumBus库的问题，具体我还没来得及细究，反正我们点阵灯珠够多，暂时不管他了，😄！ es 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 3;		 // 这里引脚 对8266来说无用，DMA传输方式,8266默认GPIO3/RXD ,make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 5 //这里调整点整亮度，晚点把它写成函数参数进去

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

//定义颜色
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

uint8_t MAP[] = {0x04, 0x0, 0x3, 0x0, 0x1, 0x0, 0x0, 0x4, 0xff, 0xfe, 0x4, 0x0, 0x4, 0x10, 0x7, 0xf8, 0x4, 0x10, 0x4, 0x10, 0x4, 0x10, 0x8, 0x10, 0x8, 0x10, 0x10, 0x10, 0x20, 0xa0, 0x40, 0x40};

void Display(uint16_t MAP[]);

void setup()
{
	Serial.begin(115200);
	while (!Serial)
		; // wait for serial attach

	Serial.println();
	Serial.println("Initializing...");
	Serial.flush();

	// 初始化点阵	this resets all the neopixels to an off state
	strip.Begin();
	strip.Show();

	Serial.println();
	Serial.println("Running...");
}

void loop()
{
	for (uint16_t i = 0; i <= 31; i++)
	{
		for (uint8_t j = 0; j <= 7; j++)
		{

			if ((MAP[i] << j) & 0x80)
			{
				strip.SetPixelColor(8 * i + j, white);
			}
			else
			{
				strip.SetPixelColor(8 * i + j, black);
			}

			// strip.SetPixelColor((1 << j) & 0x80, black);
			// strip.SetPixelColor((MAP[8 * i] << j) & 0x80, green);
		}
	}
	// strip.SetPixelColor(253,green);
	strip.Show();
	// delay(1000);
	// 	for (uint16_t i = 0; i <= 31; i++)
	// {
	// 	for (uint8_t j = 0; j <= 7; j++)
	// 	{

	// 		if((YAN[i]<<j)&0x80)
	// 		{
	// 			strip.SetPixelColor(8*i+j,white);
	// 		}
	// 		else
	// 		{
	// 			strip.SetPixelColor(8*i+j,black);
	// 		}

	// 		// strip.SetPixelColor((1 << j) & 0x80, black);
	// 		// strip.SetPixelColor((MAP[8 * i] << j) & 0x80, green);
	// 	}
	// }
	// strip.Show();
	// delay(1000);
}

void Display(uint16_t MAP[])
{
	for (uint16_t i = 0; i <= 31; i++)
	{
		for (uint8_t j = 0; j <= 7; j++)
		{

			if ((MAP[i] << j) & 0x80)
			{
				strip.SetPixelColor(8 * i + j, white);
			}
			else
			{
				strip.SetPixelColor(8 * i + j, black);
			}

			// strip.SetPixelColor((1 << j) & 0x80, black);
			// strip.SetPixelColor((MAP[8 * i] << j) & 0x80, green);
		}
	}
	strip.Show();
}