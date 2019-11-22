#include <stdio.h>
#include "mesinkataSTDIN.h"


int main(){
	boolean isRun = true;
	while(isRun){
	//STARTKATA();
	//printf("%d\n", CKata.Length );
	//PrintKata(CKata);
		STARTKATASTDIN();
		PrintKata(CKataSTDIN);	
		if (CompareKata(CKataSTDIN,"FINISH")){

			//FINISH();
			isRun = false;
		}
	}
	
	STARTKATASTDIN();
	PrintKata(CKataSTDIN);	
	int num;
	scanf("%d", &num);
	printf("%d\n", num);
	printf("%d\n", num+num );

}