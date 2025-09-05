#include "HEHAL.h"

void Sprintf_M(char *buff, const char *prefix, int val) 
{
    int i = 0;
    
    while (*prefix) 
		{
        buff[i++] = *prefix++;
    }
    
    Сonverter_Int_Str(buff + i,val);
}

void Сonverter_Int_Str(char *out_str, int in_digital)
{
	int countInt = 0; 
		
		if (in_digital < 0) {
        out_str[countInt++] = '-';
        in_digital = -in_digital;
    }

    int start = countInt;
    do {
        out_str[countInt++] = (in_digital % 10) + '0';
        in_digital /= 10;
    } while (in_digital > 0);

    // Ревер
    for (int j = start; j < start + (countInt - start) / 2; j++) {
        char temp = out_str[j];
        out_str[j] = out_str[countInt - j + start - 1];
        out_str[countInt - j + start - 1] = temp;
    }
    out_str[countInt] = '\0'; 
}

