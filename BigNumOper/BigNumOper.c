#include <stdio.h>
#include <string.h>
#define MAX 50

void addOrSub(int xNum1[], int xNum2[], int xSub, int xLen, int xNeg) {
    //��°��¼Ʀr�ۥ[�ά۴�A�Ÿ��ȥHxNeg���P�_
    int i;

    if (xSub == 0) {    //�[�k
        for (i = 0; i <= xLen; i++) {
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
        for (i = 0; i <= xLen; i++) {
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

void mul(int xNum1[], int xNum2[], int xNum1Len, int xNum2Len, int xNeg) {
    int i, j;
    int mLen = xNum1Len + xNum2Len;
    int mAns[MAX*2] = { 0 };
    for (i = 0; i < xNum2Len; i++) {
        for (j = 0; j < xNum1Len; j++) {
            if (xNum2[i] == 0) {
                break;
            }
            mAns[i + j] += xNum2[i] * xNum1[j];
        }
    }

    for (i = 0; i < mLen; i++) {
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
    /*else {
        printf("+");
    }*/

    for (i = mLen - 1; i >= 0; i--) {
        printf("%d", mAns[i]);
    }
    printf("\n");
}

void testOper(char xNum1[], char xNum2[], char xOper) {
    int i, j;
    int mSwap = 0;      //�e��洫flag
    int mNum1Neg = 0;   //Num1�t��flag
    int mNum2Neg = 0;   //Num2�t��flag
    int mNum1[MAX] = { 0 };
    int mNum2[MAX] = { 0 };

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
        //for (i = mNum1Neg, j = mNum2Neg; (i < mNum1Len + mNum1Neg) && (j < mNum2Len + mNum2Neg); i++, j++) {
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

        for (i = mNum1Len + mNum1Neg - 1, j = 0; i >= mNum1Neg; i--, j++) {
            mNum1[j] = xNum2[i] - '0';
        }
        for (i = mNum2Len + mNum2Neg - 1, j = 0; i >= mNum2Neg; i--, j++) {
            mNum2[j] = xNum1[i] - '0';
        }

    }
    else {  //�����洫,������J
        for (i = mNum1Len + mNum1Neg - 1, j = 0; i >= mNum1Neg; i--, j++) {
            mNum1[j] = xNum1[i] - '0';
        }
        for (i = mNum2Len + mNum2Neg - 1, j = 0; i >= mNum2Neg; i--, j++) {
            mNum2[j] = xNum2[i] - '0';
        }
    }

    if (xOper == '+') {
        if (mNum1Neg == 0 && mNum2Neg == 0) {
            addOrSub(mNum1, mNum2, 0, mLen, 0);
        }
        else if (mNum1Neg == 0 && mNum2Neg == 1) {
            addOrSub(mNum1, mNum2, 1, mLen, 0);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 0) {
            addOrSub(mNum1, mNum2, 1, mLen, 1);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 1) {
            addOrSub(mNum1, mNum2, 0, mLen, 1);
        }
    }
    else if(xOper == '-'){     //�����L�洫����(mSwap==1),���פ]�ݭn�[�t��
        if (mNum1Neg == 0 && mNum2Neg == 0) {
            addOrSub(mNum1, mNum2, 1, mLen, 0 ^ mSwap);
        }
        else if (mNum1Neg == 0 && mNum2Neg == 1) {
            addOrSub(mNum1, mNum2, 0, mLen, 0 ^ mSwap);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 0) {
            addOrSub(mNum1, mNum2, 0, mLen, 1 ^ mSwap);
        }
        else if (mNum1Neg == 1 && mNum2Neg == 1) {
            addOrSub(mNum1, mNum2, 1, mLen, 1 ^ mSwap);
        }
    }
    else if (xOper == '*') {
        mul(mNum1, mNum2, mLen, mNum2Len, mNum1Neg ^ mNum2Neg);
    }
}

int main(){
    testOper("0", "0", '-');
    testOper("0", "-2", '-');
    testOper("-1", "0", '-');
    testOper("0", "0", '-');
    testOper("-9", "5", '+');
    testOper("-1", "0", '-');
    testOper("1", "-1", '-');
    testOper("-1", "9", '-');
    testOper("-99998", "99999", '-');

    testOper("9999999", "987", '+');
    testOper("-9999999", "-987", '+');
    testOper("-9999999", "987", '-');
    testOper("9999999", "-987", '-');
    testOper("1111333", "333", '+');
    testOper("9999999", "987", '-');
    testOper("-9999999", "-987", '-');
    testOper("333", "1111333", '+');
    testOper("333", "-1111333", '+');
    testOper("-333", "1111333", '+');
    testOper("333", "1111333", '-');
    testOper("99999", "99998", '-');
	
    testOper("0", "0", '*');
    testOper("0", "123", '*');
	testOper("123", "123", '*');
    testOper("-123", "123", '*');
    testOper("123", "-123", '*');
    testOper("-123", "-123", '*');
    testOper("1231", "123", '*');
    testOper("-123", "1231", '*');
    testOper("-2", "99999999999999999999999", '*');
    testOper("99999999999999999999999", "-2", '*');
    
    //system("pause");
    return 0;
}