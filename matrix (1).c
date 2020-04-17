#include <stdio.h>//입출력 함수 포함 전처리기
#include <time.h>//랜덤 함수 포함 전처리기
#include <stdlib.h>//동적 할당을 해줄 함수 포함 전처리기

int** create_matrix(int row, int col);//행렬을 만들 함수
int free_matrix(int** matrix, int row, int col);//동적 할당 해제 함수
void print_matrix(int** matrix, int row, int col);//행렬을 출력해줄 함수
int fill_data(int **matrix, int row, int col);//랜덤으로 행렬의 요소를 채워줄 함수
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);//전치행렬을 만들어줄 함수
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);//행렬을 더해줄 함수
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);//행렬을 빼줄 함수
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);//행렬을 곱을 해줄 함수

int main(void)
{
	int row,col;//행렬의 행과 열
	int **A;//행렬 A
	int **B;//행렬 B
	int **At;//행렬A의 전치행렬
	int **Axt;//행렬 A와 전치행렬을 곱한 행렬
	int **sum;//A+B
	int **sub;//A-B
	int **mul;//A*At

	srand((unsigned)time(NULL));//랜덤 값을 나오게 해줌

	printf("-----------[2019038038][한서영]--------------\n");
	printf("행열의 행과 열의 크기를 입력하세요: ");

	scanf("%d %d",&row,&col);//사용자에게 행과 열 값 받음

	A=create_matrix(row,col);//A행렬 할당
	B=create_matrix(row,col);//B행렬 할당
	At=create_matrix(col,row);//A의 전치행렬 할당
	Axt=create_matrix(row,row);//A와 A의 전치행렬 곱 할당
	sum=create_matrix(row,col);//합이 들어갈 행렬 할당
	sub=create_matrix(row,col);//뺄셈 들어갈 행렬 할당

	fill_data(A,row,col);//랜덤 값 넣음
	printf("행렬 A\n");
	print_matrix(A,row,col);//행렬 출력

	fill_data(B,row,col);//랜덤 값 넣음
	printf("행렬 B\n");
	print_matrix(B,row,col);//행렬 출력

	addition_matrix(A,B,sum,row,col);//A+B계산
	printf("행렬 A+B\n");
	print_matrix(sum,row,col);//행렬 출력

	subtraction_matrix(A,B,sub,row,col);//A-B
	printf("행렬 A-B\n");
	print_matrix(sub,row,col);//행렬 출력

	transpose_matrix(A,At,row,col);//A의 전치행렬
	printf("A의 전치행렬\n");
	print_matrix(At,col,row);//행렬 출력

	multiply_matrix(A,At,Axt,row,col);//A*At
	printf("A*At\n");
	print_matrix(Axt,row,row);//행렬 출력
	
	free_matrix(A,row,col);
	free_matrix(B,row,col);
	free_matrix(At,col,row);
	free_matrix(Axt,row,row);
	free_matrix(sum,row,col);
	free_matrix(sub,row,col);//배열 동적 할당 해제

	return 0;//외부로 0값 반환

}
int** create_matrix(int row, int col)//행렬 생성
{
	if(row<=0||col<=0)//행이나 열이 0보다 작으면
	{
		printf("Check the sizes of row and col!\n");
		//입력값 확인하도록 함
	}
	int **array = (int**)malloc(sizeof(int *)*row);//배열의 행 동적할당

	for(int i=0;i<row;i++)
		array[i]=(int*)malloc(sizeof(int)*col);//배열의 요소들 동적할당

	if(array==NULL){//배열이 할당되지 않은 경우
		printf("적절한 배열이 생성되지 않았습니다.");
		//배열이 생성되지 않음을 알려줌
	}
	return array;
		
}
int free_matrix(int** matrix, int row, int col)//배열 해제
{
	for(int i=0;i<row;i++)//row번 반복
	{
		free(matrix[i]);//배열 해제
		matrix[i]=NULL;//NULL값 초기화
	}
	free(matrix);//배열 해제
	matrix=NULL;//NULL값 초기화
	if(matrix!=NULL)//만약 NULL값이 아니면
	{
		printf("메모리가 해제되지 않았습니다.");//메모리가 해제되지 않았음을 알려줌
		return -1;
	}
	
}
void print_matrix(int** matrix, int row, int col)//행렬 출력
{
	for(int i=0;i<row;i++)//row만큼 반복
	{
		for(int j=0;j<col;j++)//col만큼 반복
		{
			printf("%5d ",matrix[i][j]);//배열 요소 출력
		}
		printf("\n");
	}
	printf("\n");
}
int fill_data(int **matrix, int row, int col)//배열의 값을 랜덤값으로 채움
{
	for(int i=0;i<row;i++)//row만큼 반복
	{
		for(int j=0;j<col;j++)//col만큼 반복
		{
			matrix[i][j]=rand()%20;//0-20값 나옴
		}
	}
	
	for(int k=0;k<row;k++)//row만큼 반복
	{
		for(int p=0;p<col;p++)//col만큼 반복
		{
			if((matrix[k][p]<0)||(matrix[k][p]>19))//배열에 랜덤값 이하 또는 이상이 들어가면
				printf("배열에 옳지 않은 값이 들어갔습니다.\n");
			return -1;//잘못되었다고 알려줌
		}
	}
}
int transpose_matrix(int **matrix, int **matrix_t, int row, int col)//전치행렬 생성
{
	for(int i=0;i<row;i++)//row만큼 반복
	{
		for(int j=0;j<col;j++)//col만큼 반복
		{
			matrix_t[j][i]=matrix[i][j];//전치행렬 값 할당
		}
	}
	if(matrix_t==NULL){//만약 전치행렬 값이 들어가지 않았으면
		printf("전치 행렬에 값이 들어가지 않았습니다.\n");
		return -1;//오류임을 알려준다.
	}

}
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)//합 행렬 생성 함수
{
	for(int i=0;i<row;i++)//row만큼 반복
	{
		for(int j=0;j<col;j++)//col만큼 반복
		{
			matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];//합의 값들을 넣어준다.
		}
	}
	if(matrix_sum==NULL){//sum에 값이 없으면
		printf("합 행렬에 값이 들어가지 않았습니다.\n");
		return -1;//오류임을 알려줌
	}
}
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)//행렬의 뺄샘 계산 함수
{
        for(int i=0;i<row;i++)//row만큼 반복
        {
                for(int j=0;j<col;j++)//col만큼 반복
                {
                        matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];//뺄셈 계산해줌
                }
        }	
	if(matrix_sub==NULL){//만약 뺄셈 함수에 아무것도 없으면
		printf("뺄셈 행렬에 값이 들어가지 않았습니다.\n");
		return -1;//오류임을 알려줌
	}
}
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col)//행렬의 곱 함수
{
	int sum=0;//합을 담을 변수 초기화
	for(int i=0;i<row;i++)//row만큼 반복
	{
		for(int j=0;j<row;j++)//row만큼 반복
		{
			for(int k=0;k<col;k++)//col만큼 반복
			
			{
				sum=matrix_a[i][k]*matrix_t[k][j]+sum;//곱의 요소들 계산
			}
			matrix_axt[i][j]=sum;//할당해줌
			sum=0;	//반복문이 다시 도는 경우를 생각해 sum은 다시 0으로
		}

	}
	if(matrix_axt==NULL){//변수에 값이 할당되지 않으면
		printf("곱셈 행렬에 값이 들어가지 않습니다.\n");
		return -1;//오류임을 알려줌
	}

}
