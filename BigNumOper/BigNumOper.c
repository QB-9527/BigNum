#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

void doAdditionOrSubtraction(int xNum1[], int xNum2[], int xSub, int xLen, int xNeg) {
    //��°��¼Ʀr�ۥ[�ά۴�A�Ÿ��ȥHxNeg���P�_
    int i;

    if (xSub == 0) {    //�[�k
        for (i = 0; i < xLen; i++) {
            xNum1[i] = xNum1[i] + xNum2[i];
            if (xNum1[i] > 9) {
                xNum1[i] -= 10;
                xNum1[i + 1]++;
            }
        }
        if (xNum1[xLen] != 0) {
            xLen++;
        }
    }
    else if (xSub == 1) {   //��k
        //�Ȱ�num1>num2�����p�U
        for (i = 0; i < xLen; i++) {
            xNum1[i] = xNum1[i] - xNum2[i];
            if (xNum1[i] < 0) {
                xNum1[i] += 10;
                xNum1[i + 1]--;
            }
        }
        while (xNum1[xLen - 1] == 0 && xLen > 1)
        {
            xLen--;
        }
    }

    if (xNeg==1) {
        printf("-");
    }
    else {
        printf("+");
    }

    for (i = xLen - 1; i >= 0; i--) {
        printf("%d", xNum1[i]);
    }
    printf("\n");

}

void doMultiplication(int xNum1[], int xNum2[], int xNum1Len, int xNum2Len, int xNeg) {
    int i, j;
    int mLen = xNum1Len + xNum2Len;
    int* mAns = calloc(mLen, sizeof(int));
	
    for (i = 0; i < xNum2Len; i++) {
        for (j = 0; j < xNum1Len; j++) {
            if (xNum2[i] == 0) {
                break;
            }
            mAns[i + j] += xNum2[i] * xNum1[j];
        }
    }

    for (i = 0; i < mLen - 1; i++) {
        mAns[i + 1] += mAns[i] / 10;
        mAns[i] = mAns[i] % 10;
    }

    while (mAns[mLen - 1] == 0 && mLen > 1)
    {
        mLen--;
    }

    if (xNeg == 1) {
        printf("-");
    }

    for (i = mLen - 1; i >= 0; i--) {
        printf("%d", mAns[i]);
    }
    printf("\n");

    free(mAns);
}

void testOper(char xNum1[], char xNum2[], char xOper) {
	//�]��k�u�Ҽ{�j�ƴ�p��
	//�b�o�̷|���T�{�ǤJ���Ĥ@�ӼƦr�O�_���j�A�S�����ܰ��洫�ð�flag�A�A���B��
	
    int i, j;
    int mSwap = 0;      //�e��洫flag
    int mNum1Neg = 0;   //Num1�t��flag
    int mNum2Neg = 0;   //Num2�t��flag

    int* mNum1 = calloc(MAX, sizeof(int));
    int* mNum2 = calloc(MAX, sizeof(int));

    int mNum1Len = strlen(xNum1);
    int mNum2Len = strlen(xNum2);

    //��t��,��flag
    if (xNum1[0] == '-') {
        mNum1Neg = 1;
        mNum1Len--;
    }
    if (xNum2[0] == '-') {
        mNum2Neg = 1;
        mNum2Len--;
    }

    //�ˬdxNum1>xNum2,�S�����ܰ��洫
    int mLen = mNum1Len;    //mLen������j���Ʀr����,���w�]xNum1>xNum2
    if (mNum1Len < mNum2Len) {
        mSwap = 1;
    }
    else if (mNum1Len == mNum2Len) {
        for (i = 0; i < mNum1Len; i++) {
            if ((xNum1[i + mNum1Neg] - '0') < (xNum2[i + mNum2Neg] - '0')) {
                mSwap = 1;
                break;
            }
        }
    }

    //�N�Ʀr�q�Ӧ�ƶ}�l��J�ܰ}�C
    if (mSwap == 1) {   //xNum1<xNum2,�ݭn�N�Ʀr�洫
        mLen = mNum2Len;
        mNum2Len = mNum1Len;
        mNum1Len = mLen;

        int mTemp = mNum1Neg;
        mNum1Neg = mNum2Neg;
        mNum2Neg = mTemp;

        for (i = mNum1Len - 1, j = 0; i >= 0; i--, j++) {
            mNum1[j] = xNum2[i + mNum1Neg] - '0';
        }
        for (i = mNum2Len - 1, j = 0; i >= 0; i--, j++) {
            mNum2[j] = xNum1[i + mNum2Neg] - '0';
        }

    }
    else {  //�����洫,������J
        for (i = mNum1Len - 1, j = 0; i >= 0; i--, j++) {
            mNum1[j] = xNum1[i + mNum1Neg] - '0';
        }
        for (i = mNum2Len - 1, j = 0; i >= 0; i--, j++) {
            mNum2[j] = xNum2[i + mNum2Neg] - '0';
        }
    }

    if (xOper == '+') {
        if (mNum1Neg == 0 && mNum2Neg == 0) {
            doAdditionOrSubtraction(mNum1, mNum2, 0, mLen, 0);
        }
        else if (mNum1Neg == 0 && mNum2Neg == 1) {
            doAdditionOrSubtraction(mNum1, mNum2, 1, mLen, 0);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 0) {
            doAdditionOrSubtraction(mNum1, mNum2, 1, mLen, 1);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 1) {
            doAdditionOrSubtraction(mNum1, mNum2, 0, mLen, 1);
        }
    }
    else if(xOper == '-'){     //�����L�洫����(mSwap==1),���פ]�ݭn�[�t��
        if (mNum1Neg == 0 && mNum2Neg == 0) {
            doAdditionOrSubtraction(mNum1, mNum2, 1, mLen, 0 ^ mSwap);
        }
        else if (mNum1Neg == 0 && mNum2Neg == 1) {
            doAdditionOrSubtraction(mNum1, mNum2, 0, mLen, 0 ^ mSwap);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 0) {
            doAdditionOrSubtraction(mNum1, mNum2, 0, mLen, 1 ^ mSwap);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 1) {
            doAdditionOrSubtraction(mNum1, mNum2, 1, mLen, 1 ^ mSwap);
        }
    }
    else if (xOper == '*') {
        doMultiplication(mNum1, mNum2, mLen, mNum2Len, mNum1Neg ^ mNum2Neg);
    }

    free(mNum1);
    free(mNum2);
}

int main(){
    testOper("0", "0", '-');            printf("+0\n\n");
    testOper("0", "-2", '-');           printf("+2\n\n");
    testOper("-1", "0", '-');           printf("-1\n\n");
    testOper("0", "0", '-');            printf("+0\n\n");
    testOper("-9", "5", '+');           printf("-4\n\n");
    testOper("-1", "0", '-');           printf("-1\n\n");
    testOper("1", "-1", '-');           printf("+2\n\n");
    testOper("-1", "9", '-');           printf("-10\n\n");
    testOper("10", "9", '-');           printf("+1\n\n");
    testOper("-99998", "99999", '-');   printf("-199997\n\n");

    testOper("9999999", "987", '+');    printf("+10000986\n\n");
    testOper("-9999999", "-987", '+');  printf("-10000986\n\n");
    testOper("-9999999", "987", '-');   printf("-10000986\n\n");
    testOper("9999999", "-987", '-');   printf("+10000986\n\n");
    testOper("1111333", "333", '+');    printf("+1111666\n\n");
    testOper("9999999", "987", '-');    printf("+9999012\n\n");
    testOper("-9999999", "-987", '-');  printf("-9999012\n\n");
    testOper("333", "1111333", '+');    printf("+1111666\n\n");
    testOper("333", "-1111333", '+');   printf("-1111000\n\n");
    testOper("-333", "1111333", '+');   printf("+1111000\n\n");
    testOper("333", "1111333", '-');    printf("-1111000\n\n");
    testOper("99999", "99998", '-');    printf("+1\n\n");
	
    testOper("0", "0", '*');            printf("0\n\n");
    testOper("0", "123", '*');          printf("0\n\n");
    testOper("123", "123", '*');        printf("15129\n\n");
    testOper("-123", "123", '*');       printf("-15129\n\n");
    testOper("123", "-123", '*');       printf("-15129\n\n");
    testOper("-123", "-123", '*');      printf("15129\n\n");
    testOper("1231", "123", '*');       printf("151413\n\n");
    testOper("-123", "1231", '*');      printf("-151413\n\n");
    testOper("-2", "9999999999999999999999999999", '*');    printf("-19999999999999999999999999998\n\n");
    testOper("9999999999999999999999999999", "-2", '*');    printf("-19999999999999999999999999998\n\n");
    
    //system("pause");
    return 0;
}