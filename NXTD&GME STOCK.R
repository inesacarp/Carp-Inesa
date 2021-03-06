getwd()
setwd("C:/Users/user/Desktop/micromanag")
dir()
analiza1<-read.table("analiza1.txt", header=TRUE, sep="\t")
attach(analiza1)
class (analiza1)

#Transformarea seriei de preturi in rentabilitati
n<-length(analiza1$Date)
rent_gme=(analiza1$Pret_GME[2:n]/Pret_GME[1:(n-1)])-1
View(as.matrix(rent_gme))
rent_nxtd=(analiza1$Pret_NXTD[2:n]/Pret_NXTD[1:(n-1)])-1
View(as.matrix(rent_nxtd))
rent_indice=(analiza1$Pret_SP500[2:n]/Pret_SP500[1:(n-1)])-1
View(as.matrix(rent_indice))
rentabilitati<-data.frame(rent_gme,rent_nxtd, rent_indice)
View(as.matrix(rentabilitati))

# d)calculam rentabilitatea medie a activelor si a indicelui de piata
summary(rentabilitati)
#observam actiunea cu cea mai mare rentabilitate este game stop, urmata de nxtd si ambele sunt mai rentabile decat indicele
ER_GS<-mean(rentabilitati$rent_gme)
ER_NXTD<-mean(rentabilitati$rent_nxtd)
ER_IND<-mean(rentabilitati$rent_indice)
#calculam riscul actiunilor exprimate prin abaterea standard
risc_gme<-sd(rentabilitati$rent_gme)#0.17
risc_nxtd<-sd(rentabilitati$rent_nxtd)#0.12
risc_indice<-sd(rentabilitati$rent_indice)#0.011
#obs ca dintre cele 2 actiuni gme e cea mai riscanta, ambele sunt mai riscante decat indicele de piata
#(portofoliul de piata)

#calculam rata sharpe ca raport intre rentabilitate asteptata si risc
rata_sharpe_gme=ER_GS/risc_gme #0.14
rata_sharpe_nxtd=ER_NXTD/risc_nxtd #0.076
rata_sharpe_indice=ER_IND/risc_indice #0.13
#rata sharpe cea mai mare este GME, deci avem un castig asteptat mai mare
#asezam rentabilitatile, riscul si rata sharpe in acelasi tabel
#nxtd are un risc mare dar aduce si un castig mare, o pastreaza persoanele care au aversiune la risc
tabel=matrix(nrow=3, ncol=3)
tabel[1,]<-c(ER_GS, ER_NXTD, ER_IND)
tabel[2,]<-c(risc_gme, risc_nxtd, risc_indice)
tabel[3,]<-c(rata_sharpe_gme, rata_sharpe_nxtd, rata_sharpe_indice)
dimnames(tabel)=list(c("ER", "Risc", "Rata_Sharpe"),c("GME", "NXTD", "S&P"))
#analizam corelatia
cor(rentabilitati)
#avem o corelatie pozitiva si slaba intre game stop si nxtd
#avem o corelatie slaba si negativa intre game-stop si indice
#determinam coef de volatilitate aplicand modelul unifactorila (model de regresie
# liniara y-x, unde y= rent activului, x= rentabilitatea indicelui)
library(ggplot2)
#volatilitatea actiunii gamestop
model_game<-lm(rentabilitati$rent_gme~rentabilitati$rent_indice)
summary(model_game)
#coef de volatilitate game-stop este -0.5706 adica este unul subunitar, si rentabilitatea
#actiunii game stop este in contradictie cu piata, atunci cand indicele scade, indicele actiunii creste
windows()
ggplot(rentabilitati, mapping = aes(x=rentabilitati$rent_indice, y=rentabilitati$rent_gme))+
  geom_point(color="red", size=2.5)+
  theme_dark()+
  ggtitle("modelul unifactorial -Game-Stop si S&P, 2020")+
  geom_smooth(mapping = aes(group=1), method = "lm", formula= y~x, se=FALSE, col="green")
#R^2 are o valoare foarte mica

#volatilitatea actiunii nxtd
model_nxtd<-lm(rentabilitati$rent_nxtd~rentabilitati$rent_indice)
summary(model_nxtd)
#volatilitatea este 2.287325 >1 => nxtd are o agresivitate ridicata dar coef estimat prin regresie este
#nesemnificativ si R^2 este mic
windows()
ggplot(rentabilitati, mapping = aes(x=rentabilitati$rent_indice, y=rentabilitati$rent_nxtd))+
  geom_point(color="red", size=2.5)+
  theme_dark()+
  ggtitle("modelul unifactorial -NXTD si S&P, 2020")+
  geom_smooth(mapping = aes(group=1), method = "lm", formula= y~x, se=FALSE, col="green")

#aplicam modelul sharpe pentru cele 2 actiuni, adica vom diversifica actiunile
#prin adaugarea activului fara risc
#conform curs pag 3 se scade din cele 2 serii de rentabilitati, rent activului fara risc
#obs rf se poate lua ca obs zilnice (in SUA luam 10 year bond) sau se poate lua rf ca o rent medie pe anul respectiv
#in cazul nostru vom lua obligatiune pe 3 ani cu rf=0.15%=0.0015
rf=0.0015
rentabilitate_exces_GME<-rentabilitati$rent_gme-rf
rentabilitate_exces_NXTD<-rentabilitati$rent_nxtd-rf
prima_de_risc_piata<-rentabilitati$rent_indice-rf
#obs ca prima de risc a pietei arata cat se castiga sau se pierde daca s a ales investitia
#la bursa in defavoarea achzitiei obligatiunilor
mean(prima_de_risc_piata)
rentabilitati<-data.frame(rentabilitati, rentabilitate_exces_GME, rentabilitate_exces_NXTD, prima_de_risc_piata)
#aplicam modelul sharpe pentru gme
model_sharpe_GME<-lm(rentabilitate_exces_GME~prima_de_risc_piata)
summary(model_sharpe_GME)
#volatilitatea ramane la fel deoarece am folosit rf ca o medie
#daca dorim ca volatilitatea sa difere ne trebuie o serie de timp

#PORTOFOLIU
#ne construim un portofoliu format din cele 2 actiuni in proportile alese 
#de noi si ne determinam rentabilitatea

x_GME<-0.6
x_NXTD<-0.4
#calculam rentabilitatea asteptata 
ER_portofoliu<-x_GME*ER_GS+x_NXTD*ER_NXTD
#rentabilitate de 18.9%
#calculam riscul portofoliului calculand prima data dispersia

var_portofoliu<-(x_GME^2)*var(rentabilitati$rent_gme)+(x_NXTD^2)*var(rentabilitati$rent_nxtd)+
  2*x_GME*x_NXTD*cov(rentabilitati$rent_gme,rentabilitati$rent_nxtd)
sd_portofoliu<-sqrt(var_portofoliu)

                 
   #Riscul portofoliului este  116.3% 
#putem adauga o coloana pentru portofoliul si comparand rentabilitatea portofcu rentabilitatile

#comparam diverse combinatii de actiuni (diverse portofolii)si ne alegem portofoliul care ne place mai mult
#comentam aversiunea si inclinatia la risc in functie de optiunea decidentului pt un portofoliu cu aversiune -portof cu risc mic;
#respectiv un portofoliu cu cel mai mare castig posibil, in caz de inclinatie




#write.table(rentabilitati, file="rentabilitati.xls", sep="\t", col.names = TRUE, row.names=FALSE)



# Interpretarea datelor ---------------------------------------------------

#GME

summary(analiza1$Pret_GME)
#Observam ca pretul minim inregistrat de compania GME a fost de 3.85 $ in data de 18.11.2020 iar pretul maxim fiind de 347.51 $.
#media este de 44.96.
summary(analiza1$Volum.GME)
#min=1330100; max=197157900 media=17040667

#NXTD
summary(analiza1$Pret_NXTD)
#min=0.314 max=3.420 media=0.787
summary(analiza1$Volum_NXTD)
#min=136800 max=399819300 medie=11130670


#INDICE DE PIATA
summary(analiza1$Pret_SP500)
#min=2820 max=4185 mean=3506
summary(analiza1$Volum_SP500)
#min=1885090000  max=9878040000


#rentabilitati
summary(rentabilitati$rent_gme)
#GME:min=-0.6 max=1.348 mean=0.025
summary(rentabilitati$rent_nxtd)
#NXTD: min=-0.292 max=0.893 mean=0.0095
summary(rentabilitati$rent_indice)
#INDICE: min=-0.058 max=0.031 mean=0.001559

#Abaterea standard
sd_pret_GME<-sd(analiza1$Pret_GME) 
#70.40
sd_pret_NXTD<-sd(analiza1$Pret_NXTD)
#0.553
sd_pretIndice<-sd(analiza1$Pret_SP500)
#349.99
sd_rentGME<-sd(rentabilitati$rent_gme)
#0.173
sd_rentNXTD<-sd(rentabilitati$rent_nxtd)
#0.125
sd_rentSP<-sd(rentabilitati$rent_indice)
#0.011
#Coeficientul de variatie
cv_GME<-sd_pret_GME/mean(analiza1$Pret_GME) 
#1.565
cv_NXTD<-sd_pret_NXTD/mean(analiza1$Pret_NXTD) 
#0.70
cv_sp<-sd_pretIndice/mean(analiza1$Pret_SP500)
#0.099
cv_rentGME<-sd_rentGME/mean(rentabilitati$rent_gme)
#6.88
cv_rentNXTD<-sd_rentNXTD/mean(rentabilitati$rent_nxtd)
#13.09
cv_rentSP<-sd_rentSP/mean(rentabilitati$rent_indice)
#7.33

#Coeficientul de asimetrie si aplatizare
library(moments)
sk_NXTD<-skewness(analiza1$Pret_NXTD) 
#1.32>1 
sk_GME<-skewness(analiza1$Pret_GME)
#1.92>1
sk_SP<-skewness(analiza1$Pret_SP500)
#-0.02
sk_rentGME<-skewness(rentabilitati$rent_gme)
#3.38
sk_rentNXTD<-skewness(rentabilitati$rent_nxtd)
#2.84
sk_rentIndice<-skewness(rentabilitati$rent_indice)
#-0.99

k_pret_GME<-kurtosis(analiza1$Pret_GME) 
#5.83>3 distributie ascutita
k_pret_NXTD<-kurtosis(analiza1$Pret_NXTD)
#4.51>3 distributie ascutita
k_pret_SP<-kurtosis(analiza1$Pret_SP500)
#2.06<3 distributia este platicurtica 
k_rentGME<-kurtosis(rentabilitati$rent_gme)
#24.48
k_rentNXTD<-kurtosis(rentabilitati$rent_nxtd)
#17.67
k_rentINDICE<-kurtosis(rentabilitati$rent_indice)
#6.2
#VOLUME
sd_volum_GME<-sd(analiza1$Volum_GME) 
#2864451
sd_volum_NXTD<-sd(analiza1$Volum_NXTD)
#35211636
sd_volumIndice<-sd(analiza1$Volum_SP500)
#1079608765

#Coeficientul de variatie
cv_VGME<-sd_pret_GME/mean(analiza1$Volum_GME) 
#4.13
cv_VNXTD<-sd_pret_NXTD/mean(analiza1$Volum_NXTD) 
#4.96
cv_Vsp<-sd_pretIndice/mean(analiza1$Volum_SP500)
#7.25


#Coeficientul de asimetrie si aplatizare
library(moments)
sk_vol_NXTD<-skewness(analiza1$Volum_NXTD) 
#3.722>1 
sk_vol_GME<-skewness(analiza1$Volum_GME)
#8.14>1
sk_vol_SP<-skewness(analiza1$Volum_SP500)
#1.39


k_vol_GME<-kurtosis(analiza1$Volum_GME) 
#19.15>3 distributie ascutita
k_vol_NXTD<-kurtosis(analiza1$Volum_NXTD)
#80.79>3 distributie ascutita
k_vol_SP<-kurtosis(analiza1$Volum_SP500)
#6.1<3 distributia este platicurtica 

m<-matrix(nrow=4, ncol=3)
m[1,1]<-sk_GME
m[1,2]<-sk_NXTD
m[1,3]<-sk_SP
m[2,1]<-k_pret_GME
m[2,2]<-k_pret_NXTD
m[2,3]<-k_pret_SP
m[3,1]<-sd_pret_GME
m[3,2]<-sd_pret_NXTD
m[3,3]<-sd_pretIndice
m[4,1]<-cv_GME
m[4,2]<-cv_NXTD
m[4,3]<-cv_sp
row.names<-c("skewness", "kurtosis","abatere", "cv")
col.names<-c("GME", "NXTD", "SP500")
dimnames(m)<-list(row.names, col.names)
View(m)
m2<-matrix(nrow=4, ncol=3)
m2[1,1]<-sk_rentGME
m2[1,2]<-sk_rentNXTD
m2[1,3]<-sk_rentIndice
m2[2,1]<-k_rentGME
m2[2,2]<-k_rentNXTD
m2[2,3]<-k_rentINDICE
m2[3,1]<-sd_rentGME
m2[3,2]<-sd_pret_NXTD
m2[3,3]<-sd_rentNXTD
m2[4,1]<-cv_rentGME
m2[4,2]<-cv_rentNXTD
m2[4,3]<-cv_rentSP
row.names<-c("skewness", "kurtosis","abatere", "cv")
col.names<-c("Rentabilitate GME", "Rentabilitate NXTD", "Rentabilitate SP500")
dimnames(m2)<-list(row.names, col.names)
View(m2)

m3<-matrix(nrow=4, ncol=3)
m3[1,1]<-sk_vol_GME
m3[1,2]<-sk_vol_NXTD
m3[1,3]<-sk_vol_SP
m3[2,1]<-k_vol_GME
m3[2,2]<-k_vol_NXTD
m3[2,3]<-k_vol_SP
m3[3,1]<-sd_volum_GME
m3[3,2]<-sd_volum_NXTD
m3[3,3]<-sd_volumIndice
m3[4,1]<-cv_VGME
m3[4,2]<-cv_VNXTD
m3[4,3]<-cv_Vsp
row.names<-c("skewness", "kurtosis","abatere", "cv")
col.names<-c("GME", "NXTD", "SP500")
dimnames(m3)<-list(row.names, col.names)
View(m3)

#matricea de corelatie 
matrice_corelatie<-cor(analiza1[,2:4])
library(corrplot)
windows()
corrplot(matrice_corelatie, main="Matricea de corelatie",method=c("pie"), type=c("lower"), col="red")
matrice_corelatie2 <-cor(analiza1[,2:7])
windows()
corrplot(matrice_corelatie2, main="Matrice de corelatie",method=c("pie"), type=c("upper"), col=142)


matrice_corelatie3<-cor(rentabilitati[,1:3])
library(corrplot)
windows()
corrplot(matrice_corelatie3, main="Matrice de corelatie rentabilitati",method=c("pie"), type=c("upper"), col=258)
#HISTOGRAME
windows()
par(mfrow=c(3,3))
hist(analiza1$Pret_GME, col="green", main="Histograma pretului GME")
hist(analiza1$Pret_NXTD, col="red", main="Histograma pretului NXTD")
hist(analiza1$Pret_SP500, col="purple", main="Histograma pretului SP")
hist(analiza1$Volum_GME, col="violet", main="Histograma volumului GME")
hist(analiza1$Volum_NXTD, col="blue", main="Histograma volumului NXTD")
hist(analiza1$Volum_SP500, col="pink", main="Histograma volumului SP")


#BOXPLOTURI
windows()
par(mfrow=c(3,3))
boxplot(analiza1$Pret_GME, col="green", main="Boxplot pret GME")
boxplot(analiza1$Pret_NXTD, col="red", main="Boxplot  pret NXTD")
boxplot(analiza1$Pret_SP500, col="purple", main="Boxplot  pret SP")
boxplot(analiza1$Volum_GME, col="violet", main="Boxplot  volum GME")
boxplot(analiza1$Volum_NXTD, col="blue", main="Boxplot volum NXTD")
boxplot(analiza1$Volum_SP500, col="pink", main="Boxplot  volum SP")
windows()
par(mfrow=c(2,2))
boxplot(rentabilitati$rent_gme, col="green", main="Boxplot rentabilitate pret GME")
boxplot(rentabilitati$rent_nxtd, col="red", main="Boxplot  rentabilitate pret NXTD")
boxplot(rentabilitati$rent_indice, col="purple", main="Boxplot rentabilitate pret SP")

#PLOTURI
windows()
par(mfrow=c(2,2))
ts.plot(rentabilitati$rent_gme, main=" rentabilitatea GME", col=250, type="l")
plot(rentabilitati$rent_nxtd, main=" rentabilitate NXTD", col=123, type="l")
plot(rentabilitati$rent_indice, main=" rentabilitate indice de piata", col=52, type="l")

preturi<-data.frame(analiza1$Pret_GME, analiza1$Pret_SP500)
preturi1<-data.frame(analiza1$Pret_NXTD, analiza1$Pret_SP500) 
volum<-data.frame(analiza1$Volum_GME, analiza1$Volum_SP500)
volum1<-data.frame(analiza1$Volum_NXTD, analiza1$Volum_SP500)


windows()
ts.plot(analiza1$Pret_SP500, main="Evolutia pretului S&P500", col=c(250,58), xlab="zile", ylab="pret")

ts.plot(analiza1$Pret_NXTD, main="Evolutia pretului actiunilor NXTD", col=c(100,214), xlab="zile", ylab="pret")
ts.plot(preturi, main="Evolutia pretului actiunilor GME si a indicelui de piata", col=c(100,214), xlab="zile", ylab="pret")
legend("topright", c("pret_GME", "pret_SP"), col=c(100,214), lwd=2)
ts.plot(preturi1, main="Evolutia pretului actiunilor NXTD si a indicelui de piata", col=c(178,100), xlab="zile", ylab="pret")
legend("topright", c("pret_NXTD", "pret_SP"), col=c(178,100), lwd=2)


windows()
ts.plot(volum, main="Evolutia volumului actiunilor GME si a indicelui de piata", col=c(100,214), xlab="zile", ylab="pret")
legend("topright", c("volum_GME", "volum_SP"), col=c(100,214), lwd=2)
windows()
ts.plot(volum1, main="Evolutia volumului actiunilor NXTD si a indicelui de piata", col=c(178,100), xlab="zile", ylab="pret")
legend("topright", c("volum_NXTD", "volum_SP"), col=c(178,100), lwd=2)

rentabilit<-data.frame(rentabilitati$rent_gme, rentabilitati$rent_indice)
rentabilit1<-data.frame(rentabilitati$rent_nxtd, rentabilitati$rent_indice)
windows()
ts.plot(rentabilit, main="Evolutia rentabilitatii actiunilor GME si a indicelui de piata", col=c(100,214), xlab="zile", ylab="pret")
legend("topright", c("rent_GME", "rent_SP"), col=c(100,214), lwd=2)
windows()
ts.plot(rentabilit1, main="Evolutia rentabilitatii actiunilor NXTD si a indicelui de piata", col=c(178,100), xlab="zile", ylab="pret")
legend("topright", c("rent_NXTD", "pret_SP"), col=c(178,100), lwd=2)






