# 随机过程Chapter 5 

#### 5.8

$$
P_{ii}(t)=P(X(t+s)=i|X(s)=i)\\
=P(X(t+s)=i,没有经过转移|X(s)=i)+P(X(t+s)=i,经过两次及以上的转移|X(s)=i)\\
=e^{-v_it}+P(X(t+s)=i,经过两次及以上的转移|X(s)=i)\\
根据Markov链\\
P(X(t+s)=i,经过两次及以上的转移|X(s)=i)=\sum_jP_{ij}P(T_i+T_j\le t)\\
已知等待时间为分别有速率v_i、v_j的独立的指数随机变量\\
P(X(t+s)=i,经过两次及以上的转移|X(s)=i)/t\\
=lim_{t \to 0}\sum_jP_{ij}P(T_i+T_j\le t)/t\\
\le lim_{t \to 0}[\sum_{j\le M}P_{ij}P(T_i+T_j\le t)/t+\frac{1-e^{-v_it}}t(1-\sum_{j\le M}P_{ij}P(T_i\le t))]\\
P(T_i+T_j\le t)\le P(T_1+T_2\le t),T_1,T_2服从于v=max(v_i,v_j)的独立指数随机变量\\
=P(N(t)\ge 2),N(t)是速率为v的poisson过程\\
=o(t)\\
t \to 0\\
\frac{1-e^{v_it}}{t}\to v_i\\
\therefore P(X(t+s)=i,经过两次及以上的转移|X(s)=i)/t \le v_i(1-\sum_{j\le M}P_{ij})\\
令M\to \infty \\ 
p_ii(t)=e^{-v_i t}+o(t)\\
\therefore lim_{t \to 0}\frac {1-P_{ii}(t)}t= v_i\\
i \ne j,\\
P_{ij}(t)=P(X(t+s)=j,没有经过转移|X(s)=i)+P(X(t+s)=j,经过两次及以上的转移,首次转移\ne j|X(s)=i)\\
P_{ij}(t)\le o(t)+P_{ij}(t)(1-e^{-v_it})\\
lim_{t\to 0}P_{ij}/t=q_{ij}
$$

#### 5.34

$$
(a)\\
P(X(t)=i|X(t)\in B)\\
=\frac{P_i}{\sum_{j\in B}P_j}\\
(b)\\
P(X(t)=i|X(t)\in B,X(t^-)\in G)\\
=\frac{\sum_{j\in G}P_{j}q_{ji}}{\sum_{j\in G}\sum_{k \in B}P_{j}q_{jk}}\\
\\(c)\\
\tilde{F_i}(s)=E[e^{-sT}]E[e^{-sT'}]= \frac{v_i}{v_i+s}\sum_jE[e^{-sT'}|下一个是j]P_{ij}\\
E[e^{-sT'}|下一个是j]=\left\{\begin{matrix}
 1,if\;j\in G\\
\tilde{F_j}(s), if\;j \in B
\end{matrix}\right.
证毕\\
(d)\\
在任意时刻t，从G到B的转移次数与从B到G的转移次数之差必须不大于1，\\因此从G到B的转移发生的长程速率必须等于从B到G的转移发生的长程速率\\
(e)\\
由(c)，(s+v_i)\tilde{F_i}(s)=\sum_{j \in B}\tilde{F_j}(s)q_{ij}+\sum _{j \in G}q_{ij}\\
同乘p_i,并对i\in B求和，\\
\sum_{i\in B}P_i(s+v_i)\tilde{F_i}(s)=\sum_{i \in B}\sum_{j \in B}P_i\tilde{F_j}(s)q_{ij}+\sum_{i \in B}\sum _{j \in G}P_iq_{ij}\\
=\sum_{j\in B}\tilde{F_i}(s)\sum_{j \in B}q_{ij}+\sum_{i \in G}\sum _{j \in B}P_iq_{ij}\\
=\sum_{j\in B}\tilde{F_i}(s)[v_iP_j-\sum_{j \in G}q_{ij}]+\sum_{i \in G}\sum _{j \in B}P_iq_{ij}\\
\therefore s\sum_{j\in B}P_i\tilde{F_i}(s)=\sum_{i \in G}\sum _{j \in B}P_iq_{ij}(1-\tilde{F_i}(s))\\
(f)\\
由(b),E[e^{-sT_v}]=\frac{\sum_{i \in B}\sum_{j\in G}\tilde F_i(s)P_{j}q_{ji}}{\sum_{k \in B}\sum_{j\in G}P_{j}q_{jk}}\\
(g)\\
由f
s\sum_{j\in B}\tilde{F_i}(s)=(\sum_{i \in G}\sum _{j \in B}P_iq_{ij}(1-E[e^{-sT_v}])\\
s\to 0,同除s得\sum_{j\in B}P_j=(\sum_{i \in G}\sum _{j \in B}P_iq_{ij})E[T_v]\\
(h)\\
E[e^{-sT_x}]=\frac{\sum_{i\in B}P_i \tilde F_i(s)}{\sum _{j\in B}P_j}\\
=\frac{\sum_{i \in G}\sum _{j \in B}P_iq_{ij}(1-\tilde{F_i}(s))}{s\sum _{j\in B}P_j}\\
=\frac{\sum_{i \in G}\sum _{j \in B}P_iq_{ij}(1-E[e^{-sT_v}])}{s\sum _{j\in B}P_j}\\
=\frac{1-E[e^{-sT_v}]}{sE[T_v]}\\
(i)\\
假设P(T_x \le t )已知\\
E[e^{-sT_v}]=\int_0^\infty e^{-st}P{T_v>t}dt/E[T_v]\\
=\int _0^\infty e^{-st}\int _0^\infty dF_{T_v}(y)dtE[T_v]\\
=\int_0^\infty \int _0^ye^{-st}dtF_{T_v}(y)/E[T_v]=\frac{1-E[e^{-sT_v}]}{E[T_v]}\\
(j)\\
E[T_x]=\int_0^\infty tdF_{T_v}(y) =\int_0^\infty t\int_0^\infty  dF_{T_v}(y)dt/{E[T_v]}\\
=\int_0^\infty \int_0^y dtdF_{T_v}(y)/{E[T_v]}\\
\because E[T_v^2] \ge E[T_v]^2\\
\therefore E[T_v]=\frac{E[T_v^2]}{2E[T_v]}\ge \frac{E[T_v]}2\\
\\题目中运用到的laplace变换\\
{\widetilde {Y}}（s）=\{{\mathcal {L}}^{*}F_{Y}\}（s）=\int _{0}^{\infty }e^{-st}\lambda e^{-\lambda t}dt={\frac {\lambda }{\lambda +s}}
$$

