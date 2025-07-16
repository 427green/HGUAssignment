#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*
BPM�Q�[��
Enter�L�[�����Y���悭�������ƂŎw�肳�ꂽBPM�ɍ��킹��Q�[��
*/

//�R�����g��printf���f�o�b�O�p

#define LOOP 5 //�L�[�����񉟂����̉�
#define min 30 //BPM�ɗp���闐���̍ŏ�
#define max 300 //BPM�ɗp���闐���̍ő�


int Tar = 0; //�ڕWBPM�̗���(target)
char p; //player�̓���,scanf��p�����J�ڗp
double RecordRap[LOOP] = {0}; //�e���b�v���̋L�^�z��
double RecordBPM[LOOP] = {0}; //BPM�̋L�^�z��

double StartTime, StopTime; //UNIX���ԂŃX�g�b�v�E�H�b�`
double RapTime; //���b�v�ꎞ�ϐ�
double SumTime, FinTime = 0; //���Ԃ̍��v�ABPM�̈ꎞ�ϐ�

double BpmSub; //��Βl���Ɏg�p

int main(void) {
	int cou = 0; //�v���C���[�̃J�E���g��
	//��������
	srand((unsigned int)time(NULL));  // ���ݎ������g���������̏�����
	Tar = rand() % (max - min + 1) + min;  // min�ȏ�max�ȉ��̗���
	//printf("%d\n",Tar);

	//��������
	printf("BPM�Q�[���@�[ %d ��enter�L�[�������Ėڎw���W���X�g�I�[\n",LOOP);
	printf("BPM��... %d �ɍ��킹��\n", Tar);

	Sleep(1000);
	printf("Enter�L�[�œ��͌�X�^�[�g\n");
	scanf("%c", &p);

	/*���̓p�[�g*/
	
	while (cou < LOOP) {
		//�J�n���ԂƉ��������ԁ@�擾
		StartTime = GetTickCount64();
		printf("%d���", (cou + 1));
		scanf("%c",&p);
		StopTime = GetTickCount64();

		RapTime = (double)(StopTime - StartTime)  / 1000.0;
		RecordRap[cou] = RapTime;
		SumTime += RecordRap[cou];
		//BPM�̌v�Z
		RecordBPM[cou] = (60.0 / RecordRap[cou]); 
		//printf("%d��A%f\n",cou,RecordBPM[cou]);

		//BPM���Βl�Ƃ��Ĕ���
		BpmSub = (RecordBPM[cou] - Tar) > 0 ? (RecordBPM[cou] - Tar) : -(RecordBPM[cou] - Tar);
		/*�r��BPM�ɂ��Ă̕]��*/
		if ((int)BpmSub == 0) {
		printf("Excellent!\n");
		}
		else if (BpmSub <= 10) {
			printf("Perfect!\n");
			//�������Ԃ̑��x
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else if (BpmSub <= 20) {
			printf("Good\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else if (BpmSub <= 40) {
			printf("��H\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}
		else {
			printf("���H\n");
			(RecordBPM[cou] - Tar) > 0 ? printf("fast\n") : printf("slow\n");
		}

		
		//printf("SumTime%f\n", SumTime);
		//printf("FinTime:%f\n", FinTime);
		printf("\n");
		cou++;
	}
	FinTime = LOOP * (60.0 / SumTime); 

	/*�ҋ@���o*/
	printf("���ʂ�");
	for (int n = 0; n < 3; n++) {
		printf(".");
		Sleep(600);
	}
	printf("\n");
	
	//printf("%f", BpmSub);
	/*���ʃp�[�g*/
	BpmSub = (FinTime - Tar) > 0 ? (FinTime - Tar) : -(FinTime - Tar);

	if ((int)BpmSub == 0) {
		printf("�����I��Ή����̂悤�ɐ�΃��Y����������̂ł��傤��\n");
	}
	else if (BpmSub <= 15) {
		printf("�ɂ����I�{�E�����O�Ȃ�Η��[�Ƀs�����c����ǂ�����������ł��傤\n");
	}
	else if (BpmSub <= 30) {
		printf("�z����������܂��B�A���_���e�Ȑl�ł����Ǝv���܂�\n");
	}
	else {
		printf("����Ă܂��B�����Ɠ��X��1�b1�b�𖡂���Ă݂ẮH\n");
	}

	Sleep(1000);
	printf("��Enter�L�[�ŏڍ׌��ʂ�\��\n");
	scanf("%c", &p);

	printf("----------------------\n");
	printf("�ڍ׌���:\n");
	printf("|���b�v�^�C��:\n");
	//�e���b�v�^�C���̐���
	for (int j = 0; j < LOOP; j++) {
		printf("|%d��ځF %.3fs�@BPM %.1f\n", j+1, RecordRap[j],RecordBPM[j]);
	}
	printf("|----- \n");
	printf("|�S�̂�BPM:%.1f\n",FinTime);
	printf("----------------------\n");

}