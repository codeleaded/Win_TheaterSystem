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
TransformedView tv;
Rect rect;
Vec2 velocity;
Vec2 acceleration;


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

	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
	TransformedView_Offset(&tv,(Vec2){ 0.0f,0.0f });

	rect = (Rect){ 0.0f,0.0f,0.05f,0.05f };
	velocity = (Vec2){ 0.0f,0.0f };
	acceleration = (Vec2){ 0.0f,1.0f };
}
void Update(AlxWindow* w){
	tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	
	
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
	




	velocity = Vec2_Add(velocity,Vec2_Mulf(acceleration,w->ElapsedTime));
	rect.p = Vec2_Add(rect.p,Vec2_Mulf(velocity,w->ElapsedTime));

	if(rect.p.x<0.0f){
		rect.p.x = 0.0f;
		velocity.x *= -1.0f;
	}
	if(rect.p.y<0.0f){
		rect.p.y = 0.0f;
		velocity.y *= -1.0f;
	}
	if(rect.p.x>1.0f - rect.d.x){
		rect.p.x = 1.0f - rect.d.x;
		velocity.x *= -1.0f;
	}
	if(rect.p.y>1.0f - rect.d.y){
		rect.p.y = 1.0f - rect.d.y;
		velocity.y *= -1.0f;
	}



	Clear(WHITE);
	

	Vec2 bg_p = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	Vec2 bg_d = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
	RenderRect(bg_p.x,bg_p.y,bg_d.x,bg_d.y,BLUE);

	Vec2 p = TransformedView_WorldScreenPos(&tv,rect.p);
	Vec2 d = TransformedView_WorldScreenLength(&tv,rect.d);
	RenderRect(p.x,p.y,d.x,d.y,RED);

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