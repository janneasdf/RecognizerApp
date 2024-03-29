/*********************************************
				Timerクラス			「Timer.cpp」
 **********************************************/

#include "Timer.h"

Timer *Timer::timInstance = NULL;

/******************************************
							Singletonメソッド
 ******************************************/
/* Singletonインスタンス生成 */
Timer *Timer::getInstance(){
	if ( timInstance ){
		return timInstance;
	}else{
		timInstance = new Timer();
		return timInstance;
	}
} // getInstance

/* Singletonインスタンス破棄 */
void Timer::releaseInstance(){
	if ( timInstance ){
		delete timInstance;
		timInstance = NULL;
	}
} // releaseInstance

/***************************************************
											インタフェース
 ***************************************************/
/* 時間をセットする関数。
	 シーンクラスから毎ループ呼ばれる必要がある */
void Timer::update(void){
	prevTime = systemTime;
	systemTime = SDL_GetTicks();
	dt = (float)(systemTime - prevTime) / 1000.0f;
	if (dt < 0.001f){
		dt = 0.001f;
	}
} // update

/******************************************************************
							RDTSC命令を用いたタイマについての関数
 ******************************************************************/
/* RDTSC命令でCPUのクロックカウンタレジスタの値を読み出す */
ULONGLONG Timer::getRDTSCClockCount(){
	//DWORD hi,lo;
	//__asm {
	//	rdtsc
	//	mov hi, edx
	//	mov lo, eax
	//}
	//return (hi<<32)|lo;
	return __rdtsc();
} // getRDTSCClockCount

/* クロックカウントをmsecに変換する */
double Timer::getRDTSCMSeconds( ULONGLONG clockCount ){
	return ( (double)clockCount / (double)cpuClock ) * 1000.0;	// msecに変換
} // getRDTSCMSeconds

/***************************************************
						コンストラクタ / デストラクタ
 ***************************************************/
/* コンストラクタ */
Timer::Timer(){
	initializeTimer();
} // コンストラクタ

/* デストラクタ */
Timer::~Timer(){
} // デストラクタ

/* タイマーを初期化 */
void Timer::initializeTimer(void){
	prevTime = systemTime = SDL_GetTicks();
	prevTime--; // systemTime - prevTime = 0となるのを防ぐため
	calcCPUClock();
} // InitTimer

/******************************************************************
					RDTSC命令を用いたタイマ処理についての補助関数
 ******************************************************************/
/* プライオリティを設定する */
void Timer::hiPriority( BOOL enable ){

	static DWORD oldProcessClass;
	static DWORD oldThreadPriority;

	if( enable ){
		oldProcessClass   = GetPriorityClass( GetCurrentProcess() );
		oldThreadPriority = GetThreadPriority( GetCurrentThread() );
	} else {
		SetPriorityClass( GetCurrentProcess() , oldProcessClass );
		SetThreadPriority( GetCurrentThread() , oldThreadPriority );
	}
	Sleep(0);

	return;
} // hiPriority

/* CPUの動作クロックの測定(1000msecかかる) */
void Timer::calcCPUClock(){
	hiPriority( TRUE );
	ULONGLONG result1, result2;
	//SetThreadAffinityMask(GetCurrentThread(), 1);		// スレッドで使用するCPUコアを1つに限定
	{
		DWORD t = timeGetTime() + 100;
		while( timeGetTime() < t );
		t += 1000;
		result1 = __rdtsc();
		//__asm {
		//	rdtsc
		//	mov hi, edx
		//	mov lo, eax
		//}
		while( timeGetTime() < t );
		result2 = __rdtsc();
		//__asm {
		//	rdtsc
		//	mov hi2, edx
		//	mov lo2, eax
		//}
	}
	hiPriority( FALSE );
	cpuClock = result2 - result1;
	printf("高分解能タイマー用にCPUクロックを計測しました: %llu\n", cpuClock);
	//printf("CPU Clock: %I64 (measured for RDTSC Timer)\n", cpuClock);			// %lluが使えなかった場合
} // calcCPUClock
