# 随机过程Chapter 4 

#### 4.13

$$
同一状态类中所有状态共有的性质称为类性质\\
I_n=\left\{\begin{matrix}
 1\;\;X_n=i\\
0\;\;X_n\ne i
\end{matrix}\right.
\\ \sum_{n=0}^{\infty}I_n为过程装处在i状态的时间周期个数
\\\because E(\sum _{n=0}^\infty I_n|X_0=i)=\sum _{n=0}^\infty E(I_n|X_0=i)=\sum_{n=0}^\infty P\{X_n=i|X_0=i\}=\sum_0^\infty P_{i,i}^n\\
\sum_{n=0}^\infty P_{i,i}^n=\left\{\begin{matrix}
 \infty \;\;recurrent \\
<\infty \;\;tranient
\end{matrix}\right.
\\下面证明状态i是常返态且i\leftrightarrow j,j为常返态\\
证：\because i\leftrightarrow j,\exist m,n \in Z^*，P^m_{j,x}>0,P^n_{x,j}>0
\\ \exist i \in Z^*,\\
\sum _{n=0}^\infty P_{j,j}^{i+m+n} \ge \sum _{n=0}^\infty P_{j,x}^mP_{x,x}^iP_{x,j}^n\\
I_k=\left\{\begin{matrix}
 1\;\;X_{N_k+m}=j\\
0\;\;X_{N_k+m}\ne i
\end{matrix}\right.\\
由强大数定律，\\
\sum _{k=1}^n \frac{I_k}{n}->P^m_{i,j}>0\\
lim_{k->\infty}\frac{直至N_k+m访问j的次数}{n}\frac{n}{N_k+m} \ge P^m_{ij}\frac{1}{E[T_{ii}]}>0
$$

#### 4.16

$$
(a)\\
P_{0,r}=1,\;P_{i,r-i}=1-p,P_{i,r-i+1}=p\\
(b)
\\ \pi_0=\pi_r (1-p)\\
\pi _i=\pi_{r-i}(1-p)+\pi_{r-i+1}p , i = 1 ,... ,r-1\\
\pi_r= \pi_0+\pi_{1}p\\
\therefore \pi_0=\frac{1-p}{r+1-p}\\
\pi_i=\frac{1}{r+1-p}\\
(c)
\\
t = p\pi_0=\frac{p(1-p)}{r+1-p}
$$

#### 4.21

$$
对于Markov链正常返当且仅当，方程组\\
y_0=y_1 q_1, y_i=y_{i+1}q_{i+1}+y_{i-1}p_{i-1},i\ge 1\\
具有满足y_i\ge0,\sum_jy_i=1的一个解 \\
\therefore y_0=y_1q_1,y_{j+1}q_{q+1}-y_ip_i=y_iq_i-y_{i-1}p_{i-1},i\ge 1\\
y_{j+1}q_{q+1}=y_ip_i\\
y_{i+1}=y_0 \frac {p_0...p_i}{q_1...q_{i+1}},i\ge 0\\
\therefore 随机徘徊分布是正常返的充要条件是
\\ \sum_{i=0}^\infty  \frac {p_0...p_i}{q_1...q_{i+1}}<\infty
$$

#### 4.30

$$
\because P(X_i-Y_i=1)P_1(1-P_2),P(X_i-Y_i=-1)P_2(1-P_1)\\
看作一个随机徘徊过程，P=\frac{P_1(1-P_2)}{P_1(1-P_2)+P_2(1-P_1)}为概率\\
P(误差)=P(在赢到M前输M)因为是简单的随即徘徊过程，所以结合提示中的赌徒破产问题求解\\
我们先考虑这么一个基本的赌徒破产基础过程\\
f(n)=pf(n+1)+qf(n-1)\\
我们把一般来说的在具有初始本金n，赢到N这么理解\\
定义一下初始状态\\f(0)=0\\
f(N)=1\\
p=1-P，
q=P
可由类似4.21的推导 \because p+q=1\\
pf(n)+qf(n)=pf(n+1)+qf(n-1)\\
pf(n+1)-pf(n)=qf(n)-qf(n-1)\\
f(n+1)-f(n)=\frac{q}{p}(f(n)-f(n-1))\\
\therefore f(n)=\frac{1-(\frac{q}{p})^n}{1-\frac{q}{p}}f(1)\\
也可以这么求解\\
f(n+1)-\frac{1}{p}f(n)+\frac{q}{p}f(n-1)=0\\
利用特征根求解递推方程\\
x^2-\frac{1}{p}x+\frac{q}{p}=0\\
它有两个特征根1和r=q/p, 一般情况下，这两个根不同的话，它的通解就是这两个特征根的连续幂的组合\\
因此P(N|n)=f(n)=a(1)^n+b(r)^n\\
由已知的初始状态可得：\\
f(0)=a+b=0\;f(N)=a+b(r)^N=1\\
f(n)=\frac{1-r^n}{1-r^{N}}\\
\therefore P(误差)=\frac{1-r^M}{1-r^{2M}}\\
=\frac{1}{1+\lambda^M}\\
由wald方程\;E[\sum_{i=1}^N(X_i-Y_i)]=E[N](P_1-P_2)\\代入上述计算结果\\
\\因为P_1\ge P_2\\
E[N](P_1-P_2)=M(1\times(有效率)+(-1)\times(失效率))=M(\frac{\lambda^M}{1+\lambda^M}-\frac1{1+\lambda^M})=\frac{M(\lambda^M-1)}{1+\lambda^M}\\
E[N]=\frac{M(\lambda^M-1)}{(P_1-P_2)(1+\lambda^M)}
$$



#### 4.43

$$
根据时间可逆性，对一切排列P_{i_{j+1}} \pi(i_1,...,i_j,i_{j+1},...,i_n)=P_{i_{j}} \pi(i_1,...,i_{j+1},i_{j},...,i_n)\\
考虑任意一个利用每次前移一格的移动过程\\
P_j^k\pi(...,i,i_1,...,i_k,j,...)=P_i^k\pi(...,j,i_1,...,i_k,i,...)\\
\because P_j>P_i\\
\pi(...,i,i_1,...,i_k,j,...)<\frac{P_i}{P_j}\pi(...,j,i_1,...,i_k,i,...)\\
对上述式子求和\\
P(e_i在e_j前)<\frac{P_i}{P_j}P(e_j在e_i前)\\
P(e_i在e_j前)=1-P(e_j在e_i前)\\
P(e_j在e_i前)>\frac{P_j}{P_i+P_j}\\
书上的补充？\\
平均位置=\sum_i P_iE[元素i的位置]\\
=\sum_iP_i[1+\sum_{i \ne j}P\{元素j在i前\}]\\
=1+\sum_i\sum _{i\ne j}P_iP\{e_j在e_i前\}\\
=1+\sum _{i<j}(P_iP\{e_j在e_i前\}+P_jP\{e_i在e_j前\})\\
=1+\sum _{i<j}(P_iP\{e_j在e_i前\}+P_j(1-P\{e_j在e_i前\}))\\
=1+\sum _{i<j}(P_i-P_j)P\{e_j在e_i前\}+\sum\sum_{i<j}P_j\\
$$

