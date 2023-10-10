# 随机过程Chapter3作业 

#### 3.7

$$
\because X\sim U(0,1)\\
m(t)=E[N(t)]\\
=\int_0^{\infty}E[N(t)|X_1]dF(X)\\
=\int_0^{\infty}E[1+N(t-X)|X_1]dF(X)\\
=\int_0^{t}(1+E[N(t-X)])dF(X)\\
=t+\int_0^{t}m(t-s)ds=t+\int_0^{t}m(y)dy\\
两边同时取微商
m^{'}(t)=1+m(t)\\
\therefore m(t)=e^t-1
\\
\because 间隔时间加起来大于1的时刻为第N(t)+1到达\\
又\because  t \in[0,1]\\
\therefore 到达间隔时间超过1所需的的(0,1)均匀随机变量的期望数为e
$$

#### 3.8

(a)
$$
P\{X_1 \leq x_1, \dots, X_n \leq x_n, N(t) = n\} \\
= \int_{y_1 \leq x_1}\dots \int_{y_n \leq x_n} P\{X_{n+1} > t – \sum_{i=1}^n y_i\}dF(y_1)\dots dF(y_n) \\
=\int_0^1 \dots \int_0^1 I\{y_1 \leq x_1, \dots, y_n \leq x_n\} \bar{F}(t – \sum_{i=1}^n y_i)dF(y_1)\dots dF(y_n) \\ 
\because Fubini定理，积分交换的次序不会造成影响
\\但是X_{n+1}和其余的X分布不同，所以不能交换。
$$

(b)
$$
\because它们是可交换的
\\ E[\frac{X_1 + \dots + X_{N(t)}}{N(t)}|N(t) = n]\\
=E[\frac{X_1 + \dots + X_n}{n}|N(t) = n]  \\
=\frac{1}{n}\sum_{i=1}^{n} E[X_i|N(t) = n] \\
=E[X_1|N(t) = n] 
$$
(c)
$$
E[\frac{X_1 + \dots + X_{N(t)}}{N(t)}|N(t) > 0]  \\
= \sum_{n=1}^{\infty} E[\frac{X_1 + \dots + X_{N(t)}}{N(t)}|N(t) = n]P\{N(t) = n | N(t) > 0\}\\
= \sum_{n=1}^{\infty} E[X_1|N(t) = n]P\{N(t) = n | N(t) > 0\}\\ 
= E[X_1|N(t) > 0] = E[X_1|X_1 < t]
$$

#### 3.17

$$
g=h+g*F\\
=h+(h+g*F)*F\\
=h+h*F+g*F_2\\=...\\=
h+h*F+...+h*F_n+g*F_{n+1}\\
\because n \to \infty,F_n \to 0, \\
g = h+h*m
$$

(a)
$$
P(t)=\int_0^{\infty}P(在t时刻处于开状态|Z_1+Y_1=s)dF(s)\\
=\int_0^{t}P(在T时刻处于开状态|Z_1+Y_1=s)dF(s)+\int_t^{\infty}P(在T时刻处于开状态|Z_1+Y_1=s)dF(s)\\
=\int_0^{t}P(t-s)dF(s)+\int_t^{\infty}P(Z_1>t|Z_1+Y_1=s)ds\\
=\int_0^{t}P(t-s)dF(s)+P(Z_1>t)
$$
(b)
$$
g(t)=\int_0^{\infty}E[A(t)|X_t=s]dF(s)\\
=\int_0^{t}E[A(t)|X_t=s]dF(s)+\int_t^{\infty}E[A(t)|X_t=s]dF(s)
\\=\int_0^{t}g(t-s)dF(s)+\int_t^{\infty}tdF(s)
\\=\int_0^{t}g(t-s)dF(s)+t(1-F(t))
\\P(t)\to \frac{\int_0^{\infty}P(Z_t>t)dt}{\mu_F}=\frac{E[Z]}{E[Z]+E[Y]}
\\g(t) \to \frac{E[X^2]}{2\mu}
$$

#### 3.27

$$
E[R_{N(t)+1}]=E[R_{N(t)+1}|S_{N(t)}=0]\bar F(t)+\int _0^{t}E[R_{N(t)+1}|S_{N(t)}=s]\bar F(t-s)dm(s)\\
=E[R_{1}|X_1>t]\bar F(t)+\int _0^{t}E[R_{1}|X_1>t-s]\bar F(t-s)dm(s)\\
\to \int _0^{t}E[R_{1}|X_1>t]\bar F(t)\frac {dt}{\mu}\\
\because \bar F(t)=\int_t^{\infty}f(s)ds;\\=\int _0^{t}\int _t^{\infty }E[R_{1}|X_1=s]dF(s)\frac {dt}{\mu}\\
=\int _0^{\infty}\int _0^{s}E[R_{1}|X_1=s]dF(s)\frac {dt}{\mu}\\
=\int _0^{\infty }E[R_{1}|X_1=s]dF(s)\frac {s}{\mu}\\
=\frac{E[R_1X_1]}{\mu}
\\ \because \mu = E[X_1], E[X_1R_1]<\infty ,可以得出在t\to \infty 有E[R_{1}|X_1>t]\bar F(t)\to0,\\
Var(X)>0.\therefore E[X^2]>E^2[X]，除非X以概率为1地是常数
$$



#### 3.32

$$
(a)\\
P_0=1-\lambda \mu_G
\\(b)\\
E[G]=\frac{\mu_G}{P_0}=\frac{\mu_G}{1-\lambda\mu_G}\\
(c)\\
E[G]=E[N\mu_G]\\
E[N]=\frac{1}{1-\lambda\mu_G}
$$



#### 3.34

$$
P[X=1]=1,Y\sim U(2,3)
$$



#### 3.36

$$
lim\int_0^t\frac{r(X(s)ds)}{t}=\frac{E[\int_0^tr(X(s)ds])}{E[t]}\\
=\frac{\sum_{j}r(j)(t_{j})}{E[t]}\\
=\sum_j r(j)P_j
$$

