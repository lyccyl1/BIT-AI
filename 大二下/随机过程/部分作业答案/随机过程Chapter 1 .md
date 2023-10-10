# 随机过程Chapter 1 作业



#### Problem 1.5：假设做了n次独立试验，每次结果分别以概率p1,p2,...,pr出现1,2,...,r之一，其中

$$
({\textstyle \sum_{r}^{1}pi=1})
$$

#### ，以Ni记出现结果i的试验次数

###### (a):计算N1,...,Nr的联合分布，它称为多项分布

$$
假设全部有N=n个事件，由于每个事件独立地有pj(j=1,2,...,r)为类型j，由此可以推出，N1，N2,...,Nr的具有以p1,p2,...,pr\newline为参数的多项分布
$$

$$
则P(Nj=n_j,j=1,...,r)=P(Nj=nj,j=1,...,r|N=n)P(N=n)
$$

$$
可得到P(Nj=n_j,j=1,...,r)=\frac{n!}{1!2!...r!} p_{1} ^{1}p_{2}^{2}...p_{r}^{r}P(N=n)
$$

$$
由P(N=n)是条件已知，所以P(Nj=nj,j=1,...,r)=\frac{n!}{n_1!n_2!...n_r!} p_{1} ^{1}p_{2}^{2}...p_{r}^{r}
$$

(b):计算Cov(Ni,Nj)
$$
Cov(N_i,N_j)=E[N_iN_j]-E[N_i]E[N_j]\newline
N_iN_j=1(N_i和N_j同时发生)\newline
N_iN_j=0(其他情况)\newline
E[N_iN_j]=E[N_i=n_i|N_j=n_j]E[N_j]=n^2p_ip_j-np_ip_j\newline
E[N_i]=np_i,E[N_j]=np_j\newline 
Cov(N_i,N_j)=-np_ip_j
$$
(c):计算未出现的结果数的均值和方差

对于没有出现的结果数
$$
I_i=1(i没出现)I_i=0(i出现)\newline 
E[I_i]=(1-p_i)^n\newline
Var[I_j]=(1-p_i)^n(1-(1-p_i)^n)\newline
E[I_iI_j]=(1-p_i-p_j)^n\newline
设不出现的结果数N'=\sum I_i,E[N']=\sum_{i=1}^r(1-p_i)^n
\newline Var[N']=\sum_{i=1}^{r}Var[I_i]+\sum\sum_{i\ne j}Cov(I_i,I_i)
\newline=\sum_{i=1}^r(1-p_i)^n(1-(1-p_i)^n)+\sum\sum_{i\ne j}[(1-p_i-p_j)^n-(1-p_i)^n(1-p_j)^n]
$$

#### Problem 1.6 令X1,X2,...是独立同分布的随机变量。若Xn>max(X1,...,Xn-1),X0=-∞,则我们说在时刻n为止（包含n）已产生了一个记录，并有记录值Xn

(a)以Nn为记到n为止以产生的记录个数，计算E[Nn]和Var(Nn)
$$
令max(X_1,...,X_{n-1})=F^{n-1}(X),\newline
令I_{n}=1(X_n被记录),I_n=0(X_n没有被记录)\newline
P(I_n=1)=\int_{-∞}^{+∞} P(I_n=1|x_n=u)dF(u)\newline
=\int_{-∞}^{+∞} F^{n-1}(u)dF(u)\newline
=\int_{0}^{1}x^{n-1}dx,\because(F(u)\in [0,1])\newline
=\frac{1}{n}\newline
thus\quad I_n\sim B(1,n)\newline
thus\quad E[N_n]=\sum_{i=1}^n\frac{1}{i}\newline 
Var[N_n]=E[{N_n}^2]-E^2[N_n]=\sum_{i=1}^{n}\frac{i-1}{i^2}
$$
(b)令T=min{n:n>1且在n有一个记录}，计算P{T>n}并证明P{T<∞}=1且E[T]=∞
$$
(a)中P(T=n)=P(X_n>max(X_1,...,X_{n-1})|X_1=max(X_1,...,X_{n-1}))P(X_1=max(X_1,...,X_{n-1}))\newline
=\frac{1}{1}\times\frac{1}{2}\times\frac{2}{3}\times...\times\frac{n-2}{n-1}\times\frac{1}{n} =\frac{1}{n(n-1)}\newline
P(T>n)=\sum_{i=n+1}^{+\infty}\frac{1}{n(n-1)}=\frac{1}n
\newline\lim_{n \to \infty}P(T>n)=0\newline
P(T<\infty)=1\newline
T发生满足：只有X_1and X_n被记录\newline 
E[T]=\sum_{i=1}^{\infty}\frac{1}{n(n-1)}\times{n}=\infty
$$
(c)记XTy是Ty时刻的值
$$
P(X_{T_y}>x|T_y=n)=P(X_n>x|X_1<y,...,X_{n-1}<y,X_n>y)\newline
=P(X_{n}>x|X_n>y)\newline
=1(x<y)\newline
=\frac{(1-F(x))}{(1-F(y))}(x>y)\newline
与n无关所以独立
$$

#### 1.11

(a)证明
$$
\frac{d^k}{dz^k}P(z)|_{z=0}=k!P(X=k)
\newline证：\frac{d^k}{dz^k}P(z)|_{z=0}=k!P(X=k)+\sum_{i=k+1}^{\infty}z^{i-k}P(X=i)
\newline\because{z=0}
\newline\frac{d^k}{dz^k}P(z)|_{z=0}=k!P(X=k)
$$
(b)
$$
P(1)+P(-1)=(\sum_{i=1}^{\infty}2P(X=2i))+(\sum_{i=1}^{\infty}(P(X=2i+1)-P(X=2i+1)))=P(X是偶数)
$$
(c)若X是以n和p为参数的二项随机变量
$$
P(1)=\sum^{n}_{i=0}1^i\binom{n}{i}p^i(1-p^i)=1
\newline P(-1)=\sum^{n}_{i=0}\binom{n}{i}{(-p})^i(1-p^i)=(1-2p)^i
\newline 由(b)P(1)+P(-1)=P(X是偶数)=\frac{1+(1-2p)^i}{2}
$$
(d)
$$
若X以参数为分布的\lambda的Poisson分布\newline
P(1)=P(1)=\sum^{n}_{i=0}1^i\frac{\lambda^ie^{-\lambda}}{i!}=1
\newline P(-1)=e^{-2\lambda}\sum^{n}_{i=0}\frac{{(-\lambda)}^ie^{\lambda}}{i!}=e^{-2\lambda}
\newline 由(b)P(1)+P(-1)=P(X是偶数)=\frac{1+e^{-2\lambda}}{2}
$$
(e)
$$
若X是以p为参数的几何随机变量
\newline P(1)=1
\newline P(-1)=\sum_{i=1}^{\infty}(1-p)^{i-1}p=-\frac{p}{p-2}\sum_{i=1}^{\infty}(1-p)^{i-1}(2-p)=-\frac{p}{p-2}\newline
由(b)P(1)+P(-1)=P(X是偶数)=\frac{1-p}{2-p}
$$
(f)
$$
若X是以r和p为参数的负二项随机变量
\newline P(1)=1
\newline P(-1)=\sum_{k=r}^{\infty}\binom{k-1}{k-r}(-1)^kp^r(1-p)^{k-r}\newline
={(-1)^r(\frac{p}{2-p})^r}\sum_{k=r}^{\infty}\binom{k-1}{k-r}(p-1)^{k-r}(2-p)^r=(-1)^r(\frac{p}{2-p})^r\newline P(1)+P(-1)=P(X是偶数)=\frac1{2}(1+(-1)^r(\frac{p}{2-p})^r)
$$

#### 1.17

(a)
$$
F_{i,n}(x)=P(第i个最小值<=x|X_n<=x)F(x)+P(第i个最小值<=x|X_n>x)(1-F(x))\newline
=F_{i-1,n-1}(x)F(x)+F_{i,n-1}(x)(1-F(x))
$$
(b)
$$
F_{i,n}(x)=P(X_{i,n-1}<=x|X_n在第i个最小者中)F(x)+P(X_{i,n-1}<=x|X_n不在第i个最小者中)(1-F(x))\newline
=\frac{i}{n}F_{i+1,n}(x)+\frac{n-i}{n}F_{i,n}(x)
$$

#### 1.20

$$
将[0,x-1]分为y,x-y-1\quad two\;parts
\newline when\quad x<1,
\newline \because Y\sim U(0,x-1)
\therefore y=0,无法装入一个区间,\therefore M(x)=0
\newline when \;x>1,
\newline E[N(x)]=E[E[N(x)|Y]]=E[N(y)]+E[N(x-y-1)]+1
\newline=\int_{0}^{x-1} \frac1{x-1}(M(y)+M(x-y-1)+1)dy
\newline =\frac2{x-1}\int_{0}^{x-1}M(y)dy+1
$$

#### 1.22

$$
\because Var(X|Y)=E[(X-E[X|Y])^2|Y]
\newline \therefore E[Var(X|Y)]+Var(E[X|Y])=E[E[(X-E[X|Y])^2|Y]]+Var(E[X|Y])
\newline =E[(X-E(X|Y))^2]+Var(E[X|Y])
\newline =E[X^2-2XE(X|Y)+E(X|Y)^2]+Var(E[X|Y])
\newline = E[X^2]-E[E^2[X|Y]]+E[E^2[X|Y]]-(E[E[X|Y]])^2
\newline =E[X^2]-E^2[X]
\newline =Var(X)得证
$$

#### 1.29

$$
使用数学归纳法\newline
when \;n=1,\newline 
f(t)=\frac{\lambda e^{-\lambda t}(\lambda t)^{n-1}}{(n-1)!}
\newline f(t)=\lambda e^{-\lambda t}
\newline let \;n=k \;Conclusion
\newline when\; n=k+1,
\newline f_{k+1}(t)=\int_{0}^{t}f_1(t-x)f_k(x)dx 
\newline =\int_{0}^{t}\frac{\lambda e^{-\lambda x}(\lambda x)^{k-1}}{(k-1)!}\lambda e^{-\lambda (t-x)}dx
\newline =\frac{\lambda e^{-\lambda t}(\lambda t)^{k}}{(k)!}
$$

#### 1.34

$$
P(X_1<X_2|min(X_1,X_2)=t)=\frac {P(X_1<X_2,min(X_1,X_2)=t)}{P(min(X_1,X_2)=t)}\newline
=\frac{P(X_1=t,X_2>t)}{P(X_2=t,X_1>t)+P(X_1=t,X_2>t)}\because P(X=t)=\lambda P(X>t)\newline
=\frac{\lambda_1P(X_1>t)P(X_2>t)}{\lambda_1P(X_1>t)P(X_2>t)+\lambda_2P(X_1>t)P(X_2>t)}\newline 
=\frac{\lambda_1}{\lambda_1+\lambda_2}
$$

#### 1.35

(a)
$$
M(t)E[e^{-tX_t}h(X_t)]=M(t)\int_{-\infty}^\infty e^{-tx}h(x)f(x)dx
\newline =\int_{-\infty}^\infty h(x)f(x)dx
\newline =E[h(x)]
$$
(b)
$$
M(t)e^{-ta}P(X_t>a)=\int_a^\infty e^{t(x-a)}f(x)dx\;\because x\ge a
\newline \therefore \int_a^\infty e^{t(x-a)}f(x)dx\ge \int_a^\infty f(x)dx=P(X>a)
$$
(c)
$$
let\; f(x,t)M(t)e^{-ta}=e^{-ta}\int_{-\infty}^{\infty}e^{tx}f(x)dx\newline 
f_t'(x,t)=e^{-ta}\int_{-\infty}^{\infty}(xe^{tx}f(x)-ae^{tx}f(x))dx
\newline =e^{-ta}\int_{-\infty}^{\infty}(xe^{tx}f(x)dx-aM(t))
\newline let \;\;f_t'(x,t)=0,E[X_t]=a
\newline \therefore minM(t)e^{-ta}=M(t^*)e^{-t^*a}
$$


#### 1.37

$$
有一个简单的思想:对于任意三个数X_{i-1},X_i,X_{i+1},因为独立同分布三者都等可能的为最大者，设I_n=1(在n出现峰值),I_n=0(n没有出现峰值)，\newline
\therefore E[I_n]=\frac{1}3\;由大数定理，每个序列的前n项的平均以概率为1地收敛到\frac{1}{3},\newline
这蕴含了以概率为1地\lim_{n \to \infty}\sum_{i=1}^{n}\frac {I_{n+1}}{n}=\frac{1}{3}
$$

#### 1.39

$$
由题意显然E[T_1]=1
\newline 对于T_2\;E[T_2]=\frac{1}2+\frac{1}2(E[T_1]+E[T_2])
\newline E[T_2]=2+E[T_1]
\newline \therefore E[T_{n+1}]=2+E[T_n]
\newline E[T_n]=2n-1
\newline \sum_{i=1}^{n}E[T_n]=n^2
\newline \therefore从0开始到n,需要n^2步
$$



