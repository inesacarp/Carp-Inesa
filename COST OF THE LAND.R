#pachete
library(moments)
library(readr)
library(corrplot)
library(zoo)
library(corrplot)
library(ggplot2)
getwd()
setwd("C:/Users/user/Desktop/micromanag")
dir()
desk<-read.csv(file="date_seminar_costuri.csv", header=TRUE, sep=",")
View(desk)
attach(desk)
fix(desk)
View(as.matrix(desk))

# Pas1- Statistici descriptive --------------------------------------------

summary(desk)
#observam ca val totale ale locuintelor si ale terenurilor au variatii foarte mari dar mai ales indicii preturilor au val maxime mari
# de 2.71 si 4.83 dar land price index pare a avea o valoare minima de 0.
min(Land_Price_Index)
#totusi valoarea minima nu este zero
#ambii indici de pret au ca baza anul 2000
options(scipen=99)
min(Land_Price_Index)

# Pas2 --------------------------------------------------------------------
#putem folosi comanda unique pentru a afla val unice de pe coloana MSA
help(unique)
unique(MSA)

#extragem un esantion pt NY la comun si inca un oras pe care-l alegem noi (Detroit)

NY<-subset(desk, MSA=="NEWYORK")
View(NY)
unique(NY$MSA)
#avem 126 observatii
DT<-subset(desk, MSA=="DETROIT")
unique(DT$MSA)
#a) sa generam statistici descriptive pentru zona metropolitana 
summary(NY)
#Obs sa val medie a terenului in NY este 199065$ intre 60706 $ si 433581 $, analog obs o valoare mare a locuintelor
summary(DT)
#OBS ca VAL medie a terenului in DT este de 23212 $ (foarte mica) iar val min este de 2755 $ (min pe tot esantionul)
#iar val maxima este de egala cu valoarea min din NY

#b) grafice si sa calculam valorile reale 
attach(NY)
windows()
plot.ts(Land_Value, main="Evolutia valorii terenului", col=158)
NY[which.max(Land_Value),]  #in 2006 Q2 valoarea maxima a terenului in NY
NY[which.min(Land_Value),] #1984 Q4 VAL min a terenului in 

attach(DT)
DT[which.max(Land_Value),] #2003 Q4
DT[which.min(Land_Value),]  #1984 Q4
windows()
plot.ts(Land_Value, main="Evolutia valorii terenului in Detroit", col=158)
#Observam ca val nominala a teren din NY inreg un trend ascendent pana in 2006 
#dupa care are loc o descrestere=>trend descendent, apoi o usoara revenire, dar nu la
#inca din 2006 in SUA se pot vedea semnele inceputului crizei economice iar in jurul anului 2006 inreg perioada de varf,
#efectele crizei sunt vizibile pana in 2012
#transf in val reale pretul terenului din NY

real_land_value_NY<-100*Land_Value/Land_Price_Index
summary(real_land_value_NY)
windows()
hist(real_land_value_NY, main="Histograma pretului real al terenului NY", col=452)

NY<-data.frame(NY, real_land_value_NY)
#val nominala si val reala a terenului in acelasi grafic
windows()
par(mfrow=c(2,1))
plot.ts(Land_Value, main="Evolutia valorii terenului", col=158)
plot.ts(real_land_value_NY, main="Evolutia valorii reale a terenului", col=580)

#valoarea reala a terenului are un trend descendent pe per analizata
#conversia la time series pt a identifica momentele de timp
windows()
plot.ts(ts(NY[,c(6,10)], frequency = 4, start=c(1984,4)),
        main="Evolutia trimestriala a valorilor nominale si reale ale terenurilor", col=158)
real_land_value_DT<-100*Land_Value/Land_Price_Index
DT<-data.frame(DT, real_land_value_DT)
windows()
plot.ts(ts(DT[,c(6,10)], frequency = 4, start=c(1984,4)),
        main="Evolutia trimestriala a valorilor nominale si reale ale terenurilor", col=158)

#c)tema 


# Pas3 --------------------------------------------------------------------

#adaugam zona geografica la baza de date initiala
#Varianta 1 parcurgem msa cu un for si un if
#V2 folosim un if-else
#V3 folosim subset si creem  5 esantioane pt cele 5 zone
attach(desk)
southeast<-subset(desk, MSA==c("ATLANTA",
        "BIRMINGHAM", "CHARLOTTE", "MEMPHIS","TAMPA"))
View(southeast)
unique(southeast)
#analog fac si pt celelalte subesantioane si le unim intr un data frame

#Varianta 2

unique(MSA)
region <- ifelse(MSA %in% c('BUFFALO', 
                            'CHICAGO', 
                            'CINCINNATI', 
                            'CLEVELAND', 
                            'COLUMBUS', 
                            'DETROIT', 
                            'INDIANAPOLIS',
                            'KANSASCITY', 
                            'MILWAUKEE', 
                            'DETROIT', 
                            'MINNEAPOLISSTPAUL', 
                            'PITTSBURGH', 
                            'ROCHESTER', 
                            'STLOUIS' ), "Midwest", 
                 ifelse ( MSA %in% c('ATLANTA', 
                                     'BIRMINGHAM', 
                                     'CHARLOTTE', 
                                     'MEMPHIS', 
                                     'TAMPA'), 'Southeast', 
                          ifelse ( MSA %in% c('DALLAS', 
                                              'DENVER', 
                                              'FORTWORTH',
                                              'HOUSTON',
                                              'NEWORLEANS',
                                              'OKLAHOMACITY',	
                                              'PHOENIX',
                                              'SALTLAKECITY',
                                              'SANANTONIO'),'Southwest',	
                                   ifelse( MSA %in% c('BALTIMORE',
                                                      'BOSTON',
                                                      'HARTFORD',	
                                                      'MIAMI',
                                                      'NEWYORK',
                                                      'NORFOLK',
                                                      'PHILADELPHIA',
                                                      'PROVIDENCE',
                                                      'WASHINGTONDC'),'East Coast', 'West Coast'))))

unique(region)


desk<-data.frame(desk, region)
write.csv(desk, file="date_seminar_costuri_regiune.csv")

# pas4 --------------------------------------------------------------------

#Extragem 2 zone geografice una comuna (east coast,) si midcoast
eastcoast<-subset(desk, region=="East Coast")
unique(eastcoast$region)
southeast<-subset(desk, region=="Southwest")
unique(southeast$region)

#tema de rulat statisticile descriptive pt cele 2 zone alese si histograma si blox pt val terenului din cele 2 zone
#seminar 12
#histograme cu ggplot2
