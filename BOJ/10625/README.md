# [Diamond III] Decoding Ancient Messages - 10625 

[문제 링크](https://www.acmicpc.net/problem/10625) 

### 성능 요약

메모리: 2168 KB, 시간: 0 ms

### 분류

헝가리안

### 제출 일자

2026년 4월 9일 14:59:46

### 문제 설명

<p>Professor Y's work is to dig up ancient artifacts. Recently, he found a lot of strange stone plates, each of which has <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-msup><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: 0.363em; margin-left: 0.054em;"><mjx-mn class="mjx-n" size="s"><mjx-c class="mjx-c32"></mjx-c></mjx-mn></mjx-script></mjx-msup></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><msup><mi>N</mi><mn>2</mn></msup></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N^2\)</span></mjx-container> characters arranged in an <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-cD7"></mjx-c></mjx-mo><mjx-mi class="mjx-i" space="3"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi><mo>×</mo><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N \times N\)</span></mjx-container> matrix. Further research revealed that each plate represents a message of length <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N\)</span></mjx-container>. Also, the procedure to decode the message from a plate was turned out to be the following:</p>

<ol>
	<li>
	<p>Select <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N\)</span></mjx-container> characters from the plate one by one so that any two characters are neither in the same row nor in the same column.</p>
	</li>
	<li>
	<p>Create a string by concatenating the selected characters.</p>
	</li>
	<li>
	<p>Among all possible strings obtained by the above steps, find the lexicographically smallest one. It is the message represented by this plate.</p>
	</li>
</ol>

<p>NOTE: The order of the characters is defined as the same as the order of their ASCII values (that is, <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-texatom texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D670 TEX-T"></mjx-c></mjx-mi></mjx-texatom><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-texatom space="4" texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D671 TEX-T"></mjx-c></mjx-mi></mjx-texatom><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c22EF"></mjx-c></mjx-mo><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-texatom space="4" texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D689 TEX-T"></mjx-c></mjx-mi></mjx-texatom><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-texatom space="4" texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D68A TEX-T"></mjx-c></mjx-mi></mjx-texatom><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-texatom space="4" texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D68B TEX-T"></mjx-c></mjx-mi></mjx-texatom><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c22EF"></mjx-c></mjx-mo><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c3C"></mjx-c></mjx-mo><mjx-texatom space="4" texclass="ORD"><mjx-mi class="mjx-ty"><mjx-c class="mjx-c1D6A3 TEX-T"></mjx-c></mjx-mi></mjx-texatom></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">A</mi></mrow><mo><</mo><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">B</mi></mrow><mo><</mo><mo>⋯</mo><mo><</mo><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">Z</mi></mrow><mo><</mo><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">a</mi></mrow><mo><</mo><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">b</mi></mrow><mo><</mo><mo>⋯</mo><mo><</mo><mrow data-mjx-texclass="ORD"><mi mathvariant="monospace">z</mi></mrow></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(\mathtt{A} \lt \mathtt{B} \lt \cdots \lt \mathtt{Z} \lt \mathtt{a} \lt \mathtt{b} \lt \cdots \lt \mathtt{z}\)</span></mjx-container>).</p>

<p>After struggling with the plates, Professor Y gave up decoding messages by hand. You, a great programmer and Y's old friend, was asked for a help. Your task is to write a program to decode the messages hidden in the plates.</p>

### 입력 

 <p>The input is formated as follows:</p>

<pre>N
c<sub>11</sub>c<sub>12</sub>...c<sub>1N</sub>
c<sub>21</sub>c<sub>22</sub>...c<sub>2N</sub>
:
:
c<sub>N1</sub>c<sub>N2</sub>...c<sub>NN</sub>
</pre>

<p>The first line contains an integer <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N\)</span></mjx-container> (<mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c></mjx-mn><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2264"></mjx-c></mjx-mo><mjx-mi class="mjx-i" space="4"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2264"></mjx-c></mjx-mo><mjx-mn class="mjx-n" space="4"><mjx-c class="mjx-c35"></mjx-c><mjx-c class="mjx-c30"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>1</mn><mo>≤</mo><mi>N</mi><mo>≤</mo><mn>50</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(1 \le N \le 50\)</span></mjx-container>). Each of the subsequent <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N\)</span></mjx-container> lines contains a string of <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\(N\)</span></mjx-container> characters. Each character in the string is an uppercase or lowercase English letter (<code>A</code>-<code>Z</code>, <code>a</code>-<code>z</code>).</p>

### 출력 

 <p>Print the message represented by the plate in a line.</p>

