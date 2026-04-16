# [Diamond III] Balance - 19043 

[문제 링크](https://www.acmicpc.net/problem/19043) 

### 성능 요약

메모리: 2160 KB, 시간: 0 ms

### 분류

그래프 이론, 최대 유량, 최소 비용 최대 유량, 헝가리안, 선형 계획법, 쌍대성

### 제출 일자

2026년 4월 9일 09:41:17

### 문제 설명

<p>We say that a matrix $A$ of size $N \times N$ is <em>balanced</em> if $A[i][j] + A[i + 1][j + 1] = A[i + 1][j] + A[i][j + 1]$ for all $1 \le i, j \le N - 1$.</p>

<p>You are given a matrix $A$ of size $N \times N$. Your task is to output another matrix $B$ of equal size such that $B$ is balanced and $B[i][j] \ge A[i][j]$ for all $1 \le i, j \le N$. Furthermore, your $B$ must have the minimum possible sum of entry values.</p>

### 입력 

 <p>The first line of input contains an integer $N$, the number of rows and columns of the matrix ($1 \le N \le 50$).</p>

<p>Each of the following $N$ lines contains $N$ integers. Together they describe the matrix $A$. It is guaranteed that $0 \le A[i][j] \le 35\,000$ for all $1 \le i, j \le N$.</p>

### 출력 

 <p>On the first line, print the sum of the values of the balanced matrix $B$ you found. On the next $N$ lines, print the balanced matrix in the same format as given in the input.</p>

<p>Any output matrix that meets the constraints described in the statement will be accepted. The values of the output matrix are not constrained in any way (specifically, they may exceed the value $35\,000$).</p>

