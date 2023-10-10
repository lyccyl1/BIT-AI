# 随机过程作业Chapter 2 

#### 2.6

$$
\because 求的是计算器运转的平均长度\newline 
\therefore 设N为失效的部件数\;\;
\\ N_1为1型的失效数，N_2为2型的失效数
\\N_1和N_2是独立的，\therefore E[N]=E[N_1]+E[N_2]
\\ \mu = \mu_1+\mu_2\therefore T=\frac{E[N]}{\mu}=\frac{E[N]}{\mu_1+\mu_2}
\\E[N]=\sum_{k=min(n,m)}^{n+m-1}k[\binom{k-1}{n-1} (\frac{\mu_1}{\mu_1+\mu_2})^{n}(\frac{\mu_2}{\mu_1+\mu_2})^{k-n}+\binom{k-1}{m-1}(\frac{\mu_2}{\mu_1+\mu_2})^{m}(\frac{\mu_1}{\mu_1+\mu_2})^{k-m}]\\
T=\frac{\sum_{k=min(n,m)}^{n+m-1}k[\binom{k-1}{n-1} (\frac{\mu_1}{\mu_1+\mu_2})^{n}(\frac{\mu_2}{\mu_1+\mu_2})^{k-n}+\binom{k-1}{m-1}(\frac{\mu_2}{\mu_1+\mu_2})^{m}(\frac{\mu_1}{\mu_1+\mu_2})^{k-m}]}{\mu_1+\mu_2}
$$

#### 2.8

###### (a)

$$
P(x\ge\frac{-lnU_i}{\lambda})=P(lnU_i\ge-\lambda x)=P(U_i\ge e^{-\lambda x})=1-e^{-\lambda x}\\
\therefore X_i是具有失效率\lambda 的指数分布随机变量\\
$$

###### (b)

$$
\because \prod_{i=1}^{n}U_i\ge e ^{-\lambda}>\prod_{i=1}^{n+1}U_i
\\ \therefore \sum_{i=1}^{n}X_i\le1<\sum_{i=1}^{n+1}X_i
\\X_i是均值为\lambda的Poission随机变量,N是到达时刻1位置的数件数N（1）
\\ \therefore N是均值为\lambda的Poisson随机变量
$$

#### 2.15

（a）
$$
N_i的分布是负二项分布
$$
（b）

不独立

（c）
$$
T_i是参数为n_i和P_i的gamma随机变量
$$
（d）
$$
个人认为gamma分布可以理解为n个指数分布的和，所以是独立的
$$
（e)
$$
E[T_i]=\int_0^{\infty}P\{T>t\}dt\\
=\int_0^{\infty}P\{T_i>t,i=1,2,...,r\}dt
\\=\int_0^{\infty}\prod_{i=1}^r P\{T_i>t\}dt
\\=\int_0^{\infty}\prod_{i=1}^r \int _t^{\infty}\frac{P_ie^{P_ix}(P_ix)^{n_i-1}}{(n_i-1)!}dt
$$
(f)
$$
T=\sum X_i,因为采取的是\lambda= 1的Poisson分布，所以E[X_i]=1,\\
E[T]=E[E[T|N]]=E[NE[X_i]]=E[N]
$$

#### 2.17

###### (a)

$$
f_{X_{(i)}}(x) &= {n \choose i} (F(x))^{i-1}(\bar{F}(x))^{n-i} {i \choose 1}f(x) \\
&= \frac{n!}{(i-1)!(n-i)!}(F(x))^{i-1}(\bar{F}(x))^{n-i}f(x)\\
$$

###### (b)

$$
当且仅当有大于等于i个小于x
$$

###### (c)

$$
P\{X_{(i)}\le x \}= \sum_{k=i}^n {n \choose k}(F(x))^k(\bar{F}(x))^{n-k}
$$

###### (d)

$$
\because P\{X_{(i)}\le x \}=\sum_{k=i}^n{n \choose k}(F(x))^k(\bar{F}(x))^{n-k} \\
=  \int_0^{F(x)}\frac{n!}{(i-1)!(n-i)!}(F(t))^{i-1}(\bar{F}(t))^{n-i}dF(t)
$$



###### (e)

$$
when\ i> n, \because 无记忆性\\
\therefore \ E[S_i|N(t)=n]=t+\frac{(i-n)}{\lambda}\\
when \;i\le n,\\
从定理2.3.1我们知道(S_1, \dots, S_n | N(t) = n)与U_{(1)}, \dots, U_{(n)}有相同分布\\
E[S_i|N(t)=n]=E[U_{(i)}]\\
= \int_0^t x \frac{n!}{(i-1)!(n-i)!}(\frac{x}{t})^{i-1}(1 – \frac{x}{t})^{n-i}\frac{1}{t} dx \\
= \frac{it}{n + 1} \int_0^t \frac{(n+1)!}{i!(n-i)!}(\frac{x}{t})^i(1 – \frac{x}{t})^{n-i} d \frac{x}{t} \\
= \frac{it}{n + 1} \sum_{k=i}^n{n \choose k} (\frac{k}{t})^k(1 – \frac{k}{t})^{n-k}\\
= \frac{it}{n + 1}
$$

#### 2.24

$$
设t时刻进入的车的速度为L/v,则以t_v=L/v记录该时间，以G记录时间分布，设T=L/X为速度是X时的时间，\\可得
G(x)=(1-F(L/x)),在有t时刻的车辆的前提下，\\令一辆车s驶入道路，若其与t相遇，则计数，若s>t，则以概率\\
P\{s+T<t+t_v\}被计数为一个事件，同样的，当s<t,则以概率P\{s+T>t+t_v\}被计数。
\\即s事件和其他事件独立的以概率p(s)计数，\\
p(s)=G(t+t_v-s),when\ s<t,\\
p(s)=1-G(t+t_v-s),when \ t<s<t+t_v,\\
p(s)=0,else 
\\N(t)=\lambda E[t]=\lambda \int _0^{\infty}p(s)ds=\lambda(\int_0^{t}G(t+t_v-s)ds)+\lambda(\int_t^{t+t_v}(1-G(t+t_v-s)ds)
\\\frac{d}{dt}(\lambda\int_0^{\infty}p(s)ds)=\lambda[G(t_v)-G(t+t_v)-(1-G(t_v))+1]
\\令微分等于0，\because t->\infty ,G(t+t_v)->1，\\
\therefore G(t_v)=1-G(t_v)，\therefore G(t_v)=\frac{1}2,\\
\therefore 最优解是时间的中位数
$$

#### 2.32

###### (a)

$$
与定理2.3.1类似证明方式\\
P\{t_i < S_i < t_i + h_i, i = 1, \dots, n|N(t) = n\} \\
=\frac{n!\prod[m(t_i + h_i) – m(t_i)]}{e^{-m(t)[m(t)]^n/n!}}\\
令h_i->0，f_{s_1\dots s_n}(t_1,\dots,t_n|N(t) = n) = n!\prod[\lambda(t_i)/m(t)]9

$$


$$

$$

###### （b)

$$
在时间t失业概率为p\\
p = \int_0^t \bar{F}(t-s)d\frac{m(s)}{m(t)} = \int_0^t \bar{F}(t-s)\frac{\lambda(s)}{m(t)}ds
\\\begin{align}
E[X(t)] &= E[E[X(t)|N(t)]] \\
&= m(t)\int_0^t \bar{F}(t-s)\frac{\lambda(s)}{m(t)}ds  \\
&= \int_0^t \bar{F}(t-s)\lambda(s)ds \\
Var(X(t)) &= E[Var(X(t)|N(t))] + Var(E[X(t)|N(t)]) \\
&= m(t)p(1-p) + p^2Var(N(t)) \\
&= \int_0^t \bar{F}(t-s)\lambda(s)ds 
\end{align}
$$



####  2.41

###### (a)

$$
事件数会改变\wedge 的分布，所以没有独立增量的分布
$$

###### (b)

$$
P(\wedge = \lambda,N(s),o\le s \le t)=P(\wedge =\lambda,N(t)=n,S_1=s_1,...,S_n=s_n)\\
=P(\wedge =\lambda)P(N(t)=n|\wedge =\lambda)P(S_1=s_1,...,S_n=s_n|\wedge =\lambda)
\\=dG(\lambda )e^{-\lambda}\frac{(\lambda t)^n}{n!} \frac{n!}{t^n}由定理2.3.1\\
由全概率公式，可得P(N(t)=n,S_1=s_1,...,S_n=s_n)=\int_0^\infty  dG(\lambda )e^{-\lambda}\frac{(\lambda t)^n}
{n!}\frac{n!}{t^n}\\
\therefore P(\wedge = \lambda|N(s),o\le s \le t)=\frac{dG(\lambda )e^{-\lambda}(\lambda t)^n}{\int_0^\infty  dG(\lambda )e^{-\lambda}(\lambda t)^n}\\
无论取什么值\lambda，\wedge的条件分布只依赖于N(t),在给定N(t),S_1,...,S_n和(0,t)上的均匀分布的次序统计量同分布
$$

###### (c)

$$
设在t+s时刻发生下一事件，\\
P(发生首个事件为T>t+s|N(t)=n)\\=\frac{P([t,t+s]发生0个事件，N(t)=n)}{P(N(t)=n)}\\=
\frac{\int_0^\infty(e^{-\lambda s}e^{-\lambda t }\frac{(\lambda t)^n}{n!} dG(\lambda))}{\int_0^\infty(e^{-\lambda t }\frac{(\lambda t)^n}{n!} dG(\lambda))}
$$

###### (d)

$$
\lim_{h \to 0}\frac{P(N(h)\ge1)}{h} =\lim_{h \to 0}\frac{1-P(N(h)=0)}{h} \\ =
\lim_{h\to 0}\frac{\int_0^\infty (1-e^{-\lambda h })dG(\lambda)}{h}\because 泰勒展开\\
=\int_0^{\infty}\lambda dG(\lambda)
$$

###### (e)

不独立，同分布
