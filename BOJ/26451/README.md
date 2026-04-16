# [Diamond V] Permutation Magic - 26451 

[문제 링크](https://www.acmicpc.net/problem/26451) 

### 성능 요약

메모리: 2948 KB, 시간: 20 ms

### 분류

그래프 이론, 최대 유량, 이분 매칭, 최소 비용 최대 유량, 헝가리안

### 제출 일자

2026년 4월 9일 19:48:00

### 문제 설명

<p>There are sequences $A = (a_1, \dots , a_N)$ and $B = (b_1, \dots , b_N)$ with the same length $N$. $a_i$ denotes the $i$-th element of $A$, and its value is an integer between $1$ and $M$, and the same is true for $b_j$, which is the $j$-th element of the sequence $B$.</p>

<p>You can do a magic trick to the sequence $A$ only once: you can prepare a permutation $P = (p_1, \dots , p_M)$of integers from $1$ through $M$, and can change the sequence $A$ to $A'$ by using $P$ as follows: $a'_i = p_{a_i}$ ($1 \le i \le N$).</p>

<p>You want to make the distance between the sequence $A'$ and another sequence $B$ closer by changing $A$ to $A'$ through a magic trick. The "distance" between two sequences is defined as Hamming distance. The Hamming distance between two equal-length sequences is the number of positions at which the corresponding values are different.</p>

<p>Among all possible $A'$, you have to find a sequence which satisfies all of the following conditions.</p>

<ul>
	<li>No other possible sequences as $A'$ have a smaller distance to $B$ than the distance between this sequence and $B$.</li>
	<li>It is the lexicographically smallest sequence among possible sequences which has the same distance between $B$.</li>
</ul>

<p>Here, a sequence $X = (x_1, x_2, \dots , x_N)$ is "lexicographically smaller" than another same length sequence $Y = (y_1, y_2, \dots , y_N)$ if and only if the following condition holds: there exists an index $i$ ($1 \le i \le N$), such that $x_j = y_j$ for all indices $j$ ($1 \le j < i$), and $x_i < y_i$.</p>

### 입력 

 <p>The input consists of a single test case of the following format.</p>

<blockquote>
<p>$N$ $M$</p>

<p>$a_1$ $\dots$ $a_N$</p>

<p>$b_1$ $\dots$ $b_N$</p>
</blockquote>

<p>The first line consists two integers $N$ ($1 \le N \le 100\,000$) and $M$ ($1 \le M \le 60$), which represent that the length of sequences are $N$, and each sequence has $N$ values between $1$ and $M$.</p>

<p>The second line consists of $N$ integers. The $i$-th integer is denoted $a_i$ ($1 \le a_i \le M$).</p>

<p>The third line consists of $N$ integers. The -th integer is denoted $b_i$ ($1 \le b_i \le M$).</p>

### 출력 

 <p>Print $N$ integers, with spaces in between. The $i$-th integer should be the $i$-th element of a sequence which satisfies all conditions in the problem statement. Each element of a sequence should be printed as an integer.</p>

