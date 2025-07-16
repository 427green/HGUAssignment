#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*
BPMゲーム
Enterキーをリズムよく押すことで指定されたBPMに合わせるゲーム
*/

//コメント化printf＝デバッグ用

#define LOOP 5 //キーを何回押すかの回数
#define min 30 //BPMに用いる乱数の最小
#define max 300 //BPMに用いる乱数の最大


int Tar = 0; //目標BPMの乱数(target)
char p; //playerの入力,scanfを用いた遷移用
double RecordRap[LOOP] = {0}; //各ラップ数の記録配列
double RecordBPM[LOOP] = {0}; //BPMの記録配列

double StartTime, StopTime; //UNIX時間でストップウォッチ
double RapTime; //ラップ一時変数
double SumTime, FinTime = 0; //時間の合計、BPMの一時変数

double BpmSub; //絶対値化に使用

int main(void) {
	int cou = 0; //プレイヤーのカウント回数
	//乱数生成
	srand((unsigned int)time(NULL));  // 現在時刻を使った乱数の初期化
	Tar = rand() % (max - min + 1) + min;  // min以上max以下の乱数
	//printf("%d\n",Tar);

	//初期説明
	printf("BPMゲーム　ー %d 回enterキーを押して目指せジャスト！ー\n",LOOP);
	printf("BPMの... %d に合わせろ\n", Tar);

	Sleep(1000);
	printf("Enterキーで入力後スタート\n");
	scanf("%c", &p);

	/*入力パート*/
	
	while (cou < LOOP) {
		//開始時間と押下時時間　取得
		StartTime = GetTickCount64();
		printf("%d回目", (cou + 1));
		scanf("%c",&p);
		StopTime = GetTickCount64();

		RapTime = (double)(StopTime - StartTime)  / 1000.0;
		RecordRap[cou] = RapTime;
		SumTime += RecordRap[cou];
		//BPMの計算
		RecordBPM[cou] = (60.0 / RecordRap[cou]); 
		//printf("%d回、%f\n",cou,RecordBPM[cou]);

		//BPMを絶対値として判定
		BpmSub = (RecordBPM[cou] - Tar) > 0 ? (RecordBPM[cou] - Tar) : -(RecordBPM[cou] - Tar);
		/*途中BPMについての評価*/
		if ((int)BpmSub == 0) {
		printf("Excellent!\n");
		}
		else if (BpmSub <= 10) {
			printf("Perfect!\n");
			//押下時間の速遅
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else if (BpmSub <= 20) {
			printf("Good\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else if (BpmSub <= 40) {
			printf("ん？\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else {
			printf("え？\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}

		
		//printf("SumTime%f\n", SumTime);
		//printf("FinTime:%f\n", FinTime);
		printf("\n");
		cou++;
	}
	FinTime = LOOP * (60.0 / SumTime); 

	/*待機演出*/
	printf("結果は");
	for (int n = 0; n < 3; n++) {
		printf(".");
		Sleep(600);
	}
	printf("\n");
	
	//printf("%f", BpmSub);
	/*結果パート*/
	BpmSub = (FinTime - Tar) > 0 ? (FinTime - Tar) : -(FinTime - Tar);

	if ((int)BpmSub == 0) {
		printf("完璧！絶対音感のように絶対リズム感があるのでしょうか\n");
	}
	else if (BpmSub <= 15) {
		printf("惜しい！ボウリングならば両端にピンが残るもどかしさがあるでしょう\n");
	}
	else if (BpmSub <= 30) {
		printf("奔放さがあります。アンダンテな人でいいと思います\n");
	}
	else {
		printf("ずれてます。もっと日々の1秒1秒を味わってみては？\n");
	}

	Sleep(1000);
	printf("＞Enterキーで詳細結果を表示\n");
	scanf("%c", &p);

	printf("----------------------\n");
	printf("詳細結果:\n");
	printf("|ラップタイム:\n");
	//各ラップタイムの生成
	for (int j = 0; j < LOOP; j++) {
		printf("|%d回目： %.3fs　BPM %.1f\n", j+1, RecordRap[j],RecordBPM[j]);
	}
	printf("|----- \n");
	printf("|全体のBPM:%.1f\n",FinTime);
	printf("----------------------\n");

}