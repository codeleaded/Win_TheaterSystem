// #include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TheaterSystem.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"

TheaterSystem theater;
Vector trace;

void Setup(AlxWindow* w){
	theater = TheaterSystem_New(
		"./assets/FoldUp.png",
		"./assets/FoldDown.png",
		"./assets/Rainbow_Atlas.png",
		64
	);

	TheaterSystem_Set(&theater,0,(int[]){   },		TheaterOption_New(0,"David","NONE"));
	TheaterSystem_Add(&theater,0,(int[]){   },		TheaterOption_New(1,"David","Hello World!"));
	TheaterSystem_Add(&theater,1,(int[]){ 0 },		TheaterOption_New(2,"David","Its sooooo nice to meet you my friend!"));
	TheaterSystem_Add(&theater,2,(int[]){ 0,0 },	TheaterOption_New(3,"David","Its been a long way!"));
	TheaterSystem_Add(&theater,3,(int[]){ 0,0,0 },	TheaterOption_New(
		2,"David",
		"Bro ive found something! Its the Programming Language C.\
		Its simply the best! Wow ive never seen anything like that!\
		Im so glad that you have come to listen to my words!"
	));


	trace = Vector_New(sizeof(int));
}
void Update(AlxWindow* w){
	if(Stroke(ALX_KEY_LEFT).PRESSED){
		if(trace.size>0) Vector_PopTop(&trace);
	}
	if(Stroke(ALX_KEY_RIGHT).PRESSED){
		Branch* b = Tree_Get_Branch(&theater.theater,trace.size,trace.Memory);
		if(b->Childs.size>0) Vector_Push(&trace,(int[]){ 0 });
	}

	if(Stroke(ALX_KEY_UP).PRESSED){
		TheaterSystem_Up(&theater,trace.size,trace.Memory);
	}
	if(Stroke(ALX_KEY_DOWN).PRESSED){
		TheaterSystem_Down(&theater,trace.size,trace.Memory);
	}
	
	Clear(WHITE);

	TheaterSystem_Render(WINDOW_STD_ARGS,&theater,0.0f,100.0f,trace.size,trace.Memory);
}
void Delete(AlxWindow* w){
	Vector_Free(&trace);
    TheaterSystem_Free(&theater);
}

int main(){
    if(Create("Theater System",2200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}