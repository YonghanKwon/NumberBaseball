#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //난수로 정답값을 선언하기 위해 필요한 라이브러리
#include <time.h> //난수 씨드값을 시간으로 하기위해 필요한 라이브러리

int same_check(int res[], int i); //정답이 될 숫자나 입력받는 숫자에 중복되는 숫자가 있는지 확인하는 함수, 배열중 중복된 숫자가 있는지 판별해야하므로 배열을 입력받고, 또한 배열의 값이 선언되지 않은 요소에 의해 중복된 값이 있다고 출력되는 경우를 통제하기 위해 몇번째 배열요소가 선언되는 중인지 입력받음

int main(void)
{
    int input[4];  //입력받는 숫자 4개
    int result[4];  //정답 숫자 4개
    int result_same_check = 0;  //정답값으로 입력된 배열에 중복된 값이 있으면 1, 없으면 0을 저장하는 변수
    int input_same_check = 0; //입력된 배열에 중복된 값이 있으면 1, 없으면 0을 저장하는 변수
    int range_check = 0; //
    srand(time(NULL)); //난수 씨드를 시간으로 함
    int turn = 0; //게임이 몇번째 턴인지 저장하는 변수
    int right_number = 0; //입력된 숫자중 정답과 같은 숫자의 갯수를 저장하는 변수
    int strike = 0; //strike 갯수를 저장하는 변수

    printf("숫자 야구!\n\n");
    for (int i = 0; i < 4; i++) //정답이 될 숫자가 4개이므로 4번 루프
    {
        do  //제일 처음선언되는 숫자는 중복될리 없으니 do while문 선택
        {
            result[i] = rand() % 10; //난수 범위가 0~9까지이므로 난수에 10을 나눈 나머지를 결과값에 저장
            if (i >= 1) //두번째 숫자부터 중복되는 숫자가 있는지 판별해야하므로 if문 선택
            {
                result_same_check = same_check(result, i); //정답 배열에 중복되는 경우가 있는지 판별
            }
        } while (result_same_check);  //중복되는 경우가 있다면 숫자를 다시 선언하도록 루프를 검
    }

    while (1) //게임이 몇턴만에 끝날지 모르므로 무한루프를 걸고 게임 성공시 break를 걸어서 루프 탈출
    {
        turn++; //게임이 몇턴째인지를 저장하는 변수, 처음이 0으로 초기화되어있으므로 +1회 해주고 턴이 지날때마다 값을 하나씩 더해줌
        for (int i = 0; i < 4; i++) //입력될 숫자가 4개이므로 4번 루프
        {
            do  //입력받는 숫자가 0~9 사이 범위이기때문에 그 범위를 넘어가는 값이 입력받는다면 다시 입력받도록 함. 처음 입력은 받아야하므로 do while문 선택
            {
                do //제일 처음 선언되는 숫자는 중복될리 없으니 do while문 선택
                {
                    printf("%d번째 숫자 입력(0~9) : ", i + 1);
                    scanf("%d", &input[i]); //숫자를 입력받음
                    if (i >= 1) //두번째 숫자부터 중복되는 숫자가 있는지 판별해야하므로 if문 선택
                    {
                        input_same_check = same_check(input, i);  //입력받은 숫자 배열에 중복되는 경우가 있는지 판별
                        if (input_same_check == 1)
                        {
                            printf("중복되는 숫자가 있으므로 숫자를 다시 입력해주세요!\n");
                        }
                    }
                    if (input[i] >= 10 | input[i] < 0)  //입력받은 숫자가 0~9의 범위를 만족하는지 판별
                    {
                        range_check = 1; //입력된 값의 범위가 0~9사이의 값이 아니라면 변수에 1을 저장
                        printf("범위초과이므로 숫자를 다시 입력해주세요!\n");
                    }
                    else
                        range_check = 0; //입력된 값의 범위가 0~9사이의 값이라면 변수에 0을 저장
                } while (range_check); //입력된 값이 범위를 만족하지 않으면 숫자를 다시 입력받도록 루프를 검
            } while (input_same_check);  //입력된 값이 중복되는 경우가 있다면 숫자를 다시 입력받도록 루프를 검
        }
        for (int i = 0; i < 4; i++)
        {
            if (input[i] == result[i])  //정답과 입력된 값이 일치하고 위치도 같을 경우
                strike++;  //값과 위치가 같을경우 strike변수에 1씩 추가 
        }
        for (int i = 0; i < 4; i++)  //위치상관하지 않고 숫자만 일치하는 경우
        {
            for (int j = 0; j < 4; j++)
            {
                if (input[i] == result[j])
                    right_number++; //값이 같을경우 right_number 변수에 1씩 추가
            }
        }
        int ball = right_number - strike;  //ball의 갯수는 위치는 다르고 숫자만 같은 경우의 갯수이므로 위치 상관없이 숫자만 일치하는 경우(right_number)에서 위치와 숫자가 같은 경우(strike)를 빼면 됨
        int out = 4 - right_number;  //out의 갯수는 총 4번의 시행중 숫자가 일치하지 않는 경우이므로 전체시행 4회중 숫자만 일치하는 경우(right_number)의 갯수를 빼주면 된다
        printf("%d strike %d ball %d out!\n\n", strike, ball, out);
        if (strike == 4) //게임의 승리조건인 숫자와 위치가 모두 맞는경우(strike가 4개일 경우)
        {
            printf("%d째턴에 성공!\n\n", turn);
            break;  // 게임이 몇턴만에 끝날지 모르므로 걸어둔 무한루프를 게임에서 승리하였기때문에 break를 걸어서 무한루프에서 탈출
        }
        right_number = 0; //매 턴마다 변수를 초기화시킴, 초기화를 하지 않을경우 만일 1번째턴에 1개를 맞추고 2번째 턴에 2개를 맞추었다면 2번째턴에 2개의 맞는 숫자(strike+ball=2)가 나와야하지만 3개의 숫자가 나온다는 결과가 나오게됨.
        strike = 0; //매 턴마다 변수를 초기화시킴, 위와 같은 이유(추가로 ball과 out을 초기화시키지 않는 이유는 ball과 out의 경우는 위의 변수와 달리 매 턴마다 새롭게 선언되고 초기화되는 변수이기 때문)
    }
    return 0;
}

int same_check(int res[], int i) //정답이 될 숫자나 입력받는 숫자에 중복되는 숫자가 있는지 확인하는 함수, 배열중 중복된 숫자가 있는지 판별해야하므로 배열을 입력받고, 또한 배열의 값이 선언되지 않은 요소에 의해 중복된 값이 있다고 출력되는 경우를 통제하기 위해 몇번째 배열요소가 선언되는 중인지 입력받음
{
    for (int j = 0; j < i; j++)  //선언되어있는 값중에서만 비교하기 위해 선언되어있는 숫자까지만 루프
    {
        if (res[i] == res[j]) //만약 이전의 값들과 같은 값이라면
            return 1;  //메인함수에 result_same_check 변수나 input_same_check 변수에 1을 저장하여 while문을 통해 숫자를 다시 선언받도록 함
    }
    return 0;  //이전의 값들과 다른 값이라면 메인함수에 result_same_check 변수나 input_same_check 변수에 0을 저장하여 while문을 통과하고 다음과정으로 넘어감.
}